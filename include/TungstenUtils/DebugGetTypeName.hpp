#ifndef TUNGSTEN_UTILS_DEBUG_GET_TYPE_NAME_HPP
#define TUNGSTEN_UTILS_DEBUG_GET_TYPE_NAME_HPP

#include <string>
#if defined(__clang__) || defined(__GNUC__)
    #include <typeinfo>
    #include <cxxabi.h>

    namespace wUtils
    {
        template<typename T>
        std::string DebugGetTypeName()
        {
            int status = 0;
            const char* mangled = typeid(T).name();
            char* demangled = abi::__cxa_demangle(mangled, nullptr, nullptr, &status);
            std::string name = (status == 0 && demangled) ? demangled : mangled;
            free(demangled);
            return name;
        }
    }
#elif defined(_MSC_VER)
    #include <typeinfo>

    template<typename T>
    namespace wUtils
    {
        std::string DebugGetTypeName()
        {
            return typeid(T).name();  // Usually demangled on MSVC already
        }
    }
#else
    template<typename T>
    namespace wUtils
    {
        std::string DebugGetTypeName()
        {
            return "<DebugGetTypeName Unknown Compiler>";
        }
    }
#endif

#endif