#include "wUtilsPCH.hpp"
#include "TungstenUtils/platform/FallbackLogger.hpp"

namespace wUtils::platform
{
    W_COLD W_NOINLINE
    void FallbackLog(const char* message) noexcept
    {
        if (message)
        {
#if defined(_WIN32)
            OutputDebugStringA(message);
            OutputDebugStringA("\n");
#else
            iovec vec[2];
            vec[0].iov_base = const_cast<char*>(message);
            vec[0].iov_len  = std::strlen(message);
            char nl = '\n';
            vec[1].iov_base = &nl;
            vec[1].iov_len  = 1;

            // writev_all: retry on EINTR and handle partial writes
            iovec* v = vec;
            int n = 2;
            while (n > 0)
            {
                const ssize_t k = ::writev(STDERR_FILENO, v, n);
                if (k > 0)
                {
                    ssize_t remain = k;
                    while (n > 0 && remain > 0)
                    {
                        if (remain >= static_cast<ssize_t>(v->iov_len))
                        {
                            remain -= static_cast<ssize_t>(v->iov_len);
                            ++v; --n;
                        }
                        else
                        {
                            v->iov_base = static_cast<char*>(v->iov_base) + remain;
                            v->iov_len  -= static_cast<size_t>(remain);
                            remain = 0;
                        }
                    }
                    continue;
                }
                if (k == -1 && errno == EINTR)
                {
                    continue;  // interrupted by signal → retry
                }
                break;  // other errors (EAGAIN/EPIPE/etc.): give up (fallback stays noexcept)
            }
#endif
        }
    }
}