//
// Copyright (c) 2014, Facebook, Inc.
// All rights reserved.
//
// This source code is licensed under the University of Illinois/NCSA Open
// Source License found in the LICENSE file in the root directory of this
// source tree. An additional grant of patent rights can be found in the
// PATENTS file in the same directory.
//

#ifndef __DebugServer2_GDBRemote_DummySessionDelegateImpl_h
#define __DebugServer2_GDBRemote_DummySessionDelegateImpl_h

#include "DebugServer2/GDBRemote/SessionDelegate.h"

namespace ds2 {
namespace GDBRemote {

class DummySessionDelegateImpl : public SessionDelegate {
protected:
  bool _secure;

protected:
  DummySessionDelegateImpl();

protected: // General Information
  size_t getGPRSize() const override;

protected: // Common
  ErrorCode onEnableExtendedMode(Session &session) override;
  ErrorCode onSetBaudRate(Session &session, uint32_t speed) override;
  ErrorCode onToggleDebugFlag(Session &session) override;

  ErrorCode onSetMaxPacketSize(Session &session, size_t size) override;
  ErrorCode onSetMaxPayloadSize(Session &session, size_t size) override;

  void onSetLogging(Session &session, std::string const &mode,
                    std::string const &filename,
                    StringCollection const &flags) override;

  ErrorCode
  onAllowOperations(Session &session,
                    std::map<std::string, bool> const &operations) override;
  ErrorCode onQuerySupported(Session &session,
                             Feature::Collection const &remoteFeatures,
                             Feature::Collection &localFeatures) override;

  ErrorCode onExecuteCommand(Session &session,
                             std::string const &command) override;

  ErrorCode onQueryServerVersion(Session &session,
                                 ServerVersion &version) override;
  ErrorCode onQueryHostInfo(Session &session, HostInfo &info) override;

protected: // Debugging Session
  ErrorCode onEnableControlAgent(Session &session, bool enable) override;
  ErrorCode onNonStopMode(Session &session, bool enable) override;
  ErrorCode onEnableBTSTracing(Session &session, bool enable) override;

  ErrorCode onPassSignals(Session &session,
                          std::vector<int> const &signals) override;
  ErrorCode onProgramSignals(Session &session,
                             std::vector<int> const &signals) override;

  ErrorCode onQuerySymbol(Session &session, std::string const &name,
                          std::string const &value, std::string &next) override;

  ErrorCode onQueryRegisterInfo(Session &session, uint32_t regno,
                                RegisterInfo &info) override;

  ErrorCode onAttach(Session &session, ProcessId pid, AttachMode mode,
                     StopCode &stop) override;
  ErrorCode onAttach(Session &session, std::string const &name, AttachMode mode,
                     StopCode &stop) override;
  ErrorCode onRunAttach(Session &session, std::string const &filename,
                        StringCollection const &arguments,
                        StopCode &stop) override;
  ErrorCode onDetach(Session &session, ProcessId pid, bool stopped) override;
  ErrorCode onQueryAttached(Session &session, ProcessId pid,
                            bool &attachedProcess) override;
  ErrorCode onQueryProcessInfo(Session &session, ProcessInfo &info) override;

  ErrorCode onQueryHardwareWatchpointCount(Session &session,
                                           size_t &count) override;

  ErrorCode onQuerySectionOffsets(Session &session, Address &text,
                                  Address &data, bool &isSegment) override;
  ErrorCode onQuerySharedLibrariesInfoAddress(Session &session,
                                              Address &address) override;
  ErrorCode onQuerySharedLibraryInfo(Session &session, std::string const &path,
                                     std::string const &triple,
                                     SharedLibraryInfo &info) override;

  ErrorCode onRestart(Session &session, ProcessId pid) override;
  ErrorCode onInterrupt(Session &session) override;
  ErrorCode onTerminate(Session &session, ProcessThreadId const &ptid,
                        StopCode &stop) override;
  ErrorCode onTerminate(Session &session, ProcessId pid) override;

