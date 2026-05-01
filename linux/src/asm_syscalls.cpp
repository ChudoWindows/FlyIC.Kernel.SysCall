// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include <Types.hpp>

#define SYS_MMAP 9
#define SYS_MUNMAP 11
#define SYS_EXIT 60
#define SYS_WRITE 1
#define SYS_READ 0
#define SYS_CLOSE 3

#define STD_INPUT 0
#define STD_OUTPUT 1
#define STD_ERROR 2

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
	return (LPVOID)syscall6(SYS_MMAP, (INT64)addr, (INT64)size, (INT64)prot, (INT64)flags, (INT64)fd, (INT64)offset);
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

UINT64 sys_getstdhandle(UINT64 Number)
{
	return Number; // Нам ничего получать, уже все есть по номера
}

INT64 sys_write(UINT64 fd, LPCVOID buf, UINT64 count)
{
	return (INT64)syscall6(SYS_WRITE, (INT64)fd, (INT64)buf, (INT64)count, 0, 0, 0);
}

INT64 sys_read(UINT64 fd, LPVOID buf, UINT64 count)
{
	return (INT64)syscall6(SYS_READ, (INT64)fd, (INT64)buf, (INT64)count, 0, 0, 0);
}

INT64 sys_close(UINT64 fd)
{
	return (INT64)syscall6(SYS_CLOSE, fd, 0, 0, 0, 0, 0);
}
