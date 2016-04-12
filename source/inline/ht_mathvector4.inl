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
#include <ht_malloc.h>
#include <ht_math.h>

namespace Hatchit
{
    namespace Math
    {
        /** Returns a normalized version of the vector
        * \return The normalized vector
        */
        inline Vector4 _MM_CALLCONV MMVector4Normalize(const Vector4& v)
        {
            __m128 normalizedVec = _mm_mul_ps(v.m_vector, v.m_vector);
            normalizedVec = _mm_add_ps(normalizedVec, _mm_shuffle_ps(normalizedVec, normalizedVec, _MM_SHUFFLE(2, 3, 0, 1)));
            normalizedVec = _mm_add_ps(normalizedVec, _mm_shuffle_ps(normalizedVec, normalizedVec, _MM_SHUFFLE(0, 1, 2, 3)));
            normalizedVec = _mm_sqrt_ps(normalizedVec);
            Vector4 val;
            val.m_vector = _mm_div_ps(v.m_vector, normalizedVec);

            return val; 
        }

        inline Vector4 _MM_CALLCONV MMVector4NormalizeEst(const Vector4& v)
        {
            __m128 normalizedVec = _mm_mul_ps(v.m_vector, v.m_vector);
            normalizedVec = _mm_add_ps(normalizedVec, _mm_shuffle_ps(normalizedVec, normalizedVec, _MM_SHUFFLE(2, 3, 0, 1)));
            normalizedVec = _mm_add_ps(normalizedVec, _mm_shuffle_ps(normalizedVec, normalizedVec, _MM_SHUFFLE(0, 1, 2, 3)));
            normalizedVec = _mm_rsqrt_ps(normalizedVec);
            Vector4 val;
            val.m_vector = _mm_mul_ps(v.m_vector, normalizedVec);

            return val;
        }

        
        /** Returns the magnitude of the vector
        * \return The magnitude as a float
        */
        inline float _MM_CALLCONV MMVector4Magnitude(const Vector4& v)
        {
            __m128 val = _mm_mul_ps(v.m_vector, v.m_vector);
            val = _mm_add_ps(val, _mm_shuffle_ps(val, val, _MM_SHUFFLE(2, 3, 0, 1)));
            val = _mm_add_ps(val, _mm_shuffle_ps(val, val, _MM_SHUFFLE(0, 1, 2, 3)));
            val = _mm_sqrt_ps(val);

            return MMVectorGetX(val);
        }

        inline float _MM_CALLCONV MMVector4MagnitudeSqr(const Vector4& v)
        {
            __m128 val = _mm_mul_ps(v.m_vector, v.m_vector);
            val = _mm_add_ps(val, _mm_shuffle_ps(val, val, _MM_SHUFFLE(2, 3, 0, 1)));
            val = _mm_add_ps(val, _mm_shuffle_ps(val, val, _MM_SHUFFLE(0, 1, 2, 3)));

            return MMVectorGetX(val);
        }

        /** Returns the dot product of two vectors
        * \return The dot product as a float
        */
        inline float _MM_CALLCONV MMVector4Dot(const Vector4& v, const Vector4& u)
        {
            __m128 dotProd = _mm_mul_ps(v.m_vector, u.m_vector);
            dotProd = _mm_add_ps(dotProd, _mm_shuffle_ps(dotProd, dotProd, _MM_SHUFFLE(2, 3, 0, 1)));
            dotProd = _mm_add_ps(dotProd, _mm_shuffle_ps(dotProd, dotProd, _MM_SHUFFLE(0, 1, 2, 3)));
            float returnValue;
            _mm_store_ss(&returnValue, dotProd);
            return returnValue;
        }

        /****************************************************
        *	Constructors
        *****************************************************/

        //Create a Vector4 with all 4 elements being 0
        inline Vector4::Vector4() : m_vector(_mm_setzero_ps()) {}

        //Create a Vector4 populated with rawArray data
        inline Vector4::Vector4(const float rawArray[]) : m_vector(MMVectorSet(rawArray[0], rawArray[1], rawArray[2], rawArray[3])) {}

		//Create a Vector4 with the same value in all elements
		inline Vector4::Vector4(float xyzw) : m_vector(_mm_set_ps1(xyzw)) {}

        //Create a Vector4 with the elements x, y and z
        inline Vector4::Vector4(float x, float y, float z, float w) : m_vector(MMVectorSet(x, y, z, w)) {}

		//Create a vector4 using x and y from a vector 2 and z and w from floats
		inline Vector4::Vector4(const Vector2 & xy, float z, float w) : m_vector(MMVectorSet(xy.x, xy.y, z, w)) {}

        //Create a Vector4 with the first three elements of a given Vector3 and a fourth given float w
		inline Vector4::Vector4(const Vector3& v3, float w) : m_vector(MMVectorSetWRaw(static_cast<__m128>(v3), &w)) {}

