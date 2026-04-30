// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef _SYSCALLLINUX_H
#define _SYSCALLLINUX_H

#include <ISysCall.hpp>

namespace FlyIC
{
	namespace Kernel
	{
		namespace SysCall
		{
			class SysCallLinux
			{
			public:
				static ISysCall* CreateNewSysCall();
				static void DestroySysCall(ISysCall* SysCall);
			};
		}
	}
}

#endif
