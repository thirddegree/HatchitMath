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
 * This quaternion is represented similarly to a Vector4 with X, Y, Z and W.
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
			Quaternion();
			Quaternion(float x, float y, float z, float w);
			Quaternion(Vector3 v);
			Quaternion(Vector4 v);

			~Quaternion();

			static Quaternion getQuaternionIdentity();

			Quaternion getInverse();
			Vector4 getAxisAngle();
			Matrix3 getRotationMatrix();

			//Accessors and mutators
			float getX();
			float getY();
			float getZ();
			float getW();

			void setX(float x);
			void setY(float y);
			void setZ(float z);
			void setW(float w);

			float& operator[] (int i);
			Quaternion operator* (Quaternion other);

			friend std::ostream& operator<< (std::ostream& output, Quaternion& h);
			friend std::istream& operator>> (std::istream& input, Quaternion& h);

		private:
			float q[4];
			void normalize();
		};
	}
}
