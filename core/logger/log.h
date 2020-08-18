#pragma once

#include <memory>

#include "api/core.h"
#include "spdlog/spdlog.h"

class CE_API Log
{
public:
    static void Init();

    inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
    inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
private:
    static std::shared_ptr<spdlog::logger> s_CoreLogger;
    static std::shared_ptr<spdlog::logger> s_ClientLogger;
};


// Core log macros
#define HZ_CORE_TRACE(...)    Log::GetCoreLogger()->trace(__VA_ARGS__)
#define HZ_CORE_INFO(...)     Log::GetCoreLogger()->info(__VA_ARGS__)
#define HZ_CORE_WARN(...)     Log::GetCoreLogger()->warn(__VA_ARGS__)
#define HZ_CORE_ERROR(...)    Log::GetCoreLogger()->error(__VA_ARGS__)
#define HZ_CORE_FATAL(...)    Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define HZ_TRACE(...)	      Log::GetClientLogger()->trace(__VA_ARGS__)
#define HZ_INFO(...)	      Log::GetClientLogger()->info(__VA_ARGS__)
#define HZ_WARN(...)	      Log::GetClientLogger()->warn(__VA_ARGS__)
#define HZ_ERROR(...)	      Log::GetClientLogger()->error(__VA_ARGS__)
#define HZ_FATAL(...)	      Log::GetClientLogger()->fatal(__VA_ARGS__)