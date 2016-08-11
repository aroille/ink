#pragma once

#include "core/log.h"
#include "core/ink.h"

#include <ctime>
#include <cstdio>
#include <cstring>
#include <iostream>

#ifdef  _MSC_VER
  #include <windows.h>
#endif

namespace ink
{
  const Log Log::instance;

  char LogLevelString[(uint32)Log::Level::Count][8] =
  {
    "DEBUG",
    "INFO",
    "WARNING",
    "ERROR",
    "FATAL"
  };

  void Log::log(Level level, const std::ostringstream& msg) const
  {
    // get time
    time_t t = std::time(0);
    tm* now = localtime(&t);

    // output format
    char msg_buffer[512];

    sprintf_s(msg_buffer, sizeof(msg_buffer), "  %-8s  %04d-%02d-%02d %02d:%02d:%02d  %s",
      LogLevelString[(unsigned)level],
      now->tm_year + 1900, now->tm_mon + 1, now->tm_mday,
      now->tm_hour, now->tm_min, now->tm_sec,
      msg.str().c_str());

    // output log message
    printf(msg_buffer);
    printf("\n");

    #ifdef _MSC_VER
      OutputDebugStringA(msg_buffer);
      OutputDebugStringA("\n");
    #endif
  }

}	// namespace ink

