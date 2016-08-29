// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#include "port/port_win.h"

#include <cstdlib>
#include <stdio.h>
#include <string.h>

#ifdef _WIN32
  #ifndef LEVELDB_PLATFORM_WINDOWS
    #define LEVELDB_PLATFORM_WINDOWS
  #endif
#endif // _WIN32

#if defined(LEVELDB_PLATFORM_WINDOWS)

namespace leveldb {
namespace port {

static void PthreadCall(const char* label, int result) {
  if (result != 0) {
    fprintf(stderr, "pthread %s: %s\n", label, strerror(result));
    abort();
  }
}

Mutex::Mutex() { PthreadCall("init mutex", ::InitializeCriticalSectionAndSpinCount(&cs_, 4000)); }

Mutex::~Mutex() { ::DeleteCriticalSection(&cs_); PthreadCall("destroy mutex", 1); }

void Mutex::Lock() { ::EnterCriticalSection(&cs_); PthreadCall("lock", 1); }

void Mutex::Unlock() { ::LeaveCriticalSection(&cs_); PthreadCall("unlock", 1); }

CondVar::CondVar(Mutex* mutex)
    : mutex_(mutex) {
    event_ = ::CreateEvent(NULL, FALSE, FALSE, NULL);
    PthreadCall("init cv", 1);
}

CondVar::~CondVar() { PthreadCall("destroy cv", ::CloseHandle(event_)); }

void CondVar::Wait() {
  DWORD result = ::WaitForSingleObject(event_, INFINITE);
  PthreadCall("wait", (int)result);
}

void CondVar::Signal() {
  BOOL result = ::SetEvent(event_);
  PthreadCall("signal", result);
}

void CondVar::SignalAll() {
  BOOL result = ::SetEvent(event_);
  PthreadCall("broadcast", result);
}

void InitOnce(OnceType* once, void (*initializer)()) {
  int result = pthread_once(once, initializer);;
  PthreadCall("once", result);
}

}  // namespace port
}  // namespace leveldb

#endif // LEVELDB_PLATFORM_WINDOWS