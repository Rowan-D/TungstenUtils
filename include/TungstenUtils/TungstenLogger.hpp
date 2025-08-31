#ifndef TUNGSTEN_UTILS_TUNGSTEN_LOGGER_HPP
#define TUNGSTEN_UTILS_TUNGSTEN_LOGGER_HPP

#include <iostream>
#include <fmt/format.h>
#include <TungstenUtils/macros/ansi.hpp>
#include <TungstenUtils/platform/FallbackLogger.hpp>

#define W_GET_DEBUG_LOGGER() wUtils::TungstenLogger::GetDebugLogger()

#define W_LOG_INFO(logger, ...) logger.LogInfo(__VA_ARGS__)
#define W_LOG_WARNING(logger, ...) logger.LogWarning(__VA_ARGS__)
#define W_LOG_ERROR(logger, ...) logger.LogError(__VA_ARGS__)
#define W_LOG_CRITICAL_ERROR(logger, ...) logger.LogCritical(__VA_ARGS__)

#define W_LOG_INFO_NOEXCEPT(logger, ...) W_TRY_NOEXCEPT(W_LOG_INFO(logger, __VA_ARGS__))
#define W_LOG_WARNING_NOEXCEPT(logger, ...)W_TRY_NOEXCEPT(W_LOG_WARNING(logger, __VA_ARGS__))
#define W_LOG_ERROR_NOEXCEPT(logger, ...) W_TRY_NOEXCEPT(W_LOG_ERROR(logger, __VA_ARGS__))
#define W_LOG_CRITICAL_ERROR_NOEXCEPT(logger, ...) W_TRY_NOEXCEPT(W_LOG_INFO(logger, __VA_ARGS__))

#define W_DEBUG_LOG_INFO(...) W_LOG_INFO_NOEXCEPT(W_GET_DEBUG_LOGGER(), __VA_ARGS__)
#define W_DEBUG_LOG_WARNING(...) W_LOG_WARNING_NOEXCEPT(W_GET_DEBUG_LOGGER(), __VA_ARGS__)
#define W_DEBUG_LOG_ERROR(...) W_LOG_ERROR_NOEXCEPT(W_GET_DEBUG_LOGGER(), __VA_ARGS__)
#define W_DEBUG_LOG_CRITICAL_ERROR(...) W_LOG_CRITICAL_ERROR_NOEXCEPT(W_GET_DEBUG_LOGGER(), __VA_ARGS__)

namespace wUtils
{
    class TungstenLogger
    {
    public:
        template<typename... Args>
        void LogInfo(fmt::format_string<Args...> fmt, Args&&... args)
        {
            std::cout << ANSI_BLUE << "[Info] " << ANSI_RESET << fmt::format(fmt, std::forward<Args>(args)...) << std::endl;
        }

        template<typename... Args>
        void LogWarning(fmt::format_string<Args...> fmt, Args&&... args)
        {
            std::cout << ANSI_YELLOW << "[Warning] " << ANSI_RESET << fmt::format(fmt, std::forward<Args>(args)...) << std::endl;
        }

        template<typename... Args>
        void LogError(fmt::format_string<Args...> fmt, Args&&... args)
        {
            std::cerr << ANSI_RED << "[Error] " << ANSI_RESET << fmt::format(fmt, std::forward<Args>(args)...) << std::endl;
        }

        template<typename... Args>
        void LogCritical(fmt::format_string<Args...> fmt, Args&&... args)
        {
            std::cerr << ANSI_BG_RED << ANSI_YELLOW << "[Error] " << ANSI_RESET << fmt::format(fmt, std::forward<Args>(args)...) << std::endl;
        }

        static TungstenLogger& GetDebugLogger();
    private:
    };
}

#endif