        //Create a copy of an existing Vector4
        inline Vector4::Vector4(const Vector4& other) : m_vector(other.m_vector) {}

        //Create a Vector4 with an intrinsic vector type.
        inline Vector4::Vector4(__m128 v) : m_vector(std::move(v)) {}

        //Allocate a 16byte aligned array of Vector4s
        inline void* Vector4::operator new(size_t _size)
        {
            return aligned_malloc(_size, vectorAlignment);
        }
        
        //Delete an array of Vector4s
        inline void Vector4::operator delete(void* p)
        {
            aligned_free(p);
        }

        //Cast Vector4's SSE intrinsic to __m128
        inline Vector4::operator __m128(void) const
        {
            return m_vector;
        }

        /** Adds all elements in this Vector4 by a given scalar
        * This operation returns a new Vector4
        * \param s The scalar to add this Vector4 by
        * \return A Vector4 after all the elements have been added by s
        */
        inline Vector4 Vector4::operator+(float s) const
        {
            return Vector4(_mm_add_ps(m_vector, _mm_set1_ps(s)));
        }

        /** Subtracts all elements in this Vector4 by a given scalar
        * This operation returns a new Vector4
        * \param s The scalar to subtract this Vector4 by
        * \return A Vector4 after all the elements have been subtracted by s
        */
        inline Vector4 Vector4::operator-(float s) const
        {
            return Vector4(_mm_sub_ps(m_vector, _mm_set1_ps(s)));
        }
      
        /** Multiplies all elements in this Vector4 by a given scalar
        * This operation affects the elements in this Vector4
        * \param s The scalar to multiply this Vector4 by
        * \return A Vector4 after all the elements have been multiplied by s
        */
        inline Vector4 Vector4::operator*(float s) const
        {
            return Vector4(_mm_mul_ps(m_vector, _mm_set1_ps(s)));
        }

        /** Divides all elements in this Vector4 by a given scalar
        * This operation returns a new Vector4
        * \param s The scalar to divide this Vector4 by
        * \return A Vector4 after all the elements have been divided by s
        */
        inline Vector4 Vector4::operator/(float s) const
        {
            return Vector4(_mm_div_ps(m_vector, _mm_set1_ps(s)));
        }

        /** Adds all elements in this Vector4 by a given scalar
        * This operation affects the elements in this Vector4
        * \param s The scalar to add this Vector4 by
        * \return This Vector4 after all the elements have been added by s
        */
        inline Vector4& Vector4::operator+=(float s)
        {
            m_vector = _mm_add_ps(m_vector, _mm_set1_ps(s));
            return *this;
        }

        /** Subtracts all elements in this Vector4 by a given scalar
        * This operation affects the elements in this Vector4
        * \param s The scalar to subtract this Vector4 by
        * \return This Vector4 after all the elements have been subtracted by s
        */
        inline Vector4& Vector4::operator-=(float s)
        {
            m_vector = _mm_sub_ps(m_vector, _mm_set1_ps(s));
            return *this;
        }

        /** Multiplies all elements in this Vector4 by a given scalar
        * This operation affects the elements in this Vector4
        * \param s The scalar to multiply this Vector4 by
        * \return This Vector4 after all the elements have been multiplied by s
        */
        inline Vector4& Vector4::operator*=(float s)
        {
            m_vector = _mm_mul_ps(m_vector, _mm_set1_ps(s));
            return *this;
        }

        /** Divides all of the elements from this vector by a given scalar
        * This operation affects the elements in this Vector4
        * \param s Scalar to divide elements by
        * \return This vector with the differences of all the pairs of elements
        */
        inline Vector4& Vector4::operator/=(float s)
        {
            m_vector = _mm_div_ps(m_vector, _mm_set1_ps(s));
            return *this;
        }

        /** Compares the values of this Vector4 to another given Vector4
        * \param u The other Vector4
        * \return True if this Vector4 has the same values of the other Vector4
        */
        inline bool Vector4::operator==(const Vector4& rhs) const
        {
            //This may have too little of epsilon to be considered accurate.
            //Could add and subtract epsilon from rhs.m_vector, compare less than /
            //greater than, logic and the components and then check in the future
            //If this is too strict.
            return MMVectorEqual(m_vector, rhs.m_vector);
        }

        /** Compares the values of this Vector4 to another given Vector4
        * \param u The other Vector4
        * \return True if this Vector4 does not have the same values as the other Vector4
        */
        inline bool Vector4::operator!=(const Vector4& rhs) const
        {
            return !operator==(rhs);
        }

        /** Adds all of the elements from a given vector to this one
        * \param u The other Vector4
        * \return A new vector with the sums of all the pairs of elements
        */
        inline Vector4 Vector4::operator+(const Vector4& rhs) const
        {
            return Vector4(_mm_add_ps(m_vector, rhs.m_vector));
        }

