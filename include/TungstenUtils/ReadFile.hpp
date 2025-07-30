#ifndef TUNGSTEN_UTILS_READ_FILE_HPP
#define TUNGSTEN_UTILS_READ_FILE_HPP

#include <string>
#include <filesystem>
#include <optional>

#include <TungstenUtils/TungstenLogger.hpp>

namespace wUtils
{
    std::optional<std::string> ReadFile(const std::filesystem::path& path, TungstenLogger& errorList);
    std::optional<std::string> ReadFile(const std::filesystem::path& path);
}

#endif