#ifndef TUNGSTEN_UTILS_PLATFROM_FALLBACK_LOGGER_HPP
#define TUNGSTEN_UTILS_PLATFROM_FALLBACK_LOGGER_HPP

#include <TungstenUtils/platform/exceptionsConfig.hpp>
#include <TungstenUtils/macros/ansi.hpp>
#include <TungstenUtils/macros/ansiConfig.hpp>

#define W_FALLBACK_LOG(message) wUtils::platform::FallbackLog(message);

#if W_HAS_EXCEPTIONS
    #define W_TRY_NOEXCEPT(stmt) \
        do \
        { \
            try { stmt; } \
            catch (...) \
            { \
                wUtils::platform::FallbackLog(W_COLOR_LIT("[FALLBACK LOG] logging threw; using fallback!", ANSI_BRIGHT_RED)); \
            } \
        } \
        while (false)
#else
    #define W_TRY_NOEXCEPT(stmt) do { stmt; } while (false)
#endif

namespace wUtils::platform
{
    void FallbackLog(const char* message) noexcept;
}

#endif