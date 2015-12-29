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
 * \class Vector2
 * \ingroup HachitMath
 *
 * \brief A two dimensional vector
 *
 * A collection of 2 floats: X and Y
 */

#pragma once

#include <ht_platform.h>
#include <iostream>
#include <cmath>

namespace Hatchit
{
	namespace Math
	{
		class HT_API Vector2
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

		/** An insertion operator for a Vector2 to interace with an ostream
		 * \param output The ostream to output to
		 * \param h The Vector2 to interface with the ostream
		 */
		HT_API std::ostream& operator<< (std::ostream& output, Vector2& h);
		/** An extraction operator for a Vector2 to interace with an istream
		 * \param output The istream to input from
		 * \param h The Vector2 to be filled by the istream
		 */
		HT_API std::istream& operator>> (std::istream& input, Vector2& h);
	}
}
