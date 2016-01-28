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
 * \class Quaternion
 * \ingroup HachitMath
 *
 * \brief A 4 dimensional representation of rotation
 *
 * This quaternion is represented similarly to a Vector4 but with W,X,Y,Z.
 * This is to match the mathematical representation: a + bi + cj + dk
 * It is designed to represent rotations. 
 */

#pragma once

//Pre-Include Defines
#define _USE_MATH_DEFINES

#include <ht_platform.h>
#include <ht_vector3.h>
#include <ht_vector4.h>
#include <ht_matrix3.h>

#include <iostream>
#include <cmath>

namespace Hatchit
{
	namespace Math
	{
		class HT_API Quaternion
		{
		public:
			//Constructors
			///Creates an identity Quaterion with elements 1,0,0,0
			Quaternion();
			/** Creates a Quaterion with elements set to the given values
			 * \param x The first element
			 * \param y The second element
			 * \param z The third element
			 * \param w The fourth element
			 */
			Quaternion(float w, float x, float y, float z);
			/** Creates a Quaternion based off the Euler rotation described by a
			 * Vector3
			 * \param v The Vector3 used to describe a Euler rotation
			 */
			Quaternion(Vector3 v);
			/** Creates a Quaterion based on the Angle-Axis rotation described by
			 * a Vector4 where x,y,z is the axis and w is the angle
			 * \param v The Vector4 used to describe an Angle-Axis rotation
			 */
			Quaternion(Vector4 v);

			virtual ~Quaternion();

			/** Returns an identity Quaterion with the elements 1,0,0,0
       * \return An identity Quaterion
			 */
			static Quaternion getQuaternionIdentity();

			/** Returns an Quaterion that is the inverse of this one
			 * \return The inverse of this Quaterion
			 */
			Quaternion getInverse();
			/** Returns this Quaterion's rotation in Angle-Axis form with a Vector4
			 * \return The rotation described by this Quaterion in Angle-Axis form
			 */
			Vector4 getAxisAngle();
			/** Returns this Quaterion's rotation in Matrix form
			 * \return The rotation described by this quaterion in Matrix3 form
			 */
			Matrix3 getRotationMatrix();

			//Accessors and mutators

			///Returns the fourth element \return The first element
			float getW();
			///Returns the first element \return The second element
			float getX();
			///Returns the second element \return The third element
			float getY();
			///Returns the third element \return The fourth element
			float getZ();

			/** Sets the fourth element
			 * \param w The float you want to be the first element of this vector
			 */
			void setW(float w);
			/** Sets the first element
			 * \param x The float you want to be the second element of this vector
			 */
			void setX(float x);
			/** Sets the second element
			 * \param y The float you want to be the third element of this vector
			 */
			void setY(float y);
			/** Sets the third element
			 * \param z The float you want to be the fourth element of this vector
			 */
			void setZ(float z);

			/** Fetches an element of this Quaterion at the index i
			 * \param i The index of the element to fetch
			 * \return A float that is stored in this Quaterion at the index i
			 * This will throw an index out of range exception if you go beyond an index if 1
			 */
			float& operator[] (int i);

			/** Multiplies this quaterion with another and returns the product
			 * \param other The other quaternion to multiply into this one
			 * \return The product of this quaterion multiplied by the other one
			 */
			Quaternion operator* (Quaternion other);

		private:
			float q[4];
			void normalize();
		};

		/** An insertion operator for a Quaterion to interace with an ostream
		 * \param output The ostream to output to
		 * \param h The Quaterion to interface with the ostream
		 */
		HT_API std::ostream& operator<< (std::ostream& output, Quaternion& h);
		/** An extraction operator for a Quaterion to interace with an istream
		 * \param output The istream to input from
		 * \param h The Quaterion to be filled by the istream
		 */
		HT_API std::istream& operator>> (std::istream& input, Quaternion& h);
	}
}
