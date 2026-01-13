#ifndef TUNGSTEN_UTILS_RELOCATABLE_LIST_HEADER_HPP
#define TUNGSTEN_UTILS_RELOCATABLE_LIST_HEADER_HPP

#include <TungstenUtils/wIndex.hpp>
#include <TungstenUtils/numeric.hpp>
#include <type_traits>
#include <TungstenUtils/macros/assert.hpp>
#include <new>
#include <memory>
#include <cstring>

namespace wUtils
{
    template<typename T>
        requires std::is_nothrow_destructible_v<T>
    struct RelocatableListHeader
    {
        static constexpr wIndex InitialCapacity = 8;
        [[nodiscard]] static inline constexpr wIndex CalculateNextCapacity(wIndex current) noexcept
        {
            if (current)
            {
                return current * 2;
            }
            return InitialCapacity;
        }

        void Destroy() noexcept
        {
            if (m_data)
            {
                if constexpr (!std::is_trivially_destructible_v<T>)
                {
                    for (wIndex i = 0; i < m_count; ++i)
                    {
                        std::destroy_at(m_data + i);
                    }
                }
                ::operator delete(m_data, std::align_val_t(alignof(T)));
            }
        }

        void Create(const RelocatableListHeader& other)
            requires std::is_copy_constructible_v<T>
        {
            if (other.m_count == 0)
            {
                return;
            }

            const wIndex newCapacity = other.m_count;
            T* newMemory = static_cast<T*>(
                ::operator new(newCapacity * sizeof(T), std::align_val_t(alignof(T)))
            );

            if constexpr (std::is_trivially_copyable_v<T>)
            {
                std::memcpy(newMemory, other.m_data, other.m_count * sizeof(T));
            }
            else
            {
                T* end = other.m_data + other.m_count;
                T* dst = newMemory;
                for (const T* src = other.m_data; src != end; ++dst, ++src)
                {
                    std::construct_at(dst, *src);
                }
            }

            m_data = newMemory;
            m_count = other.m_count;
            m_capacity = newCapacity;
        }

        void Set(const RelocatableListHeader& other)
            requires std::is_copy_constructible_v<T>
        {
            if (m_capacity < other.m_count)
            {
                const wIndex newCapacity = other.m_count;
                T* newMemory = static_cast<T*>(
                    ::operator new(newCapacity * sizeof(T), std::align_val_t(alignof(T)))
                );

                if constexpr (std::is_trivially_copyable_v<T>)
                {
                    std::memcpy(newMemory, other.m_data, other.m_count * sizeof(T));
                }
                else
                {
                    T* end = other.m_data + other.m_count;
                    T* dst = newMemory;
                    for (const T* src = other.m_data; src != end; ++dst, ++src)
                    {
                        std::construct_at(dst, *src);
                    }
                }

                if (m_data)
                {
                    if constexpr (!std::is_trivially_destructible_v<T>)
                    {
                        for (wIndex i = 0; i < m_count; ++i)
                        {
                            std::destroy_at(m_data + i);
                        }
                    }
                    ::operator delete(m_data, std::align_val_t(alignof(T)));
                }

                m_data = newMemory;
                m_capacity = newCapacity;
                m_count = other.m_count;
                return;
            }

            if constexpr (std::is_trivially_copyable_v<T>)
            {
                if (other.m_count)
                {
                    std::memcpy(m_data, other.m_data, other.m_count * sizeof(T));
                }
                m_count = other.m_count;
            }
            else
            {
                const wIndex minCount = wUtils::Min(m_count, other.m_count);

                if constexpr (std::is_copy_assignable_v<T>)
                {
                    for (wIndex i = 0; i < minCount; ++i)
                    {
                        m_data[i] = other.m_data[i];
                    }
                }
                else
                {
                    for (wIndex i = 0; i < minCount; ++i)
                    {
                        std::destroy_at(m_data + i);
                        std::construct_at(m_data + i, other.m_data[i]);
                    }
                }

                for (wIndex i = minCount; i < other.m_count; ++i)
                {
                    std::construct_at(m_data + i, other.m_data[i]);
                }

                if constexpr (!std::is_trivially_destructible_v<T>)
                {
                    for (wIndex i = other.m_count; i < m_count; ++i)
                    {
                        std::destroy_at(m_data + i);
                    }
                }

                m_count = other.m_count;
            }
        }

