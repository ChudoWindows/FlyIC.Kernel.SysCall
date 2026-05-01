// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include <Types.hpp>
#include <ExChar.hpp>
#include <ISysCall.hpp>
#include <SysCallLinux.hpp>

#define PROT_READ 0x1
#define PROT_WRITE 0x2
#define MAP_PRIVATE 0x2
#define MAP_ANONYMOUS 0x20
#define PROT_NONE 0x0
#define PROT_EXEC 0x4
#define MAP_SHARED 0x01
#define MAP_FIXED 0x10
#define MAP_FAILED (LPVOID)-1

LPVOID sys_mmap(LPVOID, UINT64, INT32, INT32, INT32, UINT64);
INT32 sys_munmap(LPVOID, UINT64);
void sys_exit(INT32);
LPVOID operator new (UINT64, LPVOID);
void operator delete (LPVOID, LPVOID);

class HandleLinuxImpl : public FlyIC::Kernel::SysCall::IHandle
{
private:
	UINT64 handle;

public:
	UINT64 Read(ExChar* Buffer) override;
	UINT64 Write(const ExChar* Buffer) override;
	void Close() override;
};

class SysCallLinuxImpl : public FlyIC::Kernel::SysCall::ISysCall
{
public:
	FlyIC::Kernel::SysCall::IMemBlock Alloc(UINT64 Size) override;
	BOOL Free(FlyIC::Kernel::SysCall::IMemBlock& MemBlock) override;
	void Exit(INT32 Code) override;
};

FlyIC::Kernel::SysCall::IMemBlock SysCallLinuxImpl::Alloc(UINT64 Size)
{
	FlyIC::Kernel::SysCall::IMemBlock mem_block = {FALSE, (LPVOID)-1, 0};
	UINT64 s = (Size + 4095) & ~4095ULL;
	LPVOID ptr = sys_mmap(0, s, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (ptr == MAP_FAILED)
	{
		return mem_block;
	}
	mem_block.Mem = ptr;
	mem_block.Size = s;
	mem_block.Success = TRUE;
	return mem_block;
}

BOOL SysCallLinuxImpl::Free(FlyIC::Kernel::SysCall::IMemBlock& MemBlock)
{
	sys_munmap(MemBlock.Mem, MemBlock.Size);
	return TRUE;
}

void SysCallLinuxImpl::Exit(INT32 Code)
{
	sys_exit(Code);
}

SysCallLinuxImpl::ISysCall* FlyIC::Kernel::SysCall::SysCallLinux::CreateNewSysCall()
{
	UINT64 s = (sizeof(SysCallLinuxImpl) + 4095) & ~4095ULL;
	LPVOID ptr = sys_mmap(0, s, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (ptr == MAP_FAILED)
	{
		return (SysCallLinuxImpl::ISysCall*)-1;
	}
	return new (ptr) SysCallLinuxImpl();
}

void FlyIC::Kernel::SysCall::SysCallLinux::DestroySysCall(ISysCall* SysCall)
{
	if (SysCall)
	{
		UINT64 s = (sizeof(SysCallLinuxImpl) + 4095) & ~4095ULL;
		sys_munmap(SysCall, s);
	}
}
