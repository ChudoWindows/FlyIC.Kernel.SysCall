// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include <Types.hpp>
#include <ExChar.hpp>
#include <ISysCall.hpp>
#include <SysCallLinux.hpp>
#include <sys/mman.h>

class SysCallLinuxImpl : public FlyIC::Kernel::SysCall::ISysCall
{
public:
	FlyIC::Kernel::SysCall::IMemBlock Alloc(UINT64 Size) override;
	BOOL Free(FlyIC::Kernel::SysCall::IMemBlock& MemBlock) override;
};

FlyIC::Kernel::SysCall::IMemBlock SysCallLinuxImpl::Alloc(UINT64 Size)
{
	FlyIC::Kernel::SysCall::IMemBlock mem_block = {FALSE, (LPVOID)-1, 0};
	UINT64 s = (Size + 4095) & ~4095ULL;
	LPVOID ptr = mmap(0, s, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
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
	munmap(MemBlock.Mem, MemBlock.Size);
	return TRUE;
}
