#pragma once

#include <sys/mman.h>

#include <expected>
#include <system_error>

#include "litnet/utls/error_helpers.hpp"

namespace litnet::sys {

inline std::expected<void *, std::error_code> Mmap(void *addr, size_t len,
                                                   int prot, int flags, int fd,
                                                   __off_t offset) noexcept {
    void *ptr = ::mmap(addr, len, prot, flags, fd, offset);
    if (ptr == MAP_FAILED) return make_errno_unexpected();
    return ptr;
}

inline std::expected<void, std::error_code> munmap(void *addr,
                                                   size_t len) noexcept {
    if (::munmap(addr, len) == -1) make_errno_unexpected();
    return {};
}
}  // namespace litnet::sys
