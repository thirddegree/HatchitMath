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
 * \ingroup HatchitMath
 *
 * \brief A 4x4 Matrix
 *
 * A collection of 16 floats arranged in a two dimensional grid.
 * This Matrix is row major and is laid out as such:
 * x1, y1, z1, w1
 * x2, y2, z2, w2
 * x3, y3, z3, w3
 * x4, y4, z4, w4
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
			//Statics
			/** Generates an orthographic projection from the given values
			 * \param left The lefthand bound
			 * \param right The righthand bound
			 * \param top The topmost bound
			 * \param _near The near plane
			 * \param _far The far plane
			 * \return The resulting orthographic projection in a Matrix4
			 */
			static Matrix4 GetOrthographicProjection(float left, float right, float bottom, float top, float _near, float _far);
			/** Generates a perspective projection from the given values
			 * \param fov The field of view
			 * \param aspect The aspect ratio
			 * \param near The _near plane
			 * \param far The _far plane
			 * \return The resulting perspective projection in a Matrix4
			 */
			static Matrix4 GetPerspectiveProjection(float fov, float aspect, float _near, float _far);
			/** Generates a view matrix from the given values
			 * \param lookAt The point for the camera to look at
			 * \param center The point that the camera is located
			 * \param up The vector representing which way is up for this camera
			 * \return The resulting view matrix in a Matrix4
			 */
			static Matrix4 GetLookAtView(Vector3 lookAt, Vector3 center, Vector3 up);

			//Constructors
			///Creates a 4x4 identity matrix
			Matrix4();
			///Creates a 4x4 matrix from an array of 16 values
			Matrix4(float rawArray[]);
			///Creates a 4x4 matrix from 16 given values
			Matrix4(float x0, float y0, float z0, float w0,
						  float x1, float y1, float z1, float w1,
							float x2, float y2, float z2, float w2,
						 	float x3, float y3, float z3, float w3);
			/** Creates a 4x4 matrix from 4 given Vector3s
			 * The resulting matrix fills in a few values so that it will match this
			 * layout:
			 * x1, y1, z1, 0
			 * x2, y2, z2, 0
			 * x3, y3, z3, 0
			 * x4, y4, z4, 1
			 */
			Matrix4(Vector3 one, Vector3 two, Vector3 three, Vector3 four);
			///Creates a 4x4 matrix from 4 Vector4s where each vector represents a row
			Matrix4(Vector4 one, Vector4 two, Vector4 three, Vector4 four);

			virtual ~Matrix4();

			//Accessors
			/** Returns the transpose of this matrix as a Matrix4
			 * \return A Matrix4 that is the transpoe of this matrix
			 */
			Matrix4 getTranspose();
			/** Returns the inverse of this matrix as a Matrix4
			 * \return A Matrix4 that is the inverse of this matrix
			 */
			Matrix4 getInverse();
			/** Get this matrix as an array of values rather than a matrix
			 * This pointer is to an array on the stack which will be deleted when
			 * this matrix is disposed of.
			 * \return A float array containing all the values in this matrix
			 */
			float* getAsArray();

			//Operators
			/** Multiplies this Matrix4 by another given Matrix4 and returns the
			 * resulting matrix
			 * \param mat The other Matrix4 to multiply into this one
			 * \return The product of this matrix * mat as a Matrix4
			 */
			Matrix4 operator* (Matrix4 mat);
			/** Multiplies this Matrix4 by a given Vector3 and returns the
			 * resulting Vector3
			 * \param vec The Vector3 to multiply into this matrix
			 * \return The product of this matrix * vec as a Vector3
			 */
			Vector3 operator* (Vector3 vec);
			/** Multiplies this Matrix4 by a given Vector4 and returns the
			 * resulting Vector4
			 * \param vec The Vector4 to multiply into this matrix
			 * \return The product of this matrix * vec as a Vector4
			 */
			Vector4 operator* (Vector4 vec);
			/** Operator to convert this Matrix4 to a Matrix3
			 * The resulting matrix will be trimmed
			 * The new Matrix will be laid out:
			 * x1, y1, z1,
			 * x2, y2, z2,
			 * x3, y3, z3
			 */
			operator Matrix3();
			/** Fetches a row of this Matrix at the index i
			 * The subsequent row can also use this operator so you can access values
			 * in this matrix with two [] operators: myMatrix[0][1].
			 * \param i The index of the row to fetch
			 * \return A pointer to a float array which is a row of this matrix
			 * This will throw an index out of range exception if you try to access a
			 * 5th row with index 4.
			 */
			float* operator[] (int i);

		private:
			float matrix[4][4];
		};
	}
}
