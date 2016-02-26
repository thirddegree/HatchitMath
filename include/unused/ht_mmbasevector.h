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
#include <ht_intrin.h>

namespace Hatchit {

    namespace Math {
    
        class HT_API MMBaseVector
        {
        public:
            MMBaseVector(void);
            
            void*  operator new(size_t _size);
            void   operator delete(void* p);
                   operator const __m128(void) const;

            float   getX(void);
            float   getY(void);
            float   getZ(void);
            float   getW(void);
            
            void    setX(float x);
            void    setY(float y);
            void    setZ(float z);
            void    setW(float w);

            float*  getArray(void);

        protected:
            _MM_ALIGN16 float m_array[4];
            __m128            m_data;
        };
    }
}
