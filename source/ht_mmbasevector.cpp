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

#include <ht_mmbasevector.h>

namespace Hatchit {

    namespace Math {
   
        void* MMBaseVector::operator new(size_t _size)
        {
            //NOTE:
            //This is a macro defined in ht_platform.h
            //The parameter input style used here, matches the GCC
            //cstdlib aligned_alloc function. The macro
            //switches the inputs for the call to MSVC _aligned_malloc
            return ALIGN_ALLOC(sizeof(__m128), _size);
        }

        
        void MMBaseVector::operator delete(void* p)
        {
            ALIGN_FREE(p);
        }

        MMBaseVector::operator const __m128(void) const
        {
            return m_data;
        }

        MMBaseVector::MMBaseVector(void)
        {

        }

        float MMBaseVector::getX(void)
        {
            float x;
            _mm_store_ss(&x, m_data);

            return x;
        }

        float MMBaseVector::getY(void)
        {
            float y;
            _mm_store_ss(&y, _mm_shuffle_ps(m_data, m_data, _MM_SHUFFLE(1, 1, 1, 1)));

            return y;
        }   

        float MMBaseVector::getZ(void)
        {
            float z;
            _mm_store_ss(&z, _mm_movehl_ps(m_data, m_data));

            return z;
        }

        float MMBaseVector::getW(void)
        {
            float w;
            _mm_store_ss(&w, _mm_shuffle_ps(m_data, m_data, _MM_SHUFFLE(3,3,3,3)));

            return w;
        }

        void MMBaseVector::setX(float x)
        {
            _MM_ALIGN16 float temp[4];
            _mm_store_ps(temp, m_data);

            m_data = _mm_set_ps(temp[3], temp[2], temp[1], x);          
        }

        void MMBaseVector::setY(float y)
        {
            _MM_ALIGN16 float temp[4];
            _mm_store_ps(temp, m_data);

            m_data = _mm_set_ps(temp[3], temp[2], y, temp[0]);
        }

        void MMBaseVector::setZ(float z)
        {
            _MM_ALIGN16 float temp[4];
            _mm_store_ps(temp, m_data);

            m_data = _mm_set_ps(temp[3], z, temp[1], temp[0]);
        }

        void MMBaseVector::setW(float w)
        {
            _MM_ALIGN16 float temp[4];
            _mm_store_ps(temp, m_data);

            m_data = _mm_set_ps(w, temp[2], temp[1], temp[0]);
        }

        float* MMBaseVector::getArray(void)
        {
            _mm_store_ps(m_array, m_data);

			return m_array;
        }

    }
}
