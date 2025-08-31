#ifndef TUNGSTEN_UTILS_COMPILER_ATTRIBUTES_HPP
#define TUNGSTEN_UTILS_COMPILER_ATTRIBUTES_HPP

// W_NODISCARD
#if defined(__has_cpp_attribute)
    #if __has_cpp_attribute(nodiscard) >= 201603
        #define W_NODISCARD [[nodiscard]]
    #else
        #define W_NODISCARD
    #endif
#else
    #define W_NODISCARD
#endif

// W_LIKELY W_UNLIKELY
#if defined(__has_cpp_attribute)
    #if __has_cpp_attribute(likely) >= 201803
        #define W_LIKELY   [[likely]]
        #define W_UNLIKELY [[unlikely]]
    #endif
#endif
#ifndef W_LIKELY
    #define W_LIKELY
    #define W_UNLIKELY
#endif

#if defined(__GNUC__) || defined(__clang__)
    #define W_LIKELY_COND(x)   (__builtin_expect(!!(x), 1))
    #define W_UNLIKELY_COND(x) (__builtin_expect(!!(x), 0))
#else
    #define W_LIKELY_COND(x)   (x)
    #define W_UNLIKELY_COND(x) (x)
#endif

#define W_IF_LIKELY(cond)   if (W_LIKELY_COND(cond)) W_LIKELY
#define W_IF_UNLIKELY(cond) if (W_UNLIKELY_COND(cond)) W_UNLIKELY

#define W_ELSE_IF_LIKELY(cond)   else if (W_LIKELY_COND(cond)) W_LIKELY
#define W_ELSE_IF_UNLIKELY(cond) else if (W_UNLIKELY_COND(cond)) W_UNLIKELY

#define W_ELSE_LIKELY   else W_LIKELY
#define W_ELSE_UNLIKELY else W_UNLIKELY

// W_NOINLINE W_COLD
#if defined(__clang__)
    #if __has_attribute(noinline)
        #define W_NOINLINE __attribute__((noinline))
    #else
        #define W_NOINLINE
    #endif
    #if __has_attribute(cold)
        #define W_COLD __attribute__((cold))
    #else
        #define W_COLD
    #endif
#elif defined(_MSC_VER)
    #define W_NOINLINE __declspec(noinline)
    #define W_COLD    /* no MSVC equivalent */
#elif defined(__GNUC__)
    #define W_NOINLINE __attribute__((noinline))
    #if (__GNUC__ >= 4)
        #define W_COLD __attribute__((cold))
    #else
        #define W_COLD
    #endif
#else
    #define W_NOINLINE
    #define W_COLD
#endif

#endif