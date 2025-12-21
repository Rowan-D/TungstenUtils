#ifndef TUNGSTEN_UTILS_READ_FILE_HPP
#define TUNGSTEN_UTILS_READ_FILE_HPP

#include <string>
#include <filesystem>
#include <optional>

#include <TungstenUtils/TungstenLogger.hpp>

namespace wUtils
{
    [[nodiscard]] std::optional<std::string> ReadFile(const std::filesystem::path& path, TungstenLogger& errorList);
    [[nodiscard]] inline std::optional<std::string> ReadFile(const std::filesystem::path& path) { return ReadFile(path, W_GET_DEBUG_LOGGER()); }
}

#endif