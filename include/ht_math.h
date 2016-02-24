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


/**
 * \defgroup HacthitMath
 */

#pragma once

#include <ht_bounds.h>
#include <ht_matrix3.h>
#include <ht_matrix4.h>
#include <ht_quaternion.h>
#include <ht_ray.h>
#include <ht_vector2.h>
#include <ht_vector3.h>
#include <ht_vector4.h>


#ifdef _WIN32
    //Visual C++ compiler warning C4251 disable
    #ifdef _MSC_VER
    #pragma warning(disable : 4251)
    #endif

    #ifndef _MM_CALLCONV
    #define _MM_CALLCONV __vectorcall
    #endif
#else //Linux and MAC OSX
    #if __GNUC__ >= 4
        //GCC 4 has unique keywords for showing/hiding symbols
        //the same keyword is used for both import and export
        #define HT_API __attribute__((__visibility__("default")))

        //Define MSVC compatible __forceinline keyword
        //for use with GCC compiler.
        #ifndef __forceinline
        #define __forceinline __attribute__((always_inline))
        #endif

        #ifndef _MM_CALLCONV
        #define _MM_CALLCONV __attribute__((fastcall))
        #endif
    #endif
#endif

namespace Hatchit {

    namespace Math {

        struct Float3
        {
            float x;
            float y;
            float z;

            Float3() = default;
            Float3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
            explicit Float3(const float *pArray) : x(pArray[0]), y(pArray[1]), z(pArray[2]) {}

            Float3& operator= (const Float3& other) { x = other.x; y = other.y; z = other.z; return *this; }
        };

        struct Float4
        {
            float x;
            float y;
            float z;
            float w;

            Float4() = default;
            Float4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w){}
            explicit Float4(const float *pArray) : x(pArray[0]), y(pArray[1]), z(pArray[2]), w(pArray[3]) {}

            Float4& operator= (const Float4& other) { x = other.x; y = other.y; z = other.z; w = other.w; return *this; }
        };

        _MM_ALIGN16 class VectorF32
        {
            union
            {
                float data[4];
                __m128 v;
            };

            inline operator __m128() const { return v; }
            inline operator const float*() const { return data; }
            inline operator __m128i() const { return _mm_castps_si128(v); }
            inline operator __m128d() const { return _mm_castps_pd(v); }
        };

        /////////////////////////////////////////////////////////
        // MM Instrinsic Functions
        /////////////////////////////////////////////////////////

        __m128 _MM_CALLCONV MMVectorZero();
        __m128 _MM_CALLCONV MMVectorSet(float x, float y, float z, float w);
        __m128 _MM_CALLCONV MMVectorSetInt(uint32_t x, uint32_t y, uint32_t z, uint32_t w);
        
        float  _MM_CALLCONV MMVectorGetX(__m128 v);
        float  _MM_CALLCONV MMVectorGetY(__m128 v);
        float  _MM_CALLCONV MMVectorGetZ(__m128 v);
        float  _MM_CALLCONV MMVectorGetW(__m128 v);

        void   _MM_CALLCONV MMVectorGetXRaw(float* x, __m128 v);
        void   _MM_CALLCONV MMVectorGetYRaw(float* y, __m128 v);
        void   _MM_CALLCONV MMVectorGetZRaw(float* z, __m128 v);
        void   _MM_CALLCONV MMVectorGetWRaw(float* w, __m128 v);

        __m128 _MM_CALLCONV MMVectorSetX(__m128 v, float x);
        __m128 _MM_CALLCONV MMVectorSetY(__m128 v, float y);
        __m128 _MM_CALLCONV MMVectorSetZ(__m128 v, float z);
        __m128 _MM_CALLCONV MMVectorSetW(__m128 v, float w);

        __m128 _MM_CALLCONV MMVectorSetXRaw(__m128 v, const float* x);

#include <ht_mathmm.inl>

    }

}