  ErrorCode onSynchronizeThreadState(Session &session, ProcessId pid) override;

  //
  // If lastTid is kAllThreadId, it's the first request; if it's kAnyThreadId
  // the next of the previous request, in any other case the thread next to
  // the one specified.
  //
  ErrorCode onQueryThreadList(Session &session, ProcessId pid, ThreadId lastTid,
                              ThreadId &tid) override;

  ErrorCode onQueryThreadStopInfo(Session &session, ProcessThreadId const &ptid,
                                  StopCode &stop) override;

  ErrorCode onQueryCurrentThread(Session &session,
                                 ProcessThreadId &ptid) override;
  ErrorCode onThreadIsAlive(Session &session,
                            ProcessThreadId const &ptid) override;
  ErrorCode onQueryThreadInfo(Session &session, ProcessThreadId const &ptid,
                              uint32_t mode, void *info) override;

  ErrorCode onQueryTLSAddress(Session &session, ProcessThreadId const &ptid,
                              Address const &offset, Address const &linkMap,
                              Address &address) override;
  ErrorCode onQueryTIBAddress(Session &session, ProcessThreadId const &ptid,
                              Address &address) override;

  ErrorCode onEnableAsynchronousProfiling(Session &session,
                                          ProcessThreadId const &ptid,
                                          bool enabled, uint32_t interval,
                                          uint32_t scanType) override;
  ErrorCode onQueryProfileData(Session &session, ProcessThreadId const &ptid,
                               uint32_t scanType, void *data) override;

  ErrorCode onResume(Session &session,
                     ThreadResumeAction::Collection const &actions,
                     StopCode &stop) override;

  ErrorCode
  onReadGeneralRegisters(Session &session, ProcessThreadId const &ptid,
                         Architecture::GPRegisterValueVector &regs) override;
  ErrorCode onWriteGeneralRegisters(Session &session,
                                    ProcessThreadId const &ptid,
                                    std::vector<uint64_t> const &regs) override;

  ErrorCode onSaveRegisters(Session &session, ProcessThreadId const &ptid,
                            uint64_t &id) override;
  ErrorCode onRestoreRegisters(Session &session, ProcessThreadId const &ptid,
                               uint64_t id) override;

  ErrorCode onReadRegisterValue(Session &session, ProcessThreadId const &ptid,
                                uint32_t regno, std::string &value) override;
  ErrorCode onWriteRegisterValue(Session &session, ProcessThreadId const &ptid,
                                 uint32_t regno,
                                 std::string const &value) override;

  ErrorCode onReadMemory(Session &session, Address const &address,
                         size_t length, std::string &data) override;
  ErrorCode onWriteMemory(Session &session, Address const &address,
                          std::string const &data, size_t &nwritten) override;

  ErrorCode onAllocateMemory(Session &session, size_t size,
                             uint32_t permissions, Address &address) override;
  ErrorCode onDeallocateMemory(Session &session,
                               Address const &address) override;
  ErrorCode onQueryMemoryRegionInfo(Session &session, Address const &address,
                                    MemoryRegionInfo &info) override;

  ErrorCode onComputeCRC(Session &session, Address const &address,
                         size_t length, uint32_t &crc) override;

  ErrorCode onSearch(Session &session, Address const &address,
                     std::string const &pattern, Address &location) override;
  ErrorCode onSearchBackward(Session &session, Address const &address,
                             uint32_t pattern, uint32_t mask,
                             Address &location) override;

  ErrorCode onInsertBreakpoint(Session &session, BreakpointType type,
                               Address const &address, uint32_t kind,
                               StringCollection const &conditions,
                               StringCollection const &commands,
                               bool persistentCommands) override;
  ErrorCode onRemoveBreakpoint(Session &session, BreakpointType type,
                               Address const &address, uint32_t kind) override;

