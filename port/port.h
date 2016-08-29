// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#ifndef STORAGE_LEVELDB_PORT_PORT_H_
#define STORAGE_LEVELDB_PORT_PORT_H_

#include <string.h>

#ifdef _WIN32
#define LEVELDB_PLATFORM_WINDOWS
#if defined(_WIN64) || defined(_M_X64) || defined(__x86_64__)
typedef signed __int64 ssize_t;
#elif defined(_WIN32) || defined(_M_IX86) || defined(__i386__) || defined(__i386)
typedef signed int ssize_t;
#else
typedef signed long long ssize_t;
#endif
#endif

// Include the appropriate platform specific file below.  If you are
// porting to a new platform, see "port_example.h" for documentation
// of what the new port_<platform>.h file must provide.
#if defined(LEVELDB_PLATFORM_POSIX)
#  include "port/port_posix.h"
#elif defined(LEVELDB_PLATFORM_CHROMIUM)
#  include "port/port_chromium.h"
#elif defined(LEVELDB_PLATFORM_WINDOWS)
#  include "port/port_win.h"
#endif

#endif  // STORAGE_LEVELDB_PORT_PORT_H_
