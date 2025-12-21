#include "wUtilsPCH.hpp"
#include <filesystem>
#include "TungstenUtils/platform/ExecutablePath.hpp"

namespace wUtils::platform
{
    std::filesystem::path ExecutablePath(TungstenLogger& errorList)
    {
#if defined(_WIN32)
        wchar_t buffer[MAX_PATH];
        const DWORD len = GetModuleFileNameW(nullptr, buffer, MAX_PATH);
        if (len == 0)
        {
            W_LOG_ERROR(errorList, "ExecutablePath: GetModuleFileNameW failed.");
            return {};
        }
        return std::filesystem::path(buffer, buffer + len);

#elif defined(__APPLE__)
        char buffer[PATH_MAX];
        const uint32_t size = sizeof(buffer);
        if (_NSGetExecutablePath(buffer, &size) == 0)
        {
            try
            {
                return std::filesystem::canonical(buffer);
            }
            catch (const fs::filesystem_error& e)
            {
                W_LOG_ERROR(errorList, "ExecutablePath: Canonicalizing macOS exe path Filesystem Error: {}", e.what());
                return {};
            }
            catch (const std::exception& e)
            {
                W_LOG_ERROR(errorList, "ExecutablePath: Canonicalizing macOS exe path General Error: {}", e.what());
                return {};
            }
        }

        W_LOG_ERROR(errorList, "ExecutablePath: _NSGetExecutablePath failed.");
        return {};

#elif defined(__linux__)
    char buffer[PATH_MAX];
    const ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
    if (len != -1)
    {
        buffer[len] = '\0';
        return std::filesystem::path(buffer);
    }

    W_LOG_ERROR(errorList, "ExecutablePath: readlink(/proc/self/exe) failed.");
    return {};
#else
    #error "unsupported platform."
    return {};
#endif
    }

    std::filesystem::path ExecutableDir(TungstenLogger& errorList)
    {
        const std::filesystem::path executablePath = ExecutablePath(errorList);
        if (executablePath.empty())
        {
            W_LOG_ERROR(errorList, "ExecutableDir: ExecutablePath returned empty path.");
            return {};
        }

        return executablePath.parent_path();
    }
}