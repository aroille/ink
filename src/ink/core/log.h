#pragma once

#include <sstream>

#define INK_LOG(msg) { \
  std::ostringstream ss; \
  ss << msg; \
  ink::Log::instance.log(ss); \
}

#define INK_LOG_INFO(msg)		  INK_LOG(ink::Log::Level::Info,    msg);
namespace ink
{
  struct Log
  {
  public:
    void log(const std::ostringstream& msg) const;
    static const Log instance;
  };

}	// namespace ink

