#include "core/log.h"

#include <ctime>
#include <cstdio>
#include <iostream>

#ifdef  _MSC_VER
  #include <windows.h>
#endif

namespace ink
{
  const Log Log::instance = {};

  char LogLevelString[(unsigned)Log::Level::Count][8] =
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

    sprintf(msg_buffer, "  %-8s  %04d-%02d-%02d %02d:%02d:%02d  %s%s",
      LogLevelString[(unsigned)level],
      now->tm_year + 1900, now->tm_mon + 1, now->tm_mday,
      now->tm_hour, now->tm_min, now->tm_sec,
      msg.str().c_str(), "\n");

    // output log message
    printf("%s", msg_buffer);
  }

}	// namespace ink

