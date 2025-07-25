#ifndef TUNGSTEN_UTILS_WRITE_FILE_HPP
#define TUNGSTEN_UTILS_WRITE_FILE_HPP

#include <string_view>
#include <filesystem>

#include "TungstenLogger.hpp"

namespace wUtils
{
    bool WriteFile(const std::filesystem::path& path, std::string_view content, TungstenLogger& errorList);
    bool WriteFile(const std::filesystem::path& path, std::string_view content);
}

#endif