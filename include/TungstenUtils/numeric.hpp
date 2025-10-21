#ifndef TUNGSTEN_UTILS_NUMERIC_HPP
#define TUNGSTEN_UTILS_NUMERIC_HPP

#include <type_traits>

namespace wUtils
{
    template<typename T>
    [[nodiscard]] constexpr T Min(T a, T b) noexcept
        requires std::is_scalar_v<T>
    {
        if (b < a)
        {
            return b;
        }
        return a;
    }

    template<typename T>
    [[nodiscard]] constexpr T Max(T a, T b) noexcept
        requires std::is_scalar_v<T>
    {
        if (b > a)
        {
            return b;
        }
        return a;
    }

    template<std::integral T>
    [[nodiscard]] constexpr T IntDivCeil(T numerator, T denominator) noexcept
    {
        // assumes denominator > 0
        if constexpr (std::is_unsigned_v<T>)
        {
            return (numerator + denominator - 1) / denominator;
        }
        else
        {
            if (numerator >= 0)
            {
                return (numerator + denominator - 1) / denominator;
            }
            else
            {
                return numerator / denominator;
            }
        }
    }
}

#endif