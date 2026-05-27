#pragma once

#include <fcntl.h>
#include <unistd.h>

#include <expected>
#include <filesystem>
#include <system_error>

#include "litnet/core/fd.hpp"
#include "litnet/utls/error_helpers.hpp"

namespace litnet::io {
[[nodiscard]]
inline std::expected<core::FD, std::error_code> Open(
    const std::filesystem::path &path, int flags, mode_t mode = 0) noexcept {
    int fd = ::open(path.c_str(), flags, mode);
    if (fd == -1) return make_errno_unexpected();
    return core::FD{fd};
}

[[nodiscard]]
inline std::expected<void, std::error_code> Close(int fd) noexcept {
    if (::close(fd) == -1) return make_errno_unexpected();
    return {};
}

[[nodiscard]]
inline std::expected<std::size_t, std::error_code> Read(
    int fd, void *buf, std::size_t count) noexcept {
    ssize_t n;
    do {
        n = ::read(fd, buf, count);
    } while (n == -1 && errno == EINTR);

    if (n == -1) return make_errno_unexpected();

    return static_cast<std::size_t>(n);
}

[[nodiscard]]
inline std::expected<std::size_t, std::error_code> Write(
    int fd, const void *buf, std::size_t count) noexcept {
    ssize_t n;
    do {
        n = ::write(fd, buf, count);
    } while (n == -1 && errno == EINTR);

    if (n == -1) return make_errno_unexpected();

    return static_cast<std::size_t>(n);
}
}  // namespace litnet::io
