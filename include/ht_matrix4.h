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
 * xx, xy, xz, xw
 * yx, yy, yz, yw
 * zz, zy, zz, zw
 * wx, wy, wz, ww
 */

#pragma once

#define _USE_MATH_DEFINES

#include <ht_platform.h>
#include <ht_vector3.h>
#include <ht_vector4.h>
#include <cmath>

namespace Hatchit
{
	namespace Math
	{
		class Matrix3;

		class HT_API Matrix4
		{
		friend class Quaternion;

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
			Matrix4(float xx, float xy, float xz, float xw,
					float yx, float yy, float yz, float yw,
					float zx, float zy, float zz, float zw,
					float wx, float wy, float wz, float ww);
			/** Creates a 4x4 matrix from 4 given Vector3s
			* The resulting matrix fills in a few values so that it will match this
			* layout:
			* a1, a2, a3, 0
			* b1, b2, b3, 0
			* c1, c2, c3, 0
			* d1, d2, d3, 1
			*/
			Matrix4(Vector3 a, Vector3 b, Vector3 c, Vector3 d);
			/** Creates a 4x4 matrix from 4 given Vector4s
			* The resulting matrix fills in a few values so that it will match this
			* layout:
			* a1, a2, a3, a4
			* b1, b2, b3, b4
			* c1, c2, c3, c4
			* d1, d2, d3, d4
			*/
			Matrix4(Vector4 a, Vector4 b, Vector4 c, Vector4 d);

			/** Returns the transpose of a matrix as a Matrix4
			 * \param mat matrix to transpose
			 * \return A Matrix4 that is the transpoe of this matrix
			 */
			static Matrix4 Transpose(const Matrix4& mat);


			/** Returns the inverse of this matrix as a Matrix4
			 * \param mat matrix to invert
			 * \return A Matrix4 that is the inverse of this matrix
			 */
			static Matrix4 Inverse(const Matrix4& mat);



			//Accessors
			/** Get this matrix as an array of values rather than a matrix
			 * This pointer is to an array on the stack which will be deleted when
			 * this matrix is disposed of.
			 * \return A float array containing all the values in this matrix
			 */
			const float* const getAsArray() const;

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

		public:
			union
			{
				__m128 m_rows[4];
				struct
				{
					float	xx, xy, xz, xw,
							yx, yy, yz, yw,
							zx, zy, zz, zw,
							wx, wy, wz, ww;
				};
				float data[16];
			};
		};


		/** An insertion operator for a Matrix4 to interace with an ostream
		* \param output The ostream to output to
		* \param h The Matrix4 to interface with the ostream
		*/
		HT_API std::ostream& operator<< (std::ostream& output, Matrix4& h);
		/** An insertion operator for a Matrix4 to interace with an ostream
		* \param output The ostream to output to
		* \param h The Matrix4 to interface with the ostream
		*/
		HT_API std::istream& operator>> (std::istream& input, Matrix4& h);
	}
}
