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

  void Log::log(const std::ostringstream& msg) const
  {
    // get time
    time_t t = std::time(0);
    tm* now = localtime(&t);

    // output format
    char msg_buffer[512];

    sprintf(msg_buffer, "%02d:%02d:%02d  %s%s",
      now->tm_hour, now->tm_min, now->tm_sec,
      msg.str().c_str(), "\n");

    // output log message
    printf("%s", msg_buffer);
  }

}	// namespace ink

