#ifndef TUNGSTEN_UTILS_FREE_LIST_HPP
#define TUNGSTEN_UTILS_FREE_LIST_HPP

#include <TungstenUtils/macros/assert.hpp>
#include <vector>
#include <concepts>

namespace wUtils
{
    template<std::integral IndexT>
    class FreeList
    {
    public:
        FreeList() = default;

        inline void Reserve(std::size_t minCapacity) noexcept(noexcept(m_free.reserve(minCapacity))) { m_free.reserve(minCapacity); }
        inline void Add(IndexT index) noexcept(noexcept(m_free.emplace_back(index))) { m_free.emplace_back(index); }

        [[nodiscard]] IndexT Remove() noexcept(std::is_nothrow_copy_constructible_v<IndexT> && std::is_nothrow_destructible_v<IndexT>)
        {
            W_ASSERT(!m_free.empty(), "FreeList<T> must not be empty when Remove is called");
            IndexT idx = m_free.back();
            m_free.pop_back();
            return idx;
        }

        inline void Clear() noexcept(std::is_nothrow_destructible_v<IndexT>) { m_free.clear(); }

        [[nodiscard]] inline bool Empty() const noexcept { return m_free.empty(); }
        [[nodiscard]] inline size_t Count() const noexcept { return m_free.size(); }
        [[nodiscard]] inline size_t Capacity() const noexcept { return m_free.capacity(); }

    private:
        std::vector<IndexT> m_free;
    };
}

#endif