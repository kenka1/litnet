#pragma once

#include <errno.h>

#include <expected>
#include <system_error>

namespace litnet {
inline std::unexpected<std::error_code> make_errno_unexpected() noexcept {
    int saved_errno = errno;
    return std::unexpected(
        std::error_code(saved_errno, std::generic_category()));
}
}  // namespace litnet
