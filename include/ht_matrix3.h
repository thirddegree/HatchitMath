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
 * \class Matrix3
 * \ingroup HachitMath
 *
 * \brief A 3x3 Matrix
 *
 * A collection of 9 floats arranged in a two dimensional grid.
 */

#pragma once

#include <ht_platform.h>
#include <ht_vector3.h>

namespace Hatchit
{
	namespace Math
	{
		class Matrix4;

		class HT_API Matrix3
		{
		public:
			Matrix3();
			Matrix3(float rawArray[]);
			Matrix3(float x0, float y0, float z0,
				float x1, float y1, float z1,
				float x2, float y2, float z2);
			Matrix3(Vector3 one, Vector3 two, Vector3 three);

			//Accessors
			Matrix3 getTranspose();
			Matrix3 getInverse();
			float* getAsArray();

			//Operators
			Matrix3 operator* (Matrix3 mat);
			Vector3 operator* (Vector3 vec);
			operator Matrix4();

			float* operator[] (int i);

			~Matrix3();

		private:
			float rawMatrix[9];
			float matrix[3][3];
		};
	}
}
