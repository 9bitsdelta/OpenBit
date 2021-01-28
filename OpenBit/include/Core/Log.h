#pragma once

#include "Core/Base.h"

// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)


namespace Bit {

    class Log
    {
    public:
        static void Init();

        static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
    private:
        static Ref<spdlog::logger> s_CoreLogger;
        static Ref<spdlog::logger> s_ClientLogger;
    };

}

// Core log macros
#define BIT_CORE_TRACE(...)    ::Bit::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define BIT_CORE_INFO(...)     ::Bit::Log::GetCoreLogger()->info(__VA_ARGS__)
#define BIT_CORE_WARN(...)     ::Bit::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define BIT_CORE_ERROR(...)    ::Bit::Log::GetCoreLogger()->error(__VA_ARGS__)
#define BIT_CORE_CRITICAL(...) ::Bit::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define BIT_TRACE(...)         ::Bit::Log::GetClientLogger()->trace(__VA_ARGS__)
#define BIT_INFO(...)          ::Bit::Log::GetClientLogger()->info(__VA_ARGS__)
#define BIT_WARN(...)          ::Bit::Log::GetClientLogger()->warn(__VA_ARGS__)
#define BIT_ERROR(...)         ::Bit::Log::GetClientLogger()->error(__VA_ARGS__)
#define BIT_CRITICAL(...)      ::Bit::Log::GetClientLogger()->critical(__VA_ARGS__)
