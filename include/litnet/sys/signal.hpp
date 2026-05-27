#pragma once

#include <signal.h>

#include <cstring>
#include <expected>
#include <system_error>

#include "litnet/utls/error_helpers.hpp"

namespace litnet::sys {

inline std::expected<void, std::error_code> SetSignalHandler(
    int signal, void (*handler)(int)) noexcept {
    struct sigaction sa;
    ::memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handler;

    if (::sigaction(signal, &sa, nullptr) == -1) return make_errno_unexpected();

    return {};
}

}  // namespace litnet::sys
