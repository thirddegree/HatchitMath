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
 * \class Matrix4
 * \ingroup HachitMath
 *
 * \brief A 4x4 Matrix
 *
 * A collection of 16 floats arranged in a two dimensional grid.
 */

#pragma once

#define _USE_MATH_DEFINES

#include <ht_platform.h>
#include <ht_vector3.h>
#include <ht_vector4.h>

namespace Hatchit
{
	namespace Math
	{
		class Matrix3;

		class HT_API Matrix4
		{
		public:
			Matrix4();
			Matrix4(float rawArray[]);
			Matrix4(float x0, float y0, float z0, float w0,
				float x1, float y1, float z1, float w1,
				float x2, float y2, float z2, float w2,
				float x3, float y3, float z3, float w3);
			Matrix4(Vector3 one, Vector3 two, Vector3 three, Vector3 four);
			Matrix4(Vector4 one, Vector4 two, Vector4 three, Vector4 four);

			static Matrix4 getIdentityMatrix();

			static Matrix4 getOrthographicProjection(float left, float right, float bottom, float top, float _near, float _far);
			static Matrix4 getPerspectiveProjection(float fov, float aspect, float _near, float _far);

			static Matrix4 getLookAtView(Vector3 eye, Vector3 center, Vector3 up);

			//Accessors
			Matrix4 getTranspose();
			Matrix4 getInverse();
			float* getAsArray();

			//Operators
			float* operator[] (int i);
			Matrix4 operator* (Matrix4 mat);
			Vector3 operator* (Vector3 vec);
			Vector4 operator* (Vector4 vec);

			operator Matrix3();

			~Matrix4();

		private:
			float rawMatrix[16];
			float matrix[4][4];
		};
	}
}
