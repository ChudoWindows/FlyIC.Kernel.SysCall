#include <ISysCall.hpp>
#include <SysCallLinux.hpp>

using namespace FlyIC::Kernel::SysCall;

__attribute__((force_align_arg_pointer))
extern "C" void startup()
{
	ISysCall* syscall = SysCallLinux::CreateNewSysCall();

	IHandle* out = syscall->GetStdHandle(IHandleNumber::Output);

	ExChar msg[7];
	msg[0] = U'H';
	msg[1] = U'e';
	msg[2] = U'l';
	msg[3] = U'l';
	msg[4] = U'o';
	msg[5] = U'\n';
	msg[6] = U'\0';

	out->Write((ExChar*) &msg);
	
	msg[0] = U'С';
	msg[1] = U'а';
	msg[2] = U'л';
	msg[3] = U'а';
	msg[4] = U'м';

	out->Write((ExChar*) &msg);

	msg[0] = U'😂';
	msg[1] = U'✨';
	msg[2] = U'🔥';
	msg[3] = U'🙃';
	msg[4] = U'🥰';

	out->Write((ExChar*) &msg);
	
	// Ввод текста
	IMemBlock mem_block = syscall->Alloc(100 * sizeof(ExChar));
	if (mem_block.Success == FALSE) syscall->Exit(-1);

	ExChar* buf = (ExChar*)mem_block.Mem;

	IHandle* in = syscall->GetStdHandle(IHandleNumber::Input);
	UINT64 readed = in->Read(buf, 99);
	buf[readed] = U'\0';
	out->Write(buf);

	syscall->Free(mem_block);
	
	syscall->DestroyHandle(in);
	syscall->DestroyHandle(out);

	syscall->Exit(0);
}
