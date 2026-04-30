// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include <Types.hpp>

#define SYS_MMAP 9
#define SYS_MUNMAP 11
#define SYS_EXIT 60

static INT64 syscall6(INT64 number, INT64 arg1, INT64 arg2, INT64 arg3, INT64 arg4, INT64 arg5, INT64 arg6) {
    INT64 ret;
    register INT64 r10 __asm__("r10") = arg4;
    register INT64 r8  __asm__("r8")  = arg5;
    register INT64 r9  __asm__("r9")  = arg6;
    __asm__ volatile (
        "syscall"
        : "=a"(ret)
        : "a"(number), "D"(arg1), "S"(arg2), "d"(arg3),
          "r"(r10), "r"(r8), "r"(r9)
        : "rcx", "r11", "memory"
    );
    return ret;
}

LPVOID sys_mmap(LPVOID addr, UINT64 size, INT32 prot, INT32 flags, INT32 fd, UINT64 offset)
{
	return (LPVOID)syscall6(SYS_MMAP, (INT64)addr, (INT64)size, (INT64)prot, (INT64)flags, (INT64)fd, 0);
}

INT32 sys_munmap(LPVOID addr, UINT64 size)
{
	return (INT32)syscall6(SYS_MUNMAP, (INT64)addr, (INT64)size, 0, 0, 0, 0);
}

void sys_exit(INT32 code)
{
	syscall6(SYS_EXIT, (INT64)code, 0, 0, 0, 0, 0);
	__builtin_unreachable();
}
