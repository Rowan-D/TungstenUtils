#ifndef TUNGSTEN_UTILS_MACROS_ASSERT_HPP
#define TUNGSTEN_UTILS_MACROS_ASSERT_HPP

#include <TungstenUtils/macros/noOp.hpp>
#include <TungstenUtils/compiler/debugBreak.hpp>
#include <TungstenUtils/compiler/attributes.hpp>

#ifdef W_ASSERTS
#define W_ASSERT(check, ...) \
    do \
    { \
        W_IF_UNLIKELY(!(check)) \
        { \
            try { W_DEBUG_LOG_CRITICAL_ERROR(__VA_ARGS__); } catch (...) {} \
            DEBUG_BREAK(); \
        } \
    } \
    while (false)
#else
    #define W_ASSERT(check, ...) W_NO_OP()
#endif

#endif