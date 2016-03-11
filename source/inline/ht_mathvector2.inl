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

#include "ht_math.h"

#include <cassert>

namespace Hatchit {

    namespace Math {


        //////////////////////////////////////////////////////////////////////
        // MMVECTOR2 Implementation
        //////////////////////////////////////////////////////////////////////

        //Create a Vector2 with both elements being 0
        inline Vector2::Vector2() : m_vector(_mm_setzero_ps()) {}

		//Create a Vector2 with both elements being x
		inline Vector2::Vector2(float x) : m_vector(_mm_set_ps1(x)) {}

        //Create a Vector2 with the elements described by x and y
        inline Vector2::Vector2(float x, float y) : m_vector(MMVectorSet(x, y, 0.0f, 0.0f)) {}

        //Create a Vector2 with the elements of another Vector2
        inline Vector2::Vector2(const Vector2& other) : m_vector(other.m_vector) {}

        //Create a Vector2 object using the data from an __m128 vector
        inline Vector2::Vector2(const __m128& vector) : m_vector(vector) {}

        //Create a Vector2 object using the data from an __m128 vector
        inline Vector2::Vector2(__m128&& vector) : m_vector(vector) {}

        //Allocate a 16 byte aligned data chunk for a Vector2
        inline void* Vector2::operator new(size_t size)
        {
            return aligned_malloc(size, vectorAlignment);
        }

        //Delete the 16 byte aligned data chunk for a Vector2
        inline void Vector2::operator delete(void* p)
        {
            return aligned_free(p);
        }

        //Allocate a 16 byte aligned data chunk for an array of Vector2
        inline void* Vector2::operator new[](size_t size)
        {
            return aligned_malloc(size, vectorAlignment);
        }

        //Delete a 16 byte aligned data chunk for an array of Vector2
        inline void Vector2::operator delete[](void* p)
        {
            return aligned_free(p);
        }

        /** Casts a Vector2 object to a __m128
        * This operator casts a Vector2 to an intrinsic __m128
        */
        inline Vector2::operator __m128() const
        {
            return m_vector;
        }

        /** Adds all elements in Vector2 by a given scalar
        * This operator returns a new Vector2
        * \param s The scalar to add this Vector2 by
        * \return A Vector2 after all the elements have been added by s
        */
        inline Vector2 Vector2::operator+(float s) const
        {
            return Vector2(_mm_add_ps(m_vector, MMVectorSet(s, s, 0.0f, 0.0f)));
        }
        /** Subtracts all elements in Vector2 by a given scalar
        * This operator returns a new Vector2
        * \param s The scalar to subtract this Vector2 by
        * \return A Vector2 after all the elements have been subtracted by s
        */
        inline Vector2 Vector2::operator-(float s) const
        {
            return Vector2(_mm_sub_ps(m_vector, MMVectorSet(s, s, 0.0f, 0.0f)));
        }
        /** Multiplies all elements in Vector2 by a given scalar
        * This operator returns a new Vector2
        * \param s The scalar to multiply this Vector2 by
        * \return A Vector2 after all the elements have been multiplied by s
        */
        inline Vector2 Vector2::operator*(float s) const
        {
            return Vector2(_mm_mul_ps(m_vector, _mm_set_ps1(s)));
        }
        /** Divides all elements in Vector2 by a given scalar
        * This operator returns a new Vector2
        * \param s The scalar to divide this Vector2 by
        * \return A Vector2 after all the elements have been divided by s
        */
        inline Vector2 Vector2::operator/(float s) const
        {
            return Vector2(_mm_div_ps(m_vector, _mm_set_ps1(s)));
        }

