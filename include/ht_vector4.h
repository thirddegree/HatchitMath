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
 * \class Vector4
 * \ingroup HatchitMath
 *
 * \brief A four dimensional vector
 *
 * A collection of 4 floats: X, Y, Z and W
 */

#pragma once

#include <ht_platform.h>
#include <iostream>
#include <cmath>

namespace Hatchit
{
	namespace Math
	{
		class Vector3;

		class HT_API Vector4
		{
		public:
			//Constructors
			///Create a Vector4 with all 4 elements being 0
			Vector4();
			/** Create a Vector4 with the given elements x, y, z, w
			 * \param x The first element of the vector
			 * \param y The second element of the vector
			 * \param z The third element of the vector
			 * \param w The fourth element of the vector
			 */
			Vector4(float x, float y, float z, float w);
			/** Create a Vector4 with the first 3 elements from a Vector3 and the last element w
			 * \param v The first three elements as a Vector3
			 * \param w The fourth element of the vector
			 */
			Vector4(Vector3 v, float w);
			/** Create a copy of an existing Vector4
			 * \param other The other vector to make a copy of
			 */
			Vector4(const Vector4& other);

			//Destructor
			virtual ~Vector4();

			//Accessors and mutators
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
			/** Sets the third element
			 * \param z The float you want to be the third element of this vector
			 */
			void setZ(float z);
			/** Sets the fourth element
			 * \param w The float you want to be the fourth element of this vector
			 */
			void setW(float w);

			/** Fetches an element of this Vector at the index i
			 * \param i The index of the element to fetch
			 * \return A float that is stored in this Vector3 at the index i
			 * This will throw an index out of range exception if you go beyond an index if 1
			 */
			float& operator[] (int i);

			///Returns a Vector3 with the first three elements of this Vector4 all divided by the 4th element
			operator Vector3();

		private:
			float vector[4];
		};

		/** An insertion operator for a Vector3 to interace with an ostream
		* \param output The ostream to output to
		* \param h The Vector3 to interface with the ostream
		*/
		HT_API std::ostream& operator<< (std::ostream& output, Vector4& h);
		/** An insertion operator for a Vector3 to interace with an ostream
		* \param output The ostream to output to
		* \param h The Vector3 to interface with the ostream
		*/
    HT_API std::istream& operator>> (std::istream& input, Vector4& h);
	}
}
