#pragma once

#include <sstream>

#define INK_LOG(level, msg) { \
  std::ostringstream ss; \
  ss << msg; \
  ink::Log::instance.log(level, ss); \
}

#define INK_LOG_DEBUG(msg)		INK_LOG(ink::Log::Level::Debug,   msg);
#define INK_LOG_INFO(msg)		  INK_LOG(ink::Log::Level::Info,    msg);
#define INK_LOG_WARNING(msg)	INK_LOG(ink::Log::Level::Warning, msg);
#define INK_LOG_ERROR(msg)		INK_LOG(ink::Log::Level::Error,   msg);
#define INK_LOG_FATAL(msg)		INK_LOG(ink::Log::Level::Fatal,   msg);

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

    void log(Level level, const std::ostringstream& msg) const;

    static const Log instance;
  };

}	// namespace ink

