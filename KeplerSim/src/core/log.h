#pragma once

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

class Log {
   public:
    static void Init();

    inline static std::shared_ptr<spdlog::logger>& GetLogger() { return m_Logger; }
    inline static const bool IsInitialized() { return m_Initialized; }

   private:
    static std::shared_ptr<spdlog::logger> m_Logger;
    static bool m_Initialized;
};

#ifndef NDEBUG
#define CORE_TRACE(...) ::Log::GetLogger()->trace(__VA_ARGS__)
#define CORE_INFO(...) ::Log::GetLogger()->info(__VA_ARGS__)
#define CORE_WARN(...) ::Log::GetLogger()->warn(__VA_ARGS__)
#define CORE_ERROR(...) ::Log::GetLogger()->error(__VA_ARGS__)
#define CORE_FATAL(...)                            \
    {                                              \
        ::Log::GetLogger()->critical(__VA_ARGS__); \
        CORE_DEBUGBREAK;                           \
    }
#else

#define CORE_TRACE(...)
#define CORE_INFO(...)
#define CORE_WARN(...)
#define CORE_ERROR(...)
#define CORE_FATAL(...)
#endif