        /** Adds all elements in this Vector2 by a given scalar
        * This operation affects the elements in this Vector2
        * \param s The scalar to add this Vector2 by
        * \return This Vector2 after all the elements have been added by s
        */
        inline Vector2& Vector2::operator+=(float s)
        {
            m_vector = _mm_add_ps(m_vector, MMVectorSet(s, s, 0.0f, 0.0f));
            return *this;
        }
        /** Subtracts all elements in this Vector2 by a given scalar
        * This operation affects the elements in this Vector2
        * \param s The scalar to subtract this Vector2 by
        * \return This Vector2 after all the elements have been subtracted by s
        */
        inline Vector2& Vector2::operator-=(float s)
        {
            m_vector = _mm_sub_ps(m_vector, MMVectorSet(s, s, 0.0f, 0.0f));
            return *this;
        }
        /** Multiplies all elements in this Vector2 by a given scalar
        * This operation affects the elements in this Vector2
        * \param s The scalar to multiply this Vector2 by
        * \return This Vector2 after all the elements have been multiplied by s
        */
        inline Vector2& Vector2::operator*=(float s)
        {
            m_vector = _mm_mul_ps(m_vector, _mm_set1_ps(s));
            return *this;
        }
        /** Divides all elements in this Vector2 by a given scalar
        * This operation affects the elements in this Vector2
        * \param s The scalar to divide this Vector2 by
        * \return This Vector2 after all the elements have been divided by s
        */
        inline Vector2& Vector2::operator/=(float s)
        {
            m_vector = _mm_div_ps(m_vector, _mm_set1_ps(s));
            return *this;
        }
        /** Adds all of the elements from a given Vector2 to this one
        * \param u The other Vector2
        * \return A new vector with the sums of all the pairs of elements
        */
        inline Vector2 Vector2::operator+(const Vector2& u) const
        {
            return Vector2(_mm_add_ps(m_vector, u.m_vector));
        }
        /** Subtracts all of the elements from a given Vector2 to this one
        * \param u The other Vector2
        * \return A new vector with the differences of all the pairs of elements
        */
        inline Vector2 Vector2::operator-(const Vector2& u) const
        {
            return Vector2(_mm_sub_ps(m_vector, u.m_vector));
        }
        /** Multiplies all of the elements from a given Vector2 to this one
        * \param u The other Vector2
        * \return A new vector with the products of all the pairs of elements
        */
        inline Vector2 Vector2::operator*(const Vector2& u) const
        {
            return Vector2(_mm_mul_ps(m_vector, u.m_vector));
        }
        /** Divides all of the elements from a given Vector2 to this one
        * \param u The other Vector2
        * \return A new vector with the quocient of all the pairs of elements
        */
        inline Vector2 Vector2::operator/(const Vector2& u) const
        {
            return Vector2(_mm_div_ps(m_vector, u.m_vector));
        }

        /** Adds all of the elements from a given Vector2 to this one
        * \param u The other Vector2
        * \return This Vector2 with the sums of all the pairs of elements
        */
        inline Vector2& Vector2::operator+=(const Vector2& u)
        {
            m_vector = _mm_add_ps(m_vector, u.m_vector);
            return *this;
        }
        /** Subtracts all of the elements from a given Vector2 to this one
        * \param u The other Vector2
        * \return This Vector2 with the differences of all the pairs of elements
        */
        inline Vector2& Vector2::operator-=(const Vector2& u)
        {
            m_vector = _mm_sub_ps(m_vector, u.m_vector);
            return *this;
        }
        /** Multiplies all of the elements from a given Vector2 to this one
        * \param u The other Vector2
        * \return This Vector2 with the products of all the pairs of elements
        */
        inline Vector2& Vector2::operator*=(const Vector2& u)
        {
            m_vector = _mm_mul_ps(m_vector, u.m_vector);
            return *this;
        }
        /** Divides all of the elements from a given Vector2 to this one
        * \param u The other Vector2
        * \return This Vector2 with the quocient of all the pairs of elements
        */
        inline Vector2& Vector2::operator/=(const Vector2& u)
        {
            m_vector = _mm_div_ps(m_vector, u.m_vector);
            return *this;
        }

		/** Compares the values of this Vector2 to another given Vector2
		* \param u The other Vector2
		* \return True if this Vector2 has the same values of the other Vector2
		*/
		inline bool Vector2::operator==(const Vector2& u) const
		{
			return _mm_movemask_ps(_mm_cmpeq_ps(m_vector, u.m_vector)) == 15;
		}
		/** Compares the values of this Vector2 to another given Vector2
		* \param u The other Vector2
		* \return True if this Vector2 does not have the same values of the other Vector2
		*/
		inline bool Vector2::operator!=(const Vector2& u) const
		{
			return !operator==(u);
		}


