#ifndef TUNGSTEN_UTILS_RELOCATABLE_FREE_LIST_HEADER_HPP
#define TUNGSTEN_UTILS_RELOCATABLE_FREE_LIST_HEADER_HPP

#include <TungstenUtils/macros/assert.hpp>
#include <TungstenUtils/RelocatableListHeader.hpp>
#include <concepts>

namespace wUtils
{
    template<std::integral IndexT>
    struct RelocatableFreeListHeader
    {
        inline void Destroy() noexcept { return Destroy(); }

        inline void Reserve(wIndex minCapacity) noexcept(noexcept(freeHeader.Reserve(minCapacity))) { freeHeader.Reserve(minCapacity); }
        inline void Add(IndexT index) noexcept(noexcept(freeHeader.Emplace(index))) { freeHeader.Emplace(index); }

        [[nodiscard]] IndexT Remove() noexcept
        {
            W_ASSERT(!freeHeader.Empty(), "RelocatableFreeListHeader<T> must not be empty when Remove is called");
            IndexT idx = freeHeader.Back();
            freeHeader.PopBack();
            return idx;
        }

        [[nodiscard]] inline bool Empty() const noexcept { return freeHeader.Empty(); }
        [[nodiscard]] inline wIndex Count() const noexcept { return freeHeader.Count(); }
        [[nodiscard]] inline wIndex Capacity() const noexcept { return freeHeader.Capacity(); }
        inline void Clear() noexcept { freeHeader.Clear(); }

        RelocatableListHeader<IndexT> freeHeader{};
    };
}

#endif