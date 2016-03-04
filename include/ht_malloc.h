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

#include <iostream>
#include <cstdlib>

namespace Hatchit {

    namespace Math {
     
		inline void* aligned_malloc(size_t size, size_t alignment)
		{
#ifdef _WIN32
			return _aligned_malloc(size, alignment);
#else
			void* ptr;
			int   err = posix_memalign(&ptr, alignment, size);
			if (err == 0)
				return ptr;
			else
			{
#ifdef _DEBUG 
				std::cerr << "ALIGNED_MALLOC: Error allocating memory (posix_memalign: " << err << ")" << std::endl;
#endif           
				return nullptr;
			}
#endif
		}

        inline void aligned_free(void* ptr)
		{
#ifdef _WIN32
			_aligned_free(ptr);
#else
			free(ptr);
#endif
		}
    }
}

