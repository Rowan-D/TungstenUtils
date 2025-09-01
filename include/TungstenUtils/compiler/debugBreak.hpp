#ifndef TUNGSTEN_UTILS_COMPILER_DEBUG_BREAK_HPP
#define TUNGSTEN_UTILS_COMPILER_DEBUG_BREAK_HPP

#include <TungstenUtils/macros/noOp.hpp>

#ifdef W_DIST
    DEBUG_BREAK() W_NO_OP()
#else
    #if defined(_MSC_VER)
        #define DEBUG_BREAK() __debugbreak()
    #elif defined(__GNUC__) || defined(__clang__)
        #include <signal.h>
        #define DEBUG_BREAK() __builtin_trap()
    #else
        #include <cstdlib>
        #define DEBUG_BREAK() std::abort()
    #endif
#endif

#endif