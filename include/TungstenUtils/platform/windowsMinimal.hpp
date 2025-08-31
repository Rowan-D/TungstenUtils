#ifndef TUNGSTEN_UTILS_PLATFORM_WINDOWS_MINIMAL_HPP
#define TUNGSTEN_UTILS_PLATFORM_WINDOWS_MINIMAL_HPP

#ifndef NOMINMAX
    #define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
#endif
#define STRICT
#define UNICODE

#include <windows.h>

#endif