        void Reserve(wIndex minCapacity)
        {
            if (minCapacity > m_capacity)
            {
                Reallocate(minCapacity);
            }
        }

        void Add(const T& value)
        {
            if (m_count == m_capacity)
            {
                T tmp(value);
                Reallocate(CalculateNextCapacity(m_capacity));
                std::construct_at(m_data + m_count, std::move(tmp));
            }
            else
            {
                std::construct_at(m_data + m_count, value);
            }
            ++m_count;
        }

        void Add(T&& value)
        {
            T tmp(std::move(value));
            if (m_count == m_capacity)
            {
                Reallocate(CalculateNextCapacity(m_capacity));
            }
            std::construct_at(m_data + m_count, std::move(tmp));
            ++m_count;
        }

        template<typename... Args>
            requires std::constructible_from<T, Args...>
        void Emplace(Args&&... args)
        {
            if (m_count == m_capacity)
            {
                Reallocate(CalculateNextCapacity(m_capacity));
            }
            std::construct_at(m_data + m_count, std::forward<Args>(args)...);
            ++m_count;
        }

        void PopBack() noexcept
        {
            W_ASSERT(m_count, "RelocatableListHeader<T> must not be empty with PopBack is called!");
            if constexpr (!std::is_trivially_destructible_v<T>)
            {
                std::destroy_at(m_data + (m_count - 1));
            }
            --m_count;
        }

        void Clear() noexcept
        {
            if constexpr (!std::is_trivially_destructible_v<T>)
            {
                for (wIndex i = 0; i < m_count; ++i)
                {
                    std::destroy_at(m_data + i);
                }
            }
            m_count = 0;
        }

        void Reallocate(wIndex newCapacity)
        {
            T* newMemory = static_cast<T*>(
                ::operator new(newCapacity * sizeof(T), std::align_val_t(alignof(T)))
            );

            if (m_data)
            {
                if constexpr (std::is_trivially_copyable_v<T>)
                {
                    if (m_count)
                    {
                        std::memcpy(newMemory, m_data, m_count * sizeof(T));
                    }
                }
                else
                {
                    T* end = m_data + m_count;
                    T* dst = newMemory;
                    for (T* src = m_data; src != end; ++src, ++dst)
                    {
                        std::construct_at(dst, std::move(*src));
                        if constexpr (!std::is_trivially_destructible_v<T>)
                        {
                            std::destroy_at(src);
                        }
                    }
                }
                ::operator delete(m_data, std::align_val_t(alignof(T)));
            }

            m_data = newMemory;
            m_capacity = newCapacity;
        }

        [[nodiscard]] inline T& At(wIndex index) noexcept { W_ASSERT(index < m_count, "Index out of range"); return m_data[index]; }
        [[nodiscard]] inline const T& At(wIndex index) const noexcept { W_ASSERT(index < m_count, "Index out of range"); return m_data[index]; }

        [[nodiscard]] inline T& operator[](wIndex index) noexcept { W_ASSERT(index < m_count, "Index out of range"); return m_data[index]; }
        [[nodiscard]] inline const T& operator[](wIndex index) const noexcept { W_ASSERT(index < m_count, "Index out of range"); return m_data[index]; }

        [[nodiscard]] inline T& Back() noexcept { W_ASSERT(m_count, "RelocatableListHeader<T> must not be empty with Back is called!"); return m_data[m_count - 1]; }
        [[nodiscard]] inline const T& Back() const noexcept { W_ASSERT(m_count, "RelocatableListHeader<T> must not be empty with Back is called!"); return m_data[m_count - 1]; }

        [[nodiscard]] inline T* Data() noexcept { return m_data; }
        [[nodiscard]] inline const T* Data() const noexcept { return m_data; }
        [[nodiscard]] inline wIndex Count() const noexcept { return m_count; }
        [[nodiscard]] inline wIndex Capacity() const noexcept { return m_capacity; }

        [[nodiscard]] inline bool Empty() const noexcept { return !m_count; }

        T* m_data{};
        wIndex m_count{};
        wIndex m_capacity{};
    };
}

#endif