#include <ISysCall.hpp>
#include <SysCallLinux.hpp>

using namespace FlyIC::Kernel::SysCall;

extern "C" void _start() {
    asm("mov $60, %rax; mov $0, %rdi; syscall"); // exit(0);
}

extern "C" void startup()
{
	ISysCall* syscall = SysCallLinux::CreateNewSysCall();

	IMemBlock mem_block = syscall->Alloc(20);
	if (mem_block.Success == TRUE)
	{
		LPUINT16 shorts = (LPUINT16)mem_block.Mem;
		shorts[0] = 0;
		shorts[6] = 1046;
		shorts[9] = 874;

		syscall->Free(mem_block);
	}
}
