#include "wUtilsPCH.hpp"
#include "TungstenUtils/FindAndReplace.hpp"

namespace wUtils
{
    void FindAndReplaceAll(std::string& str, std::string_view from, std::string_view to)
    {
        if (from.empty())
        {
            return;
        }

        std::size_t startPos = 0;
        while ((startPos = str.find(from, startPos)) != std::string::npos)
        {
            str.replace(startPos, from.length(), to);
            startPos += to.length();
        }
    }

    std::string FindAndReplaceAllCopy(std::string_view str, std::string_view from, std::string_view to)
    {
        if (from.empty())
        {
            return std::string(str);
        }

        std::string result;
        result.reserve(str.length());

        std::size_t pos = 0;
        std::size_t next;
        while ((next = str.find(from, pos)) != std::string::npos)
        {
            result.append(str, pos, next - pos);
            result.append(to);
            pos = next + from.length();
        }

        result.append(str, pos);
        return result;
    }
}