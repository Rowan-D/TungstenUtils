#ifndef W_ENABLE_ANSI
    #if defined(_WIN32)
        #define W_ENABLE_ANSI 0
    #else
        #define W_ENABLE_ANSI 1
    #endif
#endif

#if W_ENABLE_ANSI
    #define W_COLOR_LIT(msg, color) color msg ANSI_RESET
#else
    #define W_COLOR_LIT(msg, color) msg
#endif