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
 * \ingroup HatchitMath
 *
 * \brief A 3x3 Matrix
 *
 * A collection of 9 floats arranged in a two dimensional grid.
 * This Matrix is row major and is laid out as such:
 * x1, y1, z1,
 * x2, y2, z2,
 * x3, y3, z3,
 */

#pragma once

#include <ht_platform.h>
#include <ht_vector3.h>

namespace Hatchit
{
	namespace Math
	{
		class HT_API Matrix3
		{
		friend class Matrix4;
		public:
			//Constructors
			///Create a 3x3 identity matrix
			Matrix3();
			///Creates a 3x3 matrix from an array of 9 values
			Matrix3(float rawArray[]);
			///Creates a 3x3 matrix from 9 given values
			Matrix3(float x0, float y0, float z0,
							float x1, float y1, float z1,
							float x2, float y2, float z2);
			///Creates a 3x3 matrix from 3 Vector3s where each Vector is a row
			Matrix3(Vector3 one, Vector3 two, Vector3 three);


			//Accessors
			/** Returns the transpose of this matrix as a Matrix3
			 * \return A Matrix3 that is the transpoe of this matrix
			 */
			Matrix3 getTranspose();
			/** Returns the inverse of this matrix as a Matrix3
			 * \return A Matrix3 that is the inverse of this matrix
			 */
			Matrix3 getInverse();
			/** Get this matrix as an array of values rather than a matrix
			 * This pointer is to an array on the stack which will be deleted when
			 * this matrix is disposed of.
			 * \return A float array containing all the values in this matrix
			 */
			float* getAsArray();

			//Operators
			/** Multiplies this Matrix3 by another given Matrix3 and returns the
			 * resulting matrix
			 * \param mat The other Matrix3 to multiply into this one
			 * \return The product of this matrix * mat as a Matrix3
			 */
			Matrix3 operator* (Matrix3 mat);
			/** Multiplies this Matrix3 by a given Vector3 and returns the
			 * resulting Vector3
			 * \param vec The Vector3 to multiply into this matrix
			 * \return The product of this matrix * vec as a Vector3
			 */
			Vector3 operator* (Vector3 vec);
			/** Operator to convert this Matrix3 to a Matrix4
			 * The resulting vector has all its new values set to 0 except for
			 * the last place which is set to a 1. The new Matrix will be laid out:
			 * x1, y1, z1, 0,
			 * x2, y2, z2, 0,
			 * x3, y3, z3, 0,
			 *  0,  0,  0, 1
			 */
			operator Matrix4();
			/** Fetches a row of this Matrix at the index i
			 * The subsequent row can also use this operator so you can access values
			 * in this matrix with two [] operators: myMatrix[0][1].
			 * \param i The index of the row to fetch
			 * \return A pointer to a float array which is a row of this matrix
			 * This will throw an index out of range exception if you try to access a
			 * 4th row with index 3.
			 */
			float* operator[] (int i);

		private:
			float matrix[3][3];
			__m128 m_rows[3];
		};
	}
}
