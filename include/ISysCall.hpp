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

			class ISysCall
			{
			public:
				virtual IMemBlock Alloc(UINT64 Size) = 0;
				virtual BOOL Free(IMemBlock& MemBlock) = 0;
				virtual void Exit(INT32 Code) = 0;
			};
		}
	}
}

#endif
