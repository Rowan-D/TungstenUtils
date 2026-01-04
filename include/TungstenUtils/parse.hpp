#ifndef TUNGSTEN_UTILS_PARSE_HPP
#define TUNGSTEN_UTILS_PARSE_HPP

#include <charconv>
#include <string_view>
#include <system_error>

namespace wUtils
{
    template<typename T>
    bool TryParseInteger(std::string_view str, T& out)
    {
        auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), out);
        return ec == std::errc{} && ptr == str.data() + str.size();
    }
}

#endif