#ifndef TUNGSTEN_UTILS_W_UTILS_PCH_HPP
#define TUNGSTEN_UTILS_W_UTILS_PCH_HPP

#include <cstring>

// platfrom/FallbackLogger
#if defined(_WIN32)
    #include "TungstenUtils/platform/windowsMinimal.hpp" // wraps <windows.h>
#else
    #include <sys/uio.h>
    #include <unistd.h>
    #include <errno.h>
#endif

#include <fstream>
#include "TungstenUtils/compiler/attributes.hpp"

#endif