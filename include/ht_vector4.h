/**
**    Hatchit Engine
**    Copyright(c) 2015 Third-Degree
**
**    GNU Lesser General Public License
**    This file may be used under the terms of the GNU Lesser
**    General Public License version 4 as published by the Free
**    Software Foundation and appearing in the file LICENSE.LGPLv4 included
**    in the packaging of this file. Please review the following information
**    to ensure the GNU Lesser General Public License requirements
**    will be met: https://www.gnu.org/licenses/lgpl.html
**
**/


/**
* \class Vector4
* \ingroup HatchitMath
*
* \brief A three dimensional vector
*
* A collection of 4 floats: X, Y and Z
*/

#pragma once

#include <ht_platform.h>
#include <iostream>
#include <ostream>
#include <ht_scalar.h>

namespace Hatchit
{
	namespace Math
	{
		class Vector2;
		class Vector3;

		class HT_API Vector4
		{
		public:
			//Constructors
			///Create a Vector4 with all 4 elements being 0
			Vector4();
			///Create a Vector4 with the elements x, y and z
			Vector4(float x, float y, float z, float w);
			///Create a copy of an existing Vector4
			Vector4(const Vector4& other);
			///Create a Vector4 with the first three elements of a given Vector3 and a fourth given float w
			Vector4(Vector3& v3, float w);

			//Custom allocation/deallocation
			///Allocate a 16byte aligned array of Vector4s
			void* operator new(size_t _size);
			///Delete an array of Vector4s
			void  operator delete(void* p);
			///Cast Vector4's SSE intrinsic to __m128
			operator const __m128(void) const;

			//Accessors & Mutators
			///Returns the first element \return The first element
			float getX();
			///Returns the second element \return The second element
			float getY();
			///Returns the third element \return The third element
			float getZ();
			///Returns the fourth element \return The fourth element
			float getW();

			/** Returns the magnitude of the vector
			* \return The magnitude as a float
			*/
			float getMagnitude();
			/** Returns this Vector4 as a pointer to an array of floats
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
			/** Sets the third element
			* \param z The float you want to be the third element of this vector
			*/
			void setZ(float z);

			/** Sets the fourth element
			* \param w The float you want to be the fourth element of this vector
			*/
			void setW(float w);

			//Static functions

			/** Executes the Dot product on two Vector4s as v * u
			* \param v The first Vector4
			* \param u The second Vector4
			* \return The Dot product of v and u as a float
			*/
			static float Dot(Vector4 v, Vector4 u);
			/** Normalizes a Vector4
			* \param v The Vector4 to normalize
			* \return A normalized version of v
			*/
			static Vector4 Normalize(Vector4 v);

			//Operators

			/** Multiplies all elements in this Vector4 by a given scalar
			* This operation returns a new Vector4
			* \param s The scalar to multiply this Vector4 by
			* \return A Vector4 after all the elements have been multiplied by s
			*/
			Vector4 operator* (float s);
			/** Divides all elements in this Vector4 by a given scalar
			* This operation returns a new Vector4
			* \param s The scalar to divide this Vector4 by
			* \return A Vector4 after all the elements have been divided by s
			*/
			Vector4 operator/ (float s);
			/** Subtracts all elements in this Vector4 by a given scalar
			* This operation returns a new Vector4
			* \param s The scalar to subtract this Vector4 by
			* \return A Vector4 after all the elements have been subtracted by s
			*/
			Vector4 operator- (float s);
			/** Adds all elements in this Vector4 by a given scalar
			* This operation returns a new Vector4
			* \param s The scalar to add this Vector4 by
			* \return A Vector4 after all the elements have been added by s
			*/
			Vector4 operator+ (float s);

			/** Multiplies all elements in this Vector4 by a given scalar
			* This operation affects the elements in this Vector4
			* \param s The scalar to multiply this Vector4 by
			* \return This Vector4 after all the elements have been multiplied by s
			*/
			Vector4 operator*= (float s);
			/** Divides all elements in this Vector4 by a given scalar
			* This operation affects the elements in this Vector4
			* \param s The scalar to divide this Vector4 by
			* \return This Vector4 after all the elements have been divided by s
			*/
			Vector4 operator/= (float s);
			/** Subtracts all elements in this Vector4 by a given scalar
			* This operation affects the elements in this Vector4
			* \param s The scalar to subtract this Vector4 by
			* \return This Vector4 after all the elements have been subtracted by s
			*/
			Vector4 operator-= (float s);
			/** Adds all elements in this Vector4 by a given scalar
			* This operation affects the elements in this Vector4
			* \param s The scalar to add this Vector4 by
			* \return This Vector4 after all the elements have been added by s
			*/
			Vector4 operator+= (float s);

			/** Compares the magnitue of this Vector4 to another given Vector4
			* \param u The other Vector4
			* \return True if this Vector4 has a larger magnitude than the other Vector4
			*/
			bool operator>(Vector4 u);
			/** Compares the magnitue of this Vector4 to another given Vector4
			* \param u The other Vector4
			* \return True if this Vector4 has a smaller magnitude than the other Vector4
			*/
			bool operator<(Vector4 u);
			/** Compares the values of this Vector4 to another given Vector4
			* \param u The other Vector4
			* \return True if this Vector4 has the same values of the other Vector4
			*/
			bool operator==(Vector4 u);
			/** Compares the values of this Vector4 to another given Vector4
			* \param u The other Vector4
			* \return True if this Vector4 does not have the same values as the other Vector4
			*/
			bool operator!=(Vector4 u);

			/** Executes the Dot product this Vector4 and another as this * other
			* \param u The other Vector4
			* \return The Dot product of this * u as a float
			*/
			float operator* (Vector4 u);

			/** Adds all of the elements from a given vector to this one
			* \param u The other Vector4
			* \return A new vector with the sums of all the pairs of elements
			*/
			Vector4 operator+ (Vector4 u);
			/** Subtracts all of the elements from this vector by a given vector
			* \param u The other Vector4
			* \return A new vector with the differences of all the pairs of elemens
			*/
			Vector4 operator- (Vector4 u);
			/** Adds all of the elements from a given vector to this one
			* \param u The other Vector4
			* \return This vector with the sums of all the pairs of elements
			*/
			Vector4 operator+= (Vector4 u);
			/** Subtracts all of the elements from this vector by a given one
			* \param u The other Vector4
			* \return This vector with the differences of all the pairs of elements
			*/
			Vector4 operator-= (Vector4 u);

			/** Fetches an element of this Vector at the index i
			* \param i The index of the element to fetch
			* \return A float that is stored in this Vector4 at the index i
			* This will throw an index out of range exception if you go beyond an index if 1
			*/
			float& operator[] (int i);

			///Returns a Vector3 with the first three elements from this vector and the last one being 0
			operator Vector3();
			///Returns a Vector2 with the fist two elements from this vector
			operator Vector2();

		private:
			__m128 m_vector;
		};

		/** An insertion operator for a Vector4 to interace with an ostream
		* \param output The ostream to output to
		* \param h The Vector4 to interface with the ostream
		*/
		HT_API std::ostream& operator<< (std::ostream& output, Vector4& h);
		/** An insertion operator for a Vector4 to interace with an ostream
		* \param output The ostream to output to
		* \param h The Vector4 to interface with the ostream
		*/
		HT_API std::istream& operator>> (std::istream& input, Vector4& h);
	}
}