        /** Fetches an element of this Vector2 at the index i
        * \param i The index of the element to fetch
        * \return A float reference that is stored in this Vector2 at the index i
        * This will throw an index out of range exception if you go beyond an index of 2
        */
        inline const float& Vector2::operator[](size_t i) const
        {
            assert(i < 2);
            return m_data[i];
        }
        /** Fetches an element of this Vector2 at the index i
        * \param i The index of the element to fetch
        * \return A float reference that is stored in this Vector2 at the index i
        * This will throw an index out of range exception if you go beyond an index of 2
        */
        inline float& Vector2::operator[](size_t i)
        {
            assert(i < 2);
            return m_data[i];
        }

		/** Calculates the dot product of two vectors
		* \param v, u: vectors used to calculate the dot product
		* \return dot product as a float
		*/
		inline float Vector2::Dot(const Vector2 & v, const Vector2 & u)
		{
			return MMVector2Dot(v, u);
		}

		/** Calculates the magnitude squared of this vector
		* \return magnitude squared as a float
		*/
		inline float Vector2::MagnitudeSquared() const
		{
			return MMVector2MagnitudeSqr(*this);
		}

		/** Calculates the magnitude of this vector
		* \return magnitude as a float
		*/
		inline float Vector2::Magnitude() const
		{
			return MMVector2Magnitude(*this);
		}

		/** Calculates a normalized copy of this float
		* \return the copy
		*/
		inline Vector2 Vector2::Normalized() const
		{
			return MMVector2Normalized(*this);
		}

		/** Normalizes this vector in place
		* \return the same vector
		*/
		inline Vector2 Vector2::Normalize()
		{
			*this = MMVector2Normalized(*this);
			return *this;
		}

        /** Executes the Dot product on two Vector2s as v * u
        * \param v The first Vector2
        * \param u The second Vector2
        * \return The Dot product of v and u as a float
        */
        inline float _MM_CALLCONV MMVector2Dot(const Vector2& v, const Vector2& u)
        {
            __m128 vecMul = _mm_mul_ps(static_cast<__m128>(v), static_cast<__m128>(u));
            return MMVectorGetX(_mm_add_ps(vecMul, _mm_shuffle_ps(vecMul, vecMul, _MM_SHUFFLE(3, 2, 0, 1))));
        }


		/** Calculates the squared magnitude of the Vector2
		* \return The magnitude of the Vector2 squared as a float
		* NOTE:
		* This function is faster than MMVector2Magnitude, use for
		* magnitude comparison
		*/
		inline float _MM_CALLCONV MMVector2MagnitudeSqr(const Vector2& v)
		{
			return MMVector2Dot(v, v);
		}

		/** Calculates the magnitude of the Vector2
		* \return The magnitude as a float
		*/
		inline float _MM_CALLCONV MMVector2Magnitude(const Vector2& v)
		{
			return sqrtf(MMVector2MagnitudeSqr(v));
		}

        /** Normalizes a Vector2
        * \param v The Vector2 to normalize
        * \return A normalized version of v
        * NOTE:
        * This function is only partially intrinsic
        */
        inline Vector2 _MM_CALLCONV MMVector2Normalized(const Vector2& v)
        {
            assert(MMVector2MagnitudeSqr(v) > 0);
            __m128 vecMul = _mm_mul_ps(static_cast<__m128>(v), static_cast<__m128>(v));
            __m128 vecSum = _mm_add_ps(vecMul, _mm_shuffle_ps(vecMul, vecMul, _MM_SHUFFLE(3, 2, 0, 1)));
            return Vector2(_mm_div_ps(static_cast<__m128>(v), _mm_sqrt_ps(vecSum)));
        }

		/** An insertion operator for a Vector2 to interface with an ostream
		* \param output the ostream to output to
		* \param v the Vector2 to interface with the ostream
		*/
		inline std::ostream& operator<<(std::ostream& output, const Vector2& v)
		{
			output << v.x << " " << v.y;
			return output;
		}
    }
}
