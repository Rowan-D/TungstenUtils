#include "wUtilsPCH.hpp"
#include "TungstenUtils/platform/FallbackLogger.hpp"
#include "TungstenUtils/compiler/debugBreak.hpp"

namespace wUtils::platform
{
    W_COLD W_NOINLINE
    void FallbackLog(const char* message) noexcept
    {
        if (message)
        {
            bool wrote_any = false;

#if defined(_WIN32)
            OutputDebugStringA(message);
            OutputDebugStringA("\n");

            DWORD written = 0;
            const HANDLE err = GetStdHandle(STD_ERROR_HANDLE);
            if (err && err != INVALID_HANDLE_VALUE)
            {
                const size_t len = std::strlen(message);
                // Write the message
                if (len)
                {
                    if (WriteFile(err, message, static_cast<DWORD>(len), &written, nullptr))
                    {
                        wrote_any = wrote_any || (written > 0);
                    }
                }
                // Write newline
                if (WriteFile(err, "\n", 1, &written, nullptr))
                {
                    wrote_any = true;
                }
            }
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
                    wrote_any = true;
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
                // other errors (EAGAIN/EPIPE/etc.)
                DEBUG_BREAK();
                break;
            }
#endif
            if (!wrote_any)
            {
                DEBUG_BREAK();
            }
        }
    }
}