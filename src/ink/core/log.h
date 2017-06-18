#pragma once

#include <sstream>

#define INK_LOG(msg) { \
  std::ostringstream ss; \
  ss << msg; \
  ink::Log::instance.log(ss); \
}

namespace ink
{
  struct Log
  {
  public:
    void log(const std::ostringstream& msg) const;
    static const Log instance;
  };

}	// namespace ink

