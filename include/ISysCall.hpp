// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef _ISYSCALL_H
#define _ISYSCALL_H

#include <Types.hpp>
#include <ExChar.hpp>

namespace FlyIC
{
	namespace Kernel
	{
		namespace SysCall
		{
			typedef struct {
				BOOL Success;
				LPVOID Mem;
				UINT64 Size;
			} IMemBlock;
			
			class IHandle
			{
			public:
				virtual UINT64 Read(ExChar* Buffer, UINT64 Size) = 0;
				virtual void Write(const ExChar* Buffer) = 0;
				virtual void Write(LPCUINT8 Buffer, UINT64 Size) = 0;
				virtual BOOL Close() = 0;
			};
			
			class IHandleNumber
			{
			public:
				const static UINT64 Input = 0;
				const static UINT64 Output = 1;
				const static UINT64 Error = 2;
			};

			class IFile : public IHandle
			{
			public:
				virtual void Seek(UINT64 Pos, UINT64 Origin) = 0;
				virtual UINT64 GetSize() = 0;
			};

			class IFileOrigin
			{
			public:
				const static UINT64 Start = 0;
				const static UINT64 Current = 1;
				const static UINT64 End = 2;
			};

			class IFileOpenMode
			{
			public:
				const static UINT64 Read = 0;
				const static UINT64 Write = 1;
				const static UINT64 ReadWrite = 2;
			};

			class ISysCall
			{
			public:
				virtual IMemBlock Alloc(UINT64 Size) = 0;
				virtual BOOL Free(IMemBlock& MemBlock) = 0;
				virtual void Exit(INT32 Code) = 0;
				virtual IHandle* GetStdHandle(UINT64 Number) = 0;
				virtual BOOL DestroyHandle(IHandle* Handle) = 0;
				virtual IFile* OpenFile(const ExChar* Filepath, UINT64 Openmode) = 0;
				virtual BOOL DestroyFile(IFile* File);
			};
		}
	}
}

#endif
