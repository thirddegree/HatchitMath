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
        #define _MM_CALLCONV __attribute__((fastcall))
        #endif
    #endif
#endif

namespace Hatchit {

    namespace Math {

        class Vector2;
        class Vector3;
        class Vector4;
        class Matrix4;

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
            Matrix4(Vector3 a, Vector3 b, Vector3 c, Vector3 d);
            Matrix4(Vector4 a, Vector4 b, Vector4 c, Vector4 d);

            /****************************************************
            *	Operators
            *****************************************************/

            Matrix4 operator* (Matrix4 mat);
            Vector3 operator* (Vector3 vec);
            Vector4 operator* (Vector4 vec);
            

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
        std::istream& operator>> (std::istream& input,  Matrix4& h);

        /////////////////////////////////////////////////////////
        // Vector2 definition
        /////////////////////////////////////////////////////////

        class Vector2
        {
        public:
            //Constructors
            ///Create a Vector2 with both elements being 0
            Vector2();
            ///Create a Vector2 with the elements described by x and y
            Vector2(float x, float y);
            ///Create a Vector2 with the elements of another Vector2
            Vector2(const Vector2& other);

            //Destructor
            virtual ~Vector2();

            //Accessors & Mutators
            ///Returns the first element \return The first element
            float getX();
            ///Returns the second element \return The second element
            float getY();

            /** Returns the magnitude
            * \return The magnitude as a float
            */
            float getMagnitude();
            /** Returns this Vector3 as a pointer to an array of floats
            * \return This vector as an array of floats
            */
            float* getAsArray();

            /** Sets the first element
            * \param x The float you want to be the first element of this vector
            */
            void setX(float x);
            /** Sets the second element
            * \param y The float you want to be the second element of this vector
            */
            void setY(float y);

            //Static functions

            /** Executes the Dot product on two Vector2s as v * u
            * \param v The first Vector2
            * \param u The second Vector2
            * \return The Dot product of v and u as a float
            */
            static float Dot(Vector2 v, Vector2 u);
            /** Normalizes a Vector2
            * \param v The Vector2 to normalize
            * \return A normalized version of v
            */
            static Vector2 Normalize(Vector2 v);

            //Operators

            /** Performs the dot procduct between this Vector2 and another Vector2
            * \param u The other Vector2
            * \return The dot product between this vector and u
            */
            float operator* (Vector2 u);
            /** Multiplies a scalar into this Vector2
            * \param s The other scalar
            * \return A Vector2 whose elements have been multiplied by s
            */
            Vector2 operator* (float s);
            /** Adds another Vector2 to this one
            * \param u The other Vector2
            * \return A Vector2 whose elements are a result of this Vector2 added to u
            */
            Vector2 operator+ (Vector2 u);
            /** Fetches an element of this Vector at the index i
            * \param i The index of the element to fetch
            * \return A float that is stored in this Vector2 at the index i
            * This will throw an index out of range exception if you go beyond an index if 1
            */
            float& operator[] (int i);

        private:
            float vector[2];
        };
        /** An insertion operator for a Vector2 to interface with an ostream
        * \param output the ostream to output to
        * \param v the Vector2 to interface with the ostream
        */
        std::ostream& operator<< (std::ostream& output, Vector2& v);
        /** An extraction operator for a Vector2 to interface with an istream
        * \param input The istream to grab input from
        * \param v The Vector2 to interface with the istream
        */
        std::istream& operator>> (std::istream& input, Vector2& v);

		/////////////////////////////////////////////////////////
        // Vector3 definition
        /////////////////////////////////////////////////////////

        class Vector3
        {
            friend class Matrix4;
        public:
            
            /****************************************************
            *	Constructors
            *****************************************************/
            Vector3();
            Vector3(float x, float y, float z);
            Vector3(const Vector3& other);
            Vector3(Vector4& v4);

            /****************************************************
            *	 Custom allocation/deallocation
            *****************************************************/
            void* operator new(size_t _size);
            void  operator delete(void* p);
            
            /****************************************************
            *	Operators
            *****************************************************/

