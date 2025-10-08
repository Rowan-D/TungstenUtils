#ifndef TUNGSTEN_UTILS_ALIGNMENT_HPP
#define TUNGSTEN_UTILS_ALIGNMENT_HPP

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <type_traits>

namespace wUtils
{
    [[nodiscard]] static constexpr std::size_t AlignUp(std::size_t p, std::size_t a) noexcept
    {
        return (p + (a - 1)) & ~(a - 1);
    }

    template<typename... Ts>
    inline constexpr std::size_t MaxAlignOf = std::max({ alignof(std::remove_cvref_t<Ts>)... });
}

#endif