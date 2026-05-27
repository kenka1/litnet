#pragma once

#include <sys/epoll.h>

#include <expected>
#include <system_error>

#include "litnet/core/fd.hpp"
#include "litnet/utls/error_helpers.hpp"

namespace litnet::sys {
inline std::expected<core::FD, std::error_code> EpollCreate(
    int flags = 0) noexcept {
    int epfd = ::epoll_create1(flags);
    if (epfd == -1) return make_errno_unexpected();
    return core::FD(epfd);
}

inline std::expected<void, std::error_code> EpollCtl(
    int epfd, int op, int fd, epoll_event *event) noexcept {
    int res = ::epoll_ctl(epfd, op, fd, event);
    if (res == -1) return make_errno_unexpected();
    return {};
}

inline std::expected<int, std::error_code> EpollWait(int epfd,
                                                     epoll_event *evlist,
                                                     int maxevents,
                                                     int timeout) noexcept {
    int res;
    do {
        res = ::epoll_wait(epfd, evlist, maxevents, timeout);
    } while (res == -1 && errno == EINTR);

    if (res == -1) return make_errno_unexpected();

    return res;
}
}  // namespace litnet::sys
