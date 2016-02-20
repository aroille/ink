#pragma once

#include "ink.h"

#include <cstdarg>
#include <sstream>

#define INK_LOG(level, module, msg) { \
  std::ostringstream ss; \
  ss << msg; \
  ink::Log::instance.log(level, module, ss); \
}

#define INK_LOG_DEBUG(module, msg)		INK_LOG(ink::Log::Level::Debug,   module, msg);
#define INK_LOG_INFO(module, msg)		  INK_LOG(ink::Log::Level::Info,    module, msg);
#define INK_LOG_WARNING(module, msg)	INK_LOG(ink::Log::Level::Warning, module, msg);
#define INK_LOG_ERROR(module, msg)		INK_LOG(ink::Log::Level::Error,   module, msg);
#define INK_LOG_FATAL(module, msg)		INK_LOG(ink::Log::Level::Fatal,   module, msg);

namespace ink
{
  struct Log
  {
  public:

    enum class Level
    {
      Debug,
      Info,
      Warning,
      Error,
      Fatal,

      Count
    };

    void log(Level level, const char* module, const std::ostringstream& msg) const;

    static const Log instance;
  };

}	// namespace ink

