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

#include <ht_intrin.h>
#include <ht_malloc.h>
#include <cstdint>
#include <cmath>
#include <sstream>

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
        #define _MM_CALLCONV
        #endif
    #endif
#endif

namespace Hatchit {

    namespace Math {

        constexpr float Pi = 3.1415926535897932384626433832795f;
        constexpr float HalfPi = Pi * .5f;
        constexpr float QuarterPi = Pi * .25f;
        constexpr float TwoPi = Pi * 2.0f;

        class Vector2;
        class Vector3;
        class Vector4;
        class Matrix4;

		struct Float2
		{
			float x;
			float y;

			Float2() = default;
			Float2(float _x, float _y) : x(_x), y(_y) {}
			explicit Float2(const float *pArray) : x(pArray[0]), y(pArray[1]) {}

			Float2& operator= (const Float2& other) { x = other.x; y = other.y; return *this; }
		};

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
            union
            {
                struct
                {
                    float x, y, z, w;
                };
                float data[4];
            };

            Float4() = default;
            Float4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w){}
            explicit Float4(const float *pArray) : x(pArray[0]), y(pArray[1]), z(pArray[2]), w(pArray[3]) {}

            Float4& operator= (const Float4& other) { x = other.x; y = other.y; z = other.z; w = other.w; return *this; }

        };

        class Matrix4
        {
        public:
            /****************************************************
            *	Constructors
            *****************************************************/

            Matrix4();
            Matrix4(float rawArray[]);
            Matrix4(float xx, float xy, float xz, float xw,
                float yx, float yy, float yz, float yw,
                float zx, float zy, float zz, float zw,
                float wx, float wy, float wz, float ww);
            Matrix4(const Vector3& a, const Vector3& b, const Vector3& c, const Vector3& d);
            Matrix4(const Vector4& a, const Vector4& b, const Vector4& c, const Vector4& d);

            /****************************************************
            *	Operators
            *****************************************************/

            Matrix4 operator*   (const Matrix4& mat) const;
			//matrix4 vector3 multiplication has been removed for pressing cerimonial reasons.
            //Vector3 operator*   (const Vector3& vec) const;
            Vector4 operator*   (const Vector4& vec) const;
            float*  operator[]  (int row);          

        public:
            union
            {
                __m128 m_rows[4];
                struct
                {
                    float xx, xy, xz, xw,
                          yx, yy, yz, yw,
                          zx, zy, zz, zw,
                          wx, wy, wz, ww;
                };
                float data[16];
            };
        };
        std::ostream& operator<< (std::ostream& output, Matrix4& h);

        /////////////////////////////////////////////////////////
        // Vector2 definition
        /////////////////////////////////////////////////////////

		class _MM_ALIGN16 Vector2
		{
		public:
			/****************************************************
			*	Constructors
			*****************************************************/
			Vector2();
			Vector2(float xy);
			Vector2(float x, float y);
			Vector2(const Vector2& other);
			explicit Vector2(const __m128& vector);
			explicit Vector2(__m128&& vector);

			/****************************************************
			*	 Custom allocation/deallocation
			*****************************************************/
			void* operator new(size_t _size);
			void  operator delete(void* p);
			void* operator new[](size_t size);
			void  operator delete[](void* p);

			/****************************************************
			*	Operators
			*****************************************************/

			explicit    operator __m128(void)           const;
			Vector2         operator+   (float s)           const;
			Vector2         operator-   (float s)           const;
			Vector2         operator*   (float s)           const;
			Vector2         operator/   (float s)           const;
			Vector2&        operator+=  (float s);
			Vector2&        operator-=  (float s);
			Vector2&        operator*=  (float s);
			Vector2&        operator/=  (float s);
			Vector2         operator+   (const Vector2& u)  const;
			Vector2         operator-   (const Vector2& u)  const;
			Vector2         operator*   (const Vector2& u)  const;
			Vector2         operator/   (const Vector2& u)  const;
			Vector2&        operator+=  (const Vector2& u);
			Vector2&        operator-=  (const Vector2& u);
			Vector2&        operator*=  (const Vector2& u);
			Vector2&        operator/=  (const Vector2& u);

			bool            operator>   (float s)  const;
			bool            operator<   (float s)  const;
			bool            operator>   (const Vector2& u)  const;
			bool            operator<   (const Vector2& u)  const;
			bool            operator==  (const Vector2& u)  const;
			bool            operator!=  (const Vector2& u)  const;
			const float&    operator[]  (size_t i)          const;
			float&          operator[]  (size_t i);

			static float Dot(const Vector2& v, const Vector2& u);
			float MagnitudeSquared() const;
			float Magnitude() const;
			Vector2 Normalized() const;
			Vector2 Normalize();

		public:
			union
			{
				__m128 m_vector;
				struct
				{
					float x, y;
				};
				float m_data[2];
			};
        };

		bool operator>(const float s, const Vector2& v);
		bool operator<(const float s, const Vector2& v);

        std::ostream& operator<< (std::ostream& output, const Vector2& v);

		/////////////////////////////////////////////////////////
        // Vector3 definition
        /////////////////////////////////////////////////////////

        class _MM_ALIGN16 Vector3
        {
            friend class Matrix4;
        public:
            
            /****************************************************
            *	Constructors
            *****************************************************/
            Vector3();
			Vector3(float xyz);
			Vector3(const Vector2& xy, float z);
            Vector3(float x, float y, float z);
            Vector3(const Vector3& other);

            /****************************************************
            *	 Custom allocation/deallocation
            *****************************************************/
            void* operator new(size_t _size);
            void  operator delete(void* p);
            
            /****************************************************
            *	Operators
            *****************************************************/

            explicit operator const __m128(void)   const;
			Vector3 operator+   (float s) const;
			Vector3 operator-   (float s) const;
            Vector3 operator*   (float s) const;
            Vector3 operator/   (float s) const;
			Vector3 operator+=  (float s);
			Vector3 operator-=  (float s);
            Vector3 operator*=  (float s);
            Vector3 operator/=  (float s);
			Vector3 operator+   (const Vector3& u) const;
			Vector3 operator-   (const Vector3& u) const;
			Vector3 operator*   (const Vector3& u) const;
			Vector3 operator/   (const Vector3& u) const;
			Vector3 operator+=  (const Vector3& u);
			Vector3 operator-=  (const Vector3& u);
			Vector3 operator*=  (const Vector3& u);
			Vector3 operator/=  (const Vector3& u);

			bool    operator>   (float s) const;
			bool    operator<   (float s) const;
            bool    operator>   (const Vector3& u) const;
            bool    operator<   (const Vector3& u) const;
            bool    operator==  (const Vector3& u) const;
            bool    operator!=  (const Vector3& u) const;
            const float&  operator[]  (int i) const;
			const float&  operator[]  (int i);

			static float Dot(const Vector3& v, const Vector3& u);
			static Vector3 Cross(const Vector3& v, const Vector3& u);
			float MagnitudeSquared() const;
			float Magnitude() const;
			Vector3 Normalized() const;
			Vector3 Normalize();
          
		public:
            union
            {
                struct
                {
                    float x, y, z;
                };
                float  m_data[3];
                __m128 m_vector;
            };
        };

		bool operator>(const float s, const Vector3& v);
		bool operator<(const float s, const Vector3& v);

        std::ostream& operator<< (std::ostream& output, Vector3& h);

        /////////////////////////////////////////////////////////
        // MM Vector4 Definition
        /////////////////////////////////////////////////////////

        class _MM_ALIGN16 Vector4
        {
        public:

            /****************************************************
            *	Operators
            *****************************************************/
            
            Vector4();
			Vector4(const Vector2& xy, float z, float w);
			Vector4(const Vector3& xyz, float w);
            Vector4(float x, float y, float z, float w);
            Vector4(const Vector4& other);
            explicit Vector4(__m128 v);

			/****************************************************
			*	 Custom allocation/deallocation
			*****************************************************/
            void* operator new(size_t _size);
            void  operator delete(void* p);


            /****************************************************
            *	Operators
            *****************************************************/
            explicit operator __m128(void) const;  
            Vector4 operator*   (float s) const; 
            Vector4 operator/   (float s) const;  
            Vector4 operator-   (float s) const;
            Vector4 operator+   (float s) const;  
            Vector4& operator*= (float s);
            Vector4& operator/= (float s);
            Vector4& operator-= (float s);
            Vector4& operator+= (float s);
            bool operator>      (const Vector4& u) const;
            bool operator<      (const Vector4& u) const;
            bool operator==     (const Vector4& u) const;
            bool operator!=     (const Vector4& u) const;
            Vector4 operator*   (const Vector4& u) const;
            Vector4 operator+   (const Vector4& u) const;
            Vector4 operator-   (const Vector4& u) const;
            Vector4& operator+= (const Vector4& u);
            Vector4& operator-= (const Vector4& u);
            float& operator[]   (size_t i);
            const float& operator[] (size_t i) const;
            operator Vector3() const;
            operator Vector2() const;

        public:
            union
            {
                __m128 m_vector;
                struct
                {
                    float x, y, z, w;
                };
                float data[4];
            };
        };
        std::ostream& operator<< (std::ostream& output, Vector4& h);

        /////////////////////////////////////////////////////////
        // MM Quaternion Definition
        /////////////////////////////////////////////////////////

        class _MM_ALIGN16 Quaternion
        {
        public:

            /****************************************************
            *	Constructors
            *****************************************************/

            Quaternion();
            Quaternion(const Vector3& axis, float angle);
            Quaternion(float x, float y, float z, float w);
            Quaternion(float roll, float pitch, float yaw);
            explicit Quaternion(__m128 quatData);

            /****************************************************
            *	 Custom allocation/deallocation
            *****************************************************/

            void* operator new(size_t _size);
            void  operator delete(void* p);
            void* operator new[](size_t size);
            void  operator delete[](void* p);

            /****************************************************
            *	Operators
            *****************************************************/

            bool        operator==  (const Quaternion& p_rhs)   const;
            bool        operator!=  (const Quaternion& p_rhs)   const;

            Quaternion  operator+   (const Quaternion& p_rhs)   const;
            Quaternion  operator-   (const Quaternion& p_rhs)   const;
            Quaternion  operator*   (const Quaternion& p_rhs)   const;

            Quaternion& operator+=  (const Quaternion& p_rhs);
            Quaternion& operator-=  (const Quaternion& p_rhs);
            Quaternion& operator*=  (const Quaternion& p_rhs);

            explicit operator __m128() const;

        public:
            union
            {
                __m128 m_quaternion;
                struct
                {
                    float x, y, z, w;
                };
                float data[4];
            };
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

        bool   _MM_CALLCONV MMVectorEqual(__m128 v, __m128 u);


        //////////////////////////////////////////////////////////
        // MM Matrix Operations
        //////////////////////////////////////////////////////////
		Matrix4 _MM_CALLCONV MMMatrixTranslation(const Vector3& v);
		Matrix4 _MM_CALLCONV MMMatrixRotationX(float r);
		Matrix4 _MM_CALLCONV MMMatrixRotationY(float r);
		Matrix4 _MM_CALLCONV MMMatrixRotationZ(float r);
		Matrix4 _MM_CALLCONV MMMatrixRotationXYZ(const Vector3& r);
		Matrix4 _MM_CALLCONV MMMatrixScale(const Vector3& scale);
        Matrix4 _MM_CALLCONV MMMatrixOrthoProj(float left, float right, float bottom, float top, float znear, float zfar);
        Matrix4 _MM_CALLCONV MMMatrixPerspProj(float fov, float width, float height, float znear, float zfar);
        Matrix4 _MM_CALLCONV MMMatrixLookAt(const Vector3& lookAt, const Vector3& center, const Vector3& up);
        Matrix4 _MM_CALLCONV MMMatrixTranspose(const Matrix4& m);
        Matrix4 _MM_CALLCONV MMMatrixInverse(const Matrix4& m);

        //////////////////////////////////////////////////////////
        // MM Vector2 Operations
        //////////////////////////////////////////////////////////
        float _MM_CALLCONV MMVector2Dot(const Vector2& v, const Vector2& u);
		float _MM_CALLCONV MMVector2MagnitudeSqr(const Vector2& v);
		float _MM_CALLCONV MMVector2Magnitude(const Vector2& v);
        Vector2 _MM_CALLCONV MMVector2Normalized(const Vector2& v);

        //////////////////////////////////////////////////////////
        // MM Vector3 Operations
        //////////////////////////////////////////////////////////
        
        Vector3 _MM_CALLCONV MMVector3Cross(const Vector3& v, const Vector3& u);
        float	_MM_CALLCONV MMVector3Dot(const Vector3& v, const Vector3& u);
		float   _MM_CALLCONV MMVector3MagnitudeSqr(const Vector3& v);
        float   _MM_CALLCONV MMVector3Magnitude(const Vector3& v);
		Vector3 _MM_CALLCONV MMVector3Normalized(const Vector3& v);

        
        //////////////////////////////////////////////////////////
        // MM Vector4 Operations
        //////////////////////////////////////////////////////////
        float   _MM_CALLCONV MMVector4Dot(const Vector4& v, const Vector4& u);
        Vector4 _MM_CALLCONV MMVector4Normalize(const Vector4& v);
        float   _MM_CALLCONV MMVector4Magnitude(const Vector4& v);


        //////////////////////////////////////////////////////////
        // MM Quaternion Operations
        //////////////////////////////////////////////////////////
        float   _MM_CALLCONV MMQuaternionDot(const Quaternion& q, const Quaternion& r);
        Quaternion _MM_CALLCONV MMQuaternionNormalize(const Quaternion& q);
        float   _MM_CALLCONV MMQuaternionMagnitude(const Quaternion& q);
        float   _MM_CALLCONV MMQuaternionMagnitudeSqr(const Quaternion& q);
        Quaternion _MM_CALLCONV MMQuaternionConjugate(const Quaternion& q);
    }
}



#include <ht_mathmm.inl>
#include <ht_mathvector2.inl>
#include <ht_mathvector3.inl>
#include <ht_mathvector4.inl>
#include <ht_mathmatrix.inl>
#include <ht_mathquaternion.inl>