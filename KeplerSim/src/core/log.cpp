#include "Log.h"

std::shared_ptr<spdlog::logger> Log::m_Logger;
bool Log::m_Initialized = false;

void Log::Init() {
    if (m_Initialized) {
        CORE_WARN("Logger already initialized.");
        return;
    }

    spdlog::set_pattern("%^[%T] %n: %v%$");  // [HH:MM:SS] loggerName: log

    m_Logger = spdlog::stdout_color_mt("ENGINE");

#ifndef NDEBUG
    m_Logger->set_level(spdlog::level::trace);
#endif  // !NDEBUG

    CORE_INFO("Logger initialized");

    m_Initialized = true;
}