        /** Subtracts all of the elements from this vector by a given vector
        * \param u The other Vector4
        * \return A new vector with the differences of all the pairs of elemens
        */
        inline Vector4 Vector4::operator-(const Vector4& u) const
        {
            return Vector4(_mm_sub_ps(m_vector, u.m_vector));
        }

        /** Executes memberwise multiplication on this Vector4
        * \param u The other Vector4
        * \return The products of this * u as a Vector4
        */
        inline Vector4 Vector4::operator*(const Vector4& rhs) const
        {
            return Vector4(_mm_mul_ps(m_vector, rhs.m_vector));
        }

        /** Executes memberwise division on this Vector4
        * \param u The Vector4 with the values to divide by
        * \return The quotients of this / u as a Vector4.
        */
        inline Vector4 Vector4::operator/(const Vector4& rhs) const
        {
            return Vector4(_mm_div_ps(m_vector, rhs.m_vector));
        }

        /** Adds all of the elements from a given vector to this one
        * \param u The other Vector4
        * \return This vector with the sums of all the pairs of elements
        */
        inline Vector4& Vector4::operator+=(const Vector4& rhs)
        {
            m_vector = _mm_add_ps(m_vector, rhs.m_vector);
            return *this;
        }

        /** Subtracts all of the elements from this vector by a given one
        * \param u The other Vector4
        * \return This vector with the differences of all the pairs of elements
        */
        inline Vector4& Vector4::operator-=(const Vector4& rhs)
        {
            m_vector = _mm_sub_ps(m_vector, rhs.m_vector);
            return *this;
        }

        /** Multiplies all of the elements of this vector by a given one
        * \param u The Vector4 which to multiply the elements by
        * \return This vector with the products of this vector's 
        * elements and the given vector's elements.
        */
        inline Vector4& Vector4::operator*=(const Vector4& rhs)
        {
            m_vector = _mm_mul_ps(m_vector, rhs.m_vector);
            return *this;
        }

        /** Divides all the elements of this vector by the elements of a given vector
        * \param u The Vector4 which to divide this vector4's elements by
        * \return This vector with the elements of this vector divided by
        * the elements of the given vector's elements.
        */
        inline Vector4& Vector4::operator/=(const Vector4& rhs)
        {
            m_vector = _mm_div_ps(m_vector, rhs.m_vector);
            return *this;
        }

        /** Fetches an element of this Vector at the index i
        * \param i The index of the element to fetch
        * \return A float that is stored in this Vector4 at the index i
        * This will throw an index out of range exception if you go beyond an index if 1
        */
        inline float& Vector4::operator[](size_t i)
        {
            return m_data[i];
        }

        /** Fetches an element of this Vector at the index i
        * \param i The index of the element to fetch
        * \return A float that is stored in this Vector4 at the index i
        * This will throw an index out of range exception if you go beyond an index if 1
        */
        inline const float& Vector4::operator[](size_t i) const
        {
            return m_data[i];
        }

        //Returns a Vector3 with the first three elements from this vector and the last one being 0
        inline Vector4::operator Vector3() const
        {
            _MM_ALIGN16 float vecArray[4];
            _mm_store_ps(&vecArray[0], m_vector);
            return Vector3(vecArray[0], vecArray[1], vecArray[2]);
        }

        //Returns a Vector2 with the fist two elements from this vector
        inline Vector4::operator Vector2() const
        {
            _MM_ALIGN16 float vecArray[4];
            _mm_store_ps(&vecArray[0], m_vector);
            return Vector2(vecArray[0], vecArray[1]);
        }


        inline float Vector4::Dot(const Vector4& v, const Vector4& u)
        {
            return MMVector4Dot(v, u);
        }

        inline Vector4 Vector4::Normalized() const
        {
            return MMVector4Normalize(*this);
        }

        inline Vector4 Vector4::NormalizedEst() const
        {
            return MMVector4NormalizeEst(*this);
        }

        inline float Vector4::Magnitude() const
        {
            return MMVector4Magnitude(*this);
        }

        inline float Vector4::MagnitudeSqr() const
        {
            return MMVector4MagnitudeSqr(*this);
        }

        /** An insertion operator for a Vector4 to interace with an ostream
        * \param output The ostream to output to
        * \param h The Vector4 to interface with the ostream
        */
        inline std::ostream& operator<<(std::ostream& output, Vector4& v)
        {
            output << v.x << " " << v.y << " " << v.z << " " << v.w;
            return output;
        }

        /** Stores values from SIMD registers into Float4
        * \return Float4 with Vector4 data.
        */
        inline Float4 Vector4::ToFloat4() const
        {
            return Float4(m_data);
        }
    }
}