  ErrorCode onXferRead(Session &session, std::string const &object,
                       std::string const &annex, uint64_t offset,
                       uint64_t length, std::string &buffer,
                       bool &last) override;
  ErrorCode onXferWrite(Session &session, std::string const &object,
                        std::string const &annex, uint64_t offset,
                        std::string const &buffer, size_t &nwritten) override;

protected: // Platform Session
  ErrorCode onDisableASLR(Session &session, bool disable) override;

  ErrorCode onSetEnvironmentVariable(Session &session, std::string const &name,
                                     std::string const &value) override;
  ErrorCode onSetWorkingDirectory(Session &session,
                                  std::string const &path) override;
  ErrorCode onSetStdFile(Session &session, int fileno,
                         std::string const &path) override;

  ErrorCode onSetArchitecture(Session &session,
                              std::string const &architecture) override;

  ErrorCode onSetProgramArguments(Session &session,
                                  StringCollection const &args) override;

  ErrorCode onExecuteProgram(Session &session, std::string const &command,
                             uint32_t timeout,
                             std::string const &workingDirectory,
                             ProgramResult &result) override;

  ErrorCode onFileCreateDirectory(Session &session, std::string const &path,
                                  uint32_t mode) override;

  ErrorCode onFileOpen(Session &session, std::string const &path,
                       uint32_t flags, uint32_t mode, int &fd) override;
  ErrorCode onFileClose(Session &session, int fd) override;
  ErrorCode onFileRead(Session &session, int fd, size_t count, uint64_t offset,
                       std::string &buffer) override;
  ErrorCode onFileWrite(Session &session, int fd, uint64_t offset,
                        std::string const &buffer, size_t &nwritten) override;

  ErrorCode onFileRemove(Session &session, std::string const &path) override;
  ErrorCode onFileReadLink(Session &session, std::string const &path,
                           std::string &resolved) override;

#if 0
    //
    // more F packets:
    // https://sourceware.org/gdb/onlinedocs/gdb/List-of-Supported-Calls.html#List-of-Supported-Calls
    //
    virtual ErrorCode onGetCurrentTime(Session &session, TimeValue &tv);

    virtual ErrorCode onFileIsATTY(Session &session, int fd);
    virtual ErrorCode onFileRename(Session &session,
            std::string const &oldPath, std::string const &newPath);

    virtual ErrorCode onFileGetStat(Session &session, std::string const &path,
            FileStat &stat);
    virtual ErrorCode onFileGetStat(Session &session, int fd,
            FileStat &stat);

    virtual ErrorCode onFileSeek(Session &session, int fd,
            int64_t offset, int whence, int64_t &newOffset);
#endif

  ErrorCode onFileExists(Session &session, std::string const &path) override;
  ErrorCode onFileComputeMD5(Session &session, std::string const &path,
                             uint8_t digest[16]) override;
  ErrorCode onFileGetSize(Session &session, std::string const &path,
                          uint64_t &size) override;

  ErrorCode onQueryProcessList(Session &session, ProcessInfoMatch const &match,
                               bool first, ProcessInfo &info) override;
  ErrorCode onQueryProcessInfo(Session &session, ProcessId pid,
                               ProcessInfo &info) override;

  ErrorCode onLaunchDebugServer(Session &session, std::string const &host,
                                uint16_t &port, ProcessId &pid) override;

  ErrorCode onQueryLaunchSuccess(Session &session, ProcessId pid) override;

  ErrorCode onQueryUserName(Session &session, UserId const &uid,
                            std::string &name) override;
  ErrorCode onQueryGroupName(Session &session, GroupId const &gid,
                             std::string &name) override;
  ErrorCode onQueryWorkingDirectory(Session &session,
                                    std::string &workingDir) override;

protected: // System Session
  void onReset(Session &session) override;
  ErrorCode onFlashErase(Session &session, Address const &address,
                         size_t length) override;
  ErrorCode onFlashWrite(Session &session, Address const &address,
                         std::string const &data) override;
  ErrorCode onFlashDone(Session &session) override;
};
}
}

#endif // !__DebugServer2_GDBRemote_DummySessionDelegateImpl_h
