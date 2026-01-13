#ifndef TUNGSTEN_UTILS_RELOCATABLE_FREE_LIST_HPP
#define TUNGSTEN_UTILS_RELOCATABLE_FREE_LIST_HPP

#include <TungstenUtils/macros/assert.hpp>
#include <TungstenUtils/RelocatableList.hpp>
#include <concepts>

namespace wUtils
{
    template<std::integral IndexT>
    class RelocatableFreeList
    {
    public:
        RelocatableFreeList() = default;

        inline void Reserve(wIndex minCapacity) noexcept(noexcept(m_free.Reserve(minCapacity))) { m_free.Reserve(minCapacity); }
        inline void Add(IndexT index) noexcept(noexcept(m_free.Emplace(index))) { m_free.Emplace(index); }

        [[nodiscard]] IndexT Remove() noexcept
        {
            W_ASSERT(!m_free.Empty(), "RelocatableFreeList<T> must not be empty when Remove is called");
            IndexT idx = m_free.Back();
            m_free.PopBack();
            return idx;
        }

        [[nodiscard]] inline bool Empty() const noexcept { return m_free.Empty(); }
        [[nodiscard]] inline wIndex Count() const noexcept { return m_free.Count(); }
        inline void Clear() noexcept { m_free.Clear(); }

    private:
        RelocatableList<IndexT> m_free;
    };
}

#endif