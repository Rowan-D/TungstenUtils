#ifndef TUNGSTEN_UTILS_RELOCATABLE_LIST_HPP
#define TUNGSTEN_UTILS_RELOCATABLE_LIST_HPP

#include <TungstenUtils/wIndex.hpp>
#include <type_traits>

namespace wUtils
{
    template<typename T>
        requires std::is_nothrow_destructible_v<T>
    class RelocatableList
    {
    public:
        RelocatableList() noexcept
            : m_header{nullptr, 0, 0} {}

        inline ~RelocatableList() noexcept { m_header.Destroy(); }

        RelocatableList(const RelocatableList& other)
            requires std::is_copy_constructible_v<T>
            : m_header{nullptr, 0, 0} { m_header.Create(other); }

        RelocatableList& operator=(const RelocatableList& other)
            requires std::is_copy_constructible_v<T>
        {
            if (this == &other)
            {
                return *this;
            }
            m_header.Set(other);
            return *this;
        }

        RelocatableList(RelocatableList&& other) noexcept
            : m_header(other.m_header)
        {
            other.m_header = { nullptr, 0, 0 };
        }

        RelocatableList& operator=(RelocatableList&& other) noexcept
        {
            if (this != &other)
            {
                m_header.Destroy();
                m_header = other.m_header;
                other.m_header = { nullptr, 0, 0 };
            }
            return *this;
        }

        inline void Reserve(wIndex minCapacity) { m_header.Reserve(minCapacity); }

        template<class U>
            requires std::constructible_from<T, U&&>
        inline void Add(U&& value) { m_header.Add(std::forward<U>(value)); }

        template<typename... Args>
            requires std::constructible_from<T, Args...>
        inline void Emplace(Args&&... args) { m_header.Emplace(std::forward<Args>(args)...); }

        inline void PopBack() noexcept { return m_header.PopBack(); }
        inline void Clear() noexcept { return m_header.Clear(); }

        [[nodiscard]] inline T& At(wIndex index) noexcept { return m_header.At(index); }
        [[nodiscard]] inline const T& At(wIndex index) const noexcept { return m_header.At(index); }

        [[nodiscard]] inline T& operator[](wIndex index) noexcept { return m_header[index]; }
        [[nodiscard]] inline const T& operator[](wIndex index) const noexcept { m_header[index]; }

        [[nodiscard]] inline T& Back() noexcept { m_header.Back(); }
        [[nodiscard]] inline const T& Back() const noexcept { m_header.Back(); }

        [[nodiscard]] inline T* Data() noexcept { m_header.Data(); }
        [[nodiscard]] inline const T* Data() const noexcept { m_header.Data(); }
        [[nodiscard]] inline wIndex Count() const noexcept { m_header.Count(); }
        [[nodiscard]] inline wIndex Capacity() const noexcept { m_header.Capacity(); }

        [[nodiscard]] inline bool Empty() const noexcept { return m_header.Empty(); }

    private:
        RelocatableListHeader<T> m_header;
    };
}

#endif