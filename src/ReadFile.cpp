#include "wUtilsPCH.hpp"
#include "TungstenUtils/ReadFile.hpp"

namespace wUtils
{
    std::optional<std::string> ReadFile(const std::filesystem::path& path, TungstenLogger& errorList)
    {
        std::ifstream file(path, std::ios::binary | std::ios::ate);
        if (!file)
        {
            W_LOG_ERROR(errorList, "Failed to open file: {}", path.string());
            return std::nullopt;
        }

        const std::streamsize size = file.tellg();
        if (size < 0)
        {
            W_LOG_ERROR(errorList, "Error getting file size! Path: {}", path.string());
            return std::nullopt;
        }

        std::string content;
        content.resize(static_cast<size_t>(size));
        file.seekg(0);
        file.read(content.data(), size);

        if (!file)
        {
            W_LOG_ERROR(errorList, "Failed to read file! Path: {}", path.string());
            return std::nullopt;
        }

        return content;
    }

    std::optional<std::string> ReadFile(const std::filesystem::path& path)
    {
        return ReadFile(path, W_GET_DEBUG_LOGGER());
    }
}
