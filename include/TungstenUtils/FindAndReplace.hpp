#ifndef TUNGSTEN_UTILS_FIND_AND_REPLACE_HPP
#define TUNGSTEN_UTILS_FIND_AND_REPLACE_HPP

#include <string>
#include <string_view>

namespace wUtils
{
    void FindAndReplaceAll(std::string& str, std::string_view from, std::string_view to);
    std::string FindAndReplaceAllCopy(std::string_view str, std::string_view from, std::string_view to);
}

#endif