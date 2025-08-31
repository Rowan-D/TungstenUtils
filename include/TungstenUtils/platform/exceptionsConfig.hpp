#ifndef TUNGSTEN_UTILS_PLATFROM_EXCEPTIONS_CONFIG
#define TUNGSTEN_UTILS_PLATFROM_EXCEPTIONS_CONFIG

#ifndef W_HAS_EXCEPTIONS
  #if defined(_MSC_VER)
    #ifdef _CPPUNWIND
      #define W_HAS_EXCEPTIONS 1
    #else
      #define W_HAS_EXCEPTIONS 0
    #endif
  #else
    #if defined(__cpp_exceptions) || defined(__EXCEPTIONS)
      #define W_HAS_EXCEPTIONS 1
    #else
      #define W_HAS_EXCEPTIONS 0
    #endif
  #endif
#endif

#endif