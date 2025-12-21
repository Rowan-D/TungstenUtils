#ifndef TUNGSTEN_UTILS_PLATFORM_EXECUTABLE_PAtH_HPP
#define TUNGSTEN_UTILS_PLATFORM_EXECUTABLE_PAtH_HPP

#include <filesystem>

#include <TungstenUtils/TungstenLogger.hpp>

namespace wUtils::platform
{
    [[nodiscard]] std::filesystem::path ExecutablePath(TungstenLogger& errorList);
    [[nodiscard]] inline std::filesystem::path ExecutablePath() { ExecutablePath(W_GET_DEBUG_LOGGER()); }
    [[nodiscard]] std::filesystem::path ExecutableDir(TungstenLogger& errorList);
    [[nodiscard]] inline std::filesystem::path ExecutableDir() { ExecutablePath(W_GET_DEBUG_LOGGER()); }
}

#endif