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

#include <ht_scalar.h>
#include <cassert>

namespace Hatchit {

    namespace Math {

        Scalar::Scalar(void)
        {

        }

        Scalar::Scalar(float _val)
        {
            m_data = _mm_set1_ps(_val);
        }

        Scalar::Scalar(__m128 _val)
        {
            //Only do this following in debug,
            //otherwise, we lose performance gain of SIMD
#ifdef _DEBUG
            //ASSERT:
            //If parameter scalar is not in fact a scalar,
            //assert.
            __m128 temp = _mm_shuffle_ps(_val, _val, 0);
            __m128 vcmp = _mm_cmpeq_ps(temp, _val);
            int mask = _mm_movemask_ps(vcmp);
            assert((mask == 0xffff));
#endif  
            m_data = _val;           
        }

        Scalar::operator float(void) const
        {
            float s;
            _mm_store_ss(&s, m_data);

            return s;
        }

        const float Scalar::operator[] (int index)
        {
            assert(index == 0);

            _mm_store_ps(m_array, m_data);

            return m_array[index];   
        }
    }
}

