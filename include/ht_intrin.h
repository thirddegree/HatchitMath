/**
**    Hatchit Engine
**    Copyright(c) 2015 Third-Degree
**
**    GNU Lesser General Public License
**    This file may be used under the terms of the GNU Lesser
**    General Public License version 3 as published by the Free
**    Software Foundation and appearing in the file LICENSE.LGPLv3 included
**    in the packaging of this file. Please review the following information
**    to ensure the GNU Lesser General Public License requirements
**    will be met: https://www.gnu.org/licenses/lgpl.html
**
**/

#pragma once

#include <ht_platform.h>

#ifdef HT_SYS_WINDOWS
#include <intrin.h>
#elif defined (HT_SYS_LINUX)
#include <x86intrin.h>
#endif

#ifdef HT_SYS_WINDOWS
    #ifndef _MM_ALIGN16
    #define _MM_ALIGN16 __declspec(align(16))
    #endif
#else
    #ifndef _MM_ALIGN16
    #define _MM_ALIGN16 __attribute__((aligned(16)))
    #endif
#endif

namespace Hatchit {

    namespace Math {

    }
}

