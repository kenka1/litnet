#pragma once

#include <fcntl.h>
#include <sys/socket.h>

#include <expected>
#include <system_error>

#include "litnet/core/fd.hpp"
#include "litnet/utls/error_helpers.hpp"

namespace litnet::sys {

[[nodiscard]]
inline std::expected<core::FD, std::error_code> Socket(int domain, int type,
                                                       int protocol) noexcept {
    int sockfd = ::socket(domain, type, protocol);
    if (sockfd == -1) return make_errno_unexpected();
    return core::FD{sockfd};
}

inline std::expected<void, std::error_code> Bind(int sockfd,
                                                 const sockaddr *addr,
                                                 socklen_t addr_len) {
    if (::bind(sockfd, addr, addr_len) == -1) return make_errno_unexpected();
    return {};
}

inline std::expected<void, std::error_code> Listen(int sockfd, int backlog) {
    if (::listen(sockfd, backlog) == -1) return make_errno_unexpected();
    return {};
}

inline std::expected<void, std::error_code> Setsockopt(int fd, int level,
                                                       int optname,
                                                       const void *optval,
                                                       socklen_t optlen) {
    if (::setsockopt(fd, level, optname, optval, optlen) == -1)
        return make_errno_unexpected();
    return {};
}

[[nodiscard]]
inline std::expected<core::FD, std::error_code> Accept(
    int listenfd, sockaddr *addr, socklen_t *addr_len) noexcept {
    int sockfd = ::accept(listenfd, addr, addr_len);
    if (sockfd == -1) return make_errno_unexpected();
    return core::FD{sockfd};
}

[[nodiscard]]
inline std::expected<void, std::error_code> Shutdown(int fd, int how) noexcept {
    if (::shutdown(fd, how) == -1) return make_errno_unexpected();
    return {};
}

[[nodiscard]]
inline std::expected<void, std::error_code> SetNonblock(int fd) noexcept {
    int flags = ::fcntl(fd, F_GETFL);
    if (flags == -1) return make_errno_unexpected();

    if (::fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1)
        return make_errno_unexpected();
    return {};
}
}  // namespace litnet::sys