            operator const __m128(void) const;
            Vector3 operator*   (float s);
            Vector3 operator/   (float s);
            Vector3 operator-   (float s);
            Vector3 operator+   (float s);
            Vector3 operator*=  (float s);
            Vector3 operator/=  (float s);
            Vector3 operator-=  (float s);
            Vector3 operator+=  (float s);
            bool    operator>   (Vector3 u);
            bool    operator<   (Vector3 u);
            bool    operator==  (Vector3 u);
            bool    operator!=  (Vector3 u);
            Vector3 operator*   (Vector3 u);
            Vector3 operator+   (Vector3 u);
            Vector3 operator-   (Vector3 u);
            Vector3 operator+=  (Vector3 u);
            Vector3 operator-=  (Vector3 u);
            float&  operator[]  (int i);

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

        std::ostream& operator<< (std::ostream& output, Vector3& h);
        std::istream& operator>> (std::istream& input,  Vector3& h);

        /////////////////////////////////////////////////////////
        // MM Vector4 Definition
        /////////////////////////////////////////////////////////

        class Vector4
        {
        public:

            /****************************************************
            *	Operators
            *****************************************************/
            
            Vector4();
            Vector4(float x, float y, float z, float w);
            Vector4(const Vector4& other);
            Vector4(const Vector3& v3, float w);
            explicit Vector4(__m128 v);

			/****************************************************
			*	 Custom allocation/deallocation
			*****************************************************/
            void* operator new(size_t _size);
            void  operator delete(void* p);


            /****************************************************
            *	Operators
            *****************************************************/
            operator __m128(void) const;  
            Vector4 operator* (float s) const; 
            Vector4 operator/ (float s) const;  
            Vector4 operator- (float s) const;
            Vector4 operator+ (float s) const;  
            Vector4& operator*= (float s);
            Vector4& operator/= (float s);
            Vector4& operator-= (float s);
            Vector4& operator+= (float s);
            bool operator>(Vector4 u) const;
            bool operator<(Vector4 u) const;
            bool operator==(Vector4 u) const;
            bool operator!=(Vector4 u) const;
            Vector4 operator* (Vector4 u) const;
            Vector4 operator+ (Vector4 u) const;
            Vector4 operator- (Vector4 u) const;
            Vector4& operator+= (Vector4 u);
            Vector4& operator-= (Vector4 u); 
            float& operator[] (size_t i);
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
        std::istream& operator>> (std::istream& input,  Vector4& h);

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


        //////////////////////////////////////////////////////////
        // MM Matrix Operations
        //////////////////////////////////////////////////////////
        Matrix4 _MM_CALLCONV MMMatrixOrthoProj(float left, float right, float bottom, float top, float znear, float zfar);
        Matrix4 _MM_CALLCONV MMMatrixPerspProj(float fov, float aspect, float znear, float zfar);
        Matrix4 _MM_CALLCONV MMMatrixLookAt(Vector3 lookAt, Vector3 center, Vector3 up);
        Matrix4 _MM_CALLCONV MMMatrixTranspose(const Matrix4& m);
        Matrix4 _MM_CALLCONV MMMatrixInverse(const Matrix4& m);

        //////////////////////////////////////////////////////////
        // MM Vector3 Operations
        //////////////////////////////////////////////////////////
        
        Vector3 _MM_CALLCONV MMVector3Cross(Vector3 v, Vector3 u);
        float	_MM_CALLCONV MMVector3Dot(Vector3 v, Vector3 u);
        Vector3 _MM_CALLCONV MMVector3Normalize(Vector3 v);
        float   _MM_CALLCONV MMVector3Magnitude(Vector3 v);

        
        //////////////////////////////////////////////////////////
        // MM Vector4 Operations
        //////////////////////////////////////////////////////////
        float   _MM_CALLCONV MMVector4Dot(Vector4 lhs, Vector4 rhs);
        Vector4 _MM_CALLCONV MMVector4Normalize(Vector4 v);
        float   _MM_CALLCONV MMVector4Magnitude(Vector4 v);
    }
}



#include <ht_mathmm.inl>
#include <ht_mathvector3.inl>
#include <ht_mathvector4.inl>
#include <ht_mathmatrix.inl>