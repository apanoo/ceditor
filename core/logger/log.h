#pragma once

#include <memory>

#include "api/core.h"
#include "common/ref.h"
#include "spdlog/spdlog.h"

class Log {
public:
  static void Init();

  static Ref<spdlog::logger> &GetCoreLogger() { return s_CoreLogger; }
  static Ref<spdlog::logger> &GetClientLogger() { return s_ClientLogger; }

private:
  static Ref<spdlog::logger> s_CoreLogger;
  static Ref<spdlog::logger> s_ClientLogger;
};

// Core log macros
#define HZ_CORE_TRACE(...) ::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define HZ_CORE_INFO(...) ::Log::GetCoreLogger()->info(__VA_ARGS__)
#define HZ_CORE_WARN(...) ::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define HZ_CORE_ERROR(...) ::Log::GetCoreLogger()->error(__VA_ARGS__)
#define HZ_CORE_CRITICAL(...) ::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define HZ_TRACE(...) ::Log::GetClientLogger()->trace(__VA_ARGS__)
#define HZ_INFO(...) ::Log::GetClientLogger()->info(__VA_ARGS__)
#define HZ_WARN(...) ::Log::GetClientLogger()->warn(__VA_ARGS__)
#define HZ_ERROR(...) ::Log::GetClientLogger()->error(__VA_ARGS__)
#define HZ_CRITICAL(...) ::Log::GetClientLogger()->critical(__VA_ARGS__)