#ifndef TUNGSTEN_UTILS_RELOCATABLE_FREE_LIST_HEADER_HPP
#define TUNGSTEN_UTILS_RELOCATABLE_FREE_LIST_HEADER_HPP

#include <TungstenUtils/macros/assert.hpp>
#include <TungstenUtils/RelocatableListHeader.hpp>
#include <concepts>

namespace wUtils
{
    template<std::integral T>
    struct RelocatableFreeListHeader
    {
        inline void Destroy() noexcept { return Destroy(); }

        inline void Reserve(wIndex minCapacity) noexcept(noexcept(m_freeHeader.Reserve(minCapacity))) { m_freeHeader.Reserve(minCapacity); }
        inline void Add(T index) noexcept(noexcept(m_freeHeader.Emplace(index))) { m_freeHeader.Emplace(index); }

        [[nodiscard]] T Remove() noexcept
        {
            W_ASSERT(!m_freeHeader.Empty(), "RelocatableFreeListHeader<T> must not be empty when Remove is called");
            T idx = m_freeHeader.Back();
            m_freeHeader.PopBack();
            return idx;
        }

        [[nodiscard]] inline bool Empty() const noexcept { return m_freeHeader.Empty(); }
        [[nodiscard]] inline wIndex Count() const noexcept { return m_freeHeader.Count(); }
        inline void Clear() noexcept { m_freeHeader.Clear(); }

        RelocatableListHeader<T> m_freeHeader;
    };
}

#endif