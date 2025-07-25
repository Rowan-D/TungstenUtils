#include "wUtilsPCH.hpp"
#include "TungstenUtils/WriteFile.hpp"

namespace wUtils
{
    bool WriteFile(const std::filesystem::path& path, const std::string_view content, TungstenLogger& errorList)
    {
        std::ofstream file(path, std::ios::binary | std::ios::trunc);
        if (!file)
        {
            W_LOG_ERROR(errorList, "Failed to open file for writing: {}", path.string());
            return false;
        }

        file.write(content.data(), static_cast<std::streamsize>(content.size()));
        if (!file)
        {
            W_LOG_ERROR(errorList, "Failed to write file: {}", path.string());
            return false;
        }

        return true;
    }

    bool WriteFile(const std::filesystem::path& path, const std::string_view content)
    {
        return WriteFile(path, content, W_GET_DEBUG_LOGGER());
    }
}