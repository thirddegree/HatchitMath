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

#include <ht_matrix4.h>
#include <ht_matrix3.h>
#include <cassert>

namespace Hatchit {

    namespace Math {

        /*
        Statics
        */

        Matrix4 Matrix4::GetOrthographicProjection(float left, float right, float bottom, float top, float _near, float _far)
        {
            float a = 2 / (right - left);
            float b = 2 / (top - bottom);
            float c = -2 / (_far - _near);
            float d = -1 * ((right + left) / (right - left));
            float e = -1 * ((top + bottom) / (top - bottom));
            float f = -1 * ((_far + _near) / (_far - _near));

            return Matrix4(a, 0, 0, 0,
                           0, b, 0, 0,
                           0, 0, c, 0,
                           d, e, f, 1);
        }

        Matrix4 Matrix4::GetPerspectiveProjection(float fov, float aspect, float _near, float _far)
        {
            //thanks to https://stackoverflow.com/questions/18404890/how-to-build-perspective-projection-matrix-no-api
            float depth = _far - _near;
            float q = -(_far + _near) / depth;
            float qn = -2 * (_far * _near) / depth;

            float h = 1 / tanf(0.5f * fov);
            float w = h / aspect;

            return Matrix4(w, 0, 0, 0,
                           0, h, 0, 0,
                           0, 0, q, -1,
                           0, 0, qn, 0);
        }

        Matrix4 Matrix4::GetLookAtView(Vector3 lookAt, Vector3 center, Vector3 up)
        {
            //Calculate axes
            Vector3 zAxis = Vector3::Normalize((lookAt - center));
            Vector3 xAxis = Vector3::Normalize(Vector3::Cross(up, zAxis));
            Vector3 yAxis = Vector3::Cross(zAxis, xAxis);

            //Create view matrix;
            return Matrix4(xAxis.getX(), yAxis.getX(), zAxis.getX(), 0,
                           xAxis.getY(), yAxis.getY(), zAxis.getY(), 0,
                           xAxis.getZ(), yAxis.getZ(), zAxis.getZ(), 0,
                Vector3::Dot(xAxis * -1, lookAt),
                Vector3::Dot(yAxis * -1, lookAt),
                Vector3::Dot(zAxis * -1, lookAt),
                1);
        }

        /*
        Constructors
        */

        Matrix4::Matrix4()
        {
			float zero = 0;
			float one = 1;
			__m128 o = _mm_load_ss(&one);
			__m128 z = _mm_load_ss(&zero);
			this->m_rows[0] = o;
			this->m_rows[1] = _mm_movelh_ps(_mm_unpacklo_ps(z, o), _mm_unpacklo_ps(z, z));
			this->m_rows[2] = _mm_movelh_ps(_mm_unpacklo_ps(z, z), _mm_unpacklo_ps(o, z));
			this->m_rows[3] = _mm_movelh_ps(_mm_unpacklo_ps(z, z), _mm_unpacklo_ps(z, o));
        }

        Matrix4::Matrix4(float rawArray[])
        {
			__m128 xx = _mm_load_ss(&rawArray[0]);
			__m128 xy = _mm_load_ss(&rawArray[1]);
			__m128 xz = _mm_load_ss(&rawArray[2]);
			__m128 xw = _mm_load_ss(&rawArray[3]);
			__m128 yx = _mm_load_ss(&rawArray[4]);
			__m128 yy = _mm_load_ss(&rawArray[5]);
			__m128 yz = _mm_load_ss(&rawArray[6]);
			__m128 yw = _mm_load_ss(&rawArray[7]);
			__m128 zx = _mm_load_ss(&rawArray[8]);
			__m128 zy = _mm_load_ss(&rawArray[9]);
			__m128 zz = _mm_load_ss(&rawArray[10]);
			__m128 zw = _mm_load_ss(&rawArray[11]);
			__m128 wx = _mm_load_ss(&rawArray[12]);
			__m128 wy = _mm_load_ss(&rawArray[13]);
			__m128 wz = _mm_load_ss(&rawArray[14]);
			__m128 ww = _mm_load_ss(&rawArray[15]);

			this->m_rows[0] = _mm_movelh_ps(_mm_unpacklo_ps(xx, xy), _mm_unpacklo_ps(xz, xw));
			this->m_rows[1] = _mm_movelh_ps(_mm_unpacklo_ps(yx, yy), _mm_unpacklo_ps(yz, yw));
			this->m_rows[2] = _mm_movelh_ps(_mm_unpacklo_ps(zx, zy), _mm_unpacklo_ps(zz, zw));
			this->m_rows[3] = _mm_movelh_ps(_mm_unpacklo_ps(wx, wy), _mm_unpacklo_ps(wz, ww));
        }

        Matrix4:: Matrix4(	float xx, float xy, float xz, float xw,
							float yx, float yy, float yz, float yw,
							float zx, float zy, float zz, float zw,
							float wx, float wy, float wz, float ww)
        {
			__m128 xx0 = _mm_load_ss(&xx);
			__m128 xy0 = _mm_load_ss(&xy);
			__m128 xz0 = _mm_load_ss(&xz);
			__m128 xw0 = _mm_load_ss(&xw);
			__m128 yx0 = _mm_load_ss(&yx);
			__m128 yy0 = _mm_load_ss(&yy);
			__m128 yz0 = _mm_load_ss(&yz);
			__m128 yw0 = _mm_load_ss(&yw);
			__m128 zx0 = _mm_load_ss(&zx);
			__m128 zy0 = _mm_load_ss(&zy);
			__m128 zz0 = _mm_load_ss(&zz);
			__m128 zw0 = _mm_load_ss(&zw);
			__m128 wx0 = _mm_load_ss(&wx);
			__m128 wy0 = _mm_load_ss(&wy);
			__m128 wz0 = _mm_load_ss(&wz);
			__m128 ww0 = _mm_load_ss(&ww);

			this->m_rows[0] = _mm_movelh_ps(_mm_unpacklo_ps(xx0, xy0), _mm_unpacklo_ps(xz0, xw0));
			this->m_rows[1] = _mm_movelh_ps(_mm_unpacklo_ps(yx0, yy0), _mm_unpacklo_ps(yz0, yw0));
			this->m_rows[2] = _mm_movelh_ps(_mm_unpacklo_ps(zx0, zy0), _mm_unpacklo_ps(zz0, zw0));
			this->m_rows[3] = _mm_movelh_ps(_mm_unpacklo_ps(wx0, wy0), _mm_unpacklo_ps(wz0, ww0));
        }

		Matrix4::Matrix4(Vector3 a,
						 Vector3 b,
						 Vector3 c,
						 Vector3 d)
        {
			float zero = 0;
			float one = 1;
			__m128 o = _mm_load_ss(&one);
			__m128 z = _mm_load_ss(&zero);

			__m128 xx = _mm_load_ss(&a[0]);
			__m128 xy = _mm_load_ss(&a[1]);
			__m128 xz = _mm_load_ss(&a[2]);
			__m128 yx = _mm_load_ss(&b[0]);
			__m128 yy = _mm_load_ss(&b[1]);
			__m128 yz = _mm_load_ss(&b[2]);
			__m128 zx = _mm_load_ss(&c[0]);
			__m128 zy = _mm_load_ss(&c[1]);
			__m128 zz = _mm_load_ss(&c[2]);
			__m128 wx = _mm_load_ss(&d[0]);
			__m128 wy = _mm_load_ss(&d[1]);
			__m128 wz = _mm_load_ss(&d[2]);

			this->m_rows[0] = _mm_movelh_ps(_mm_unpacklo_ps(xx, xy), _mm_unpacklo_ps(xz, o));
			this->m_rows[1] = _mm_movelh_ps(_mm_unpacklo_ps(yx, yy), _mm_unpacklo_ps(yz, o));
			this->m_rows[2] = _mm_movelh_ps(_mm_unpacklo_ps(zx, zy), _mm_unpacklo_ps(zz, o));
			this->m_rows[3] = _mm_movelh_ps(_mm_unpacklo_ps(wx, wy), _mm_unpacklo_ps(wz, z));
        }

        Matrix4::Matrix4(Vector4 a,
						 Vector4 b,
						 Vector4 c,
						 Vector4 d)
        {
			__m128 xx = _mm_load_ss(&a[0]);
			__m128 xy = _mm_load_ss(&a[1]);
			__m128 xz = _mm_load_ss(&a[2]);
			__m128 xw = _mm_load_ss(&a[3]);
			__m128 yx = _mm_load_ss(&b[0]);
			__m128 yy = _mm_load_ss(&b[1]);
			__m128 yz = _mm_load_ss(&b[2]);
			__m128 yw = _mm_load_ss(&b[3]);
			__m128 zx = _mm_load_ss(&c[0]);
			__m128 zy = _mm_load_ss(&c[1]);
			__m128 zz = _mm_load_ss(&c[2]);
			__m128 zw = _mm_load_ss(&c[3]);
			__m128 wx = _mm_load_ss(&d[0]);
			__m128 wy = _mm_load_ss(&d[1]);
			__m128 wz = _mm_load_ss(&d[2]);
			__m128 ww = _mm_load_ss(&d[3]);

			this->m_rows[0] = _mm_movelh_ps(_mm_unpacklo_ps(xx, xy), _mm_unpacklo_ps(xz, xw));
			this->m_rows[1] = _mm_movelh_ps(_mm_unpacklo_ps(yx, yy), _mm_unpacklo_ps(yz, yw));
			this->m_rows[2] = _mm_movelh_ps(_mm_unpacklo_ps(zx, zy), _mm_unpacklo_ps(zz, zw));
			this->m_rows[3] = _mm_movelh_ps(_mm_unpacklo_ps(wx, wy), _mm_unpacklo_ps(wz, ww));
        }

        /*
        Accessors and Mutators
        */

        Matrix4 Matrix4::Transpose(const Matrix4& mat)
        {
			/*matrix shuffling to transpose is done in 3 steps
			* |01,02,03,04|    |01,02,05,06|    |01,05,02,06|    |01,05,09,13|
			* |05,06,07,08| -> |03,04,07,08| -> |03,07,04,08| -> |02,06,10,14|
			* |09,10,11,12|    |09,10,13,14|    |09,13,10,14|    |03,07,11,15|
			* |13,14,15,16|    |11,12,15,16|    |11,15,12,16|    |04,08,12,16|
			*/
            Matrix4 transpose;

			//first step
			__m128 a = _mm_shuffle_ps(mat.m_rows[0], mat.m_rows[1], _MM_SHUFFLE(1, 0, 1, 0));
			__m128 b = _mm_shuffle_ps(mat.m_rows[0], mat.m_rows[1], _MM_SHUFFLE(3, 2, 3, 2));
			__m128 c = _mm_shuffle_ps(mat.m_rows[2], mat.m_rows[3], _MM_SHUFFLE(1, 0, 1, 0));
			__m128 d = _mm_shuffle_ps(mat.m_rows[2], mat.m_rows[3], _MM_SHUFFLE(3, 2, 3, 2));

			//second step
			a = _mm_shuffle_ps(a, a, _MM_SHUFFLE(3, 1, 2, 0));
			b = _mm_shuffle_ps(b, b, _MM_SHUFFLE(3, 1, 2, 0));
			c = _mm_shuffle_ps(c, c, _MM_SHUFFLE(3, 1, 2, 0));
			d = _mm_shuffle_ps(d, d, _MM_SHUFFLE(3, 1, 2, 0));

			//third step
			transpose.m_rows[0] = _mm_shuffle_ps(a, c, _MM_SHUFFLE(1, 0, 1, 0));
			transpose.m_rows[1] = _mm_shuffle_ps(a, c, _MM_SHUFFLE(3, 2, 3, 2));
			transpose.m_rows[2] = _mm_shuffle_ps(b, d, _MM_SHUFFLE(1, 0, 1, 0));
			transpose.m_rows[3] = _mm_shuffle_ps(b, d, _MM_SHUFFLE(3, 2, 3, 2));

            return transpose;
        }

		float Matrix4::Determinant(const Matrix4& mat)
		{
			return 0;
		}

		Matrix4 Matrix4::Inverse(const Matrix4& mat, const float det)
        {
            Matrix4 inverse;

			
            //Inversion using Cramer's Rule adapted from https://graphics.stanford.edu/~mdfisher/Code/Engine/Matrix4.cpp.html
			/*
            float tmp[12]; //Temp array for pairs
            float src[16]; //Transpose of source matrix
            float determinant;

            //Transpose into float
            for (unsigned int i = 0; i < 4; i++)
            {
                src[i + 0] = matrix[i][0];
                src[i + 4] = matrix[i][1];
                src[i + 8] = matrix[i][2];
                src[i + 12] = matrix[i][3];
            }

            //Calculate pairs for first 8 elements (cofactors)
            tmp[0] = src[10] * src[15];
            tmp[1] = src[11] * src[14];
            tmp[2] = src[9] * src[15];
            tmp[3] = src[11] * src[13];
            tmp[4] = src[9] * src[14];
            tmp[5] = src[10] * src[13];
            tmp[6] = src[8] * src[15];
            tmp[7] = src[11] * src[12];
            tmp[8] = src[8] * src[14];
            tmp[9] = src[10] * src[12];
            tmp[10] = src[8] * src[13];
            tmp[11] = src[9] * src[12];
            //Calculate first 8 elements (cofactors)
            inverse[0][0] = tmp[0] * src[5] + tmp[3] * src[6] + tmp[4] * src[7];
            inverse[0][0] -= tmp[1] * src[5] + tmp[2] * src[6] + tmp[5] * src[7];
            inverse[0][1] = tmp[1] * src[4] + tmp[6] * src[6] + tmp[9] * src[7];
            inverse[0][1] -= tmp[0] * src[4] + tmp[7] * src[6] + tmp[8] * src[7];
            inverse[0][2] = tmp[2] * src[4] + tmp[7] * src[5] + tmp[10] * src[7];
            inverse[0][2] -= tmp[3] * src[4] + tmp[6] * src[5] + tmp[11] * src[7];
            inverse[0][3] = tmp[5] * src[4] + tmp[8] * src[5] + tmp[11] * src[6];
            inverse[0][3] -= tmp[4] * src[4] + tmp[9] * src[5] + tmp[10] * src[6];
            inverse[1][0] = tmp[1] * src[1] + tmp[2] * src[2] + tmp[5] * src[3];
            inverse[1][0] -= tmp[0] * src[1] + tmp[3] * src[2] + tmp[4] * src[3];
            inverse[1][1] = tmp[0] * src[0] + tmp[7] * src[2] + tmp[8] * src[3];
            inverse[1][1] -= tmp[1] * src[0] + tmp[6] * src[2] + tmp[9] * src[3];
            inverse[1][2] = tmp[3] * src[0] + tmp[6] * src[1] + tmp[11] * src[3];
            inverse[1][2] -= tmp[2] * src[0] + tmp[7] * src[1] + tmp[10] * src[3];
            inverse[1][3] = tmp[4] * src[0] + tmp[9] * src[1] + tmp[10] * src[2];
            inverse[1][3] -= tmp[5] * src[0] + tmp[8] * src[1] + tmp[11] * src[2];
            //Calculate pairs for second 8 elements (cofactors)
            tmp[0] = src[2] * src[7];
            tmp[1] = src[3] * src[6];
            tmp[2] = src[1] * src[7];
            tmp[3] = src[3] * src[5];
            tmp[4] = src[1] * src[6];
            tmp[5] = src[2] * src[5];

            tmp[6] = src[0] * src[7];
            tmp[7] = src[3] * src[4];
            tmp[8] = src[0] * src[6];
            tmp[9] = src[2] * src[4];
            tmp[10] = src[0] * src[5];
            tmp[11] = src[1] * src[4];
            //Calculate second 8 elements (cofactors)
            inverse[2][0] = tmp[0] * src[13] + tmp[3] * src[14] + tmp[4] * src[15];
            inverse[2][0] -= tmp[1] * src[13] + tmp[2] * src[14] + tmp[5] * src[15];
            inverse[2][1] = tmp[1] * src[12] + tmp[6] * src[14] + tmp[9] * src[15];
            inverse[2][1] -= tmp[0] * src[12] + tmp[7] * src[14] + tmp[8] * src[15];
            inverse[2][2] = tmp[2] * src[12] + tmp[7] * src[13] + tmp[10] * src[15];
            inverse[2][2] -= tmp[3] * src[12] + tmp[6] * src[13] + tmp[11] * src[15];
            inverse[2][3] = tmp[5] * src[12] + tmp[8] * src[13] + tmp[11] * src[14];
            inverse[2][3] -= tmp[4] * src[12] + tmp[9] * src[13] + tmp[10] * src[14];
            inverse[3][0] = tmp[2] * src[10] + tmp[5] * src[11] + tmp[1] * src[9];
            inverse[3][0] -= tmp[4] * src[11] + tmp[0] * src[9] + tmp[3] * src[10];
            inverse[3][1] = tmp[8] * src[11] + tmp[0] * src[8] + tmp[7] * src[10];
            inverse[3][1] -= tmp[6] * src[10] + tmp[9] * src[11] + tmp[1] * src[8];
            inverse[3][2] = tmp[6] * src[9] + tmp[11] * src[11] + tmp[3] * src[8];
            inverse[3][2] -= tmp[10] * src[11] + tmp[2] * src[8] + tmp[7] * src[9];
            inverse[3][3] = tmp[10] * src[10] + tmp[4] * src[8] + tmp[9] * src[9];
            inverse[3][3] -= tmp[8] * src[9] + tmp[11] * src[10] + tmp[5] * src[8];

            //Calculate inverse determinant
            determinant = src[0] * inverse[0][0] + src[1] * inverse[0][1] + src[2] * inverse[0][2] + src[3] * inverse[0][3];
            determinant = 1.0f / determinant;

            //Multiply inverse determinant to all memebers
            for (unsigned int i = 0; i < 4; i++)
            {
                for (unsigned int j = 0; j < 4; j++)
                {
                    inverse[i][j] *= determinant;
                }
            }
			*/
            return inverse;
        }

        const float* const Matrix4::getAsArray() const
        {
			static _MM_ALIGN16 float mat_array[16];

			_mm_store_ps(mat_array     , m_rows[0]);
			_mm_store_ps(mat_array +  4, m_rows[1]);
			_mm_store_ps(mat_array +  8, m_rows[2]);
			_mm_store_ps(mat_array + 12, m_rows[3]);

            return mat_array;
        }

        /*
        Operators
        */

        const float* const Matrix4::operator[] (int i) const
        {
			assert(0 <= i && i <= 3);
			const float* mat_array = getAsArray();
			return mat_array + 4*i;
        }

        Matrix4 Matrix4::operator*(const Matrix4 m)
        {
			Matrix4 result;

			//transpose the other matrix to get it as columns
			Matrix4 other = Transpose(m);

			//get the dot product of each row/column and put them into an array
			//rows
			for (int i = 0; i < 4; i++)
			{
				//columns
				__m128 a = _mm_mul_ps(m_rows[i], other.m_rows[0]);
				a = _mm_add_ps(a, _mm_shuffle_ps(a, a, _MM_SHUFFLE(0, 1, 2, 3)));
				a = _mm_add_ps(a, _mm_shuffle_ps(a, a, _MM_SHUFFLE(2, 3, 0, 1)));

				__m128 b = _mm_mul_ps(m_rows[i], other.m_rows[1]);
				b = _mm_add_ps(b, _mm_shuffle_ps(b, b, _MM_SHUFFLE(0, 1, 2, 3)));
				b = _mm_add_ps(b, _mm_shuffle_ps(b, b, _MM_SHUFFLE(2, 3, 0, 1)));

				__m128 c = _mm_mul_ps(m_rows[i], other.m_rows[2]);
				c = _mm_add_ps(c, _mm_shuffle_ps(c, c, _MM_SHUFFLE(0, 1, 2, 3)));
				c = _mm_add_ps(c, _mm_shuffle_ps(c, c, _MM_SHUFFLE(2, 3, 0, 1)));

				__m128 d = _mm_mul_ps(m_rows[i], other.m_rows[3]);
				d = _mm_add_ps(d, _mm_shuffle_ps(d, d, _MM_SHUFFLE(0, 1, 2, 3)));
				d = _mm_add_ps(d, _mm_shuffle_ps(d, d, _MM_SHUFFLE(2, 3, 0, 1)));

				//combine into one m128 and store in the new matrix
				result.m_rows[i] = _mm_movelh_ps(_mm_unpacklo_ps(a, b), _mm_unpacklo_ps(c, d));
			}

			return result; //newMat;
        }

        Vector3 Matrix4::operator*(Vector3 vec)
        {
			Vector3 result;

			__m128 x = _mm_mul_ps(m_rows[0], vec.m_vector);
			x = _mm_add_ps(x, _mm_shuffle_ps(x, x, _MM_SHUFFLE(0, 1, 2, 3)));
			x = _mm_add_ps(x, _mm_shuffle_ps(x, x, _MM_SHUFFLE(2, 3, 0, 1)));

			__m128 y = _mm_mul_ps(m_rows[1], vec.m_vector);
			y = _mm_add_ps(y, _mm_shuffle_ps(y, y, _MM_SHUFFLE(0, 1, 2, 3)));
			y = _mm_add_ps(y, _mm_shuffle_ps(y, y, _MM_SHUFFLE(2, 3, 0, 1)));

			__m128 z = _mm_mul_ps(m_rows[2], vec.m_vector);
			z = _mm_add_ps(z, _mm_shuffle_ps(z, z, _MM_SHUFFLE(0, 1, 2, 3)));
			z = _mm_add_ps(z, _mm_shuffle_ps(z, z, _MM_SHUFFLE(2, 3, 0, 1)));

			__m128 w = _mm_load_ss(0);

			result.m_vector = _mm_movelh_ps(_mm_unpacklo_ps(x, y), _mm_unpacklo_ps(z, w));

			return result;
        }

        Vector4 Matrix4::operator*(Vector4 vec)
        {
			Vector3 result;

			__m128 x = _mm_mul_ps(m_rows[0], vec.m_vector);
			x = _mm_add_ps(x, _mm_shuffle_ps(x, x, _MM_SHUFFLE(0, 1, 2, 3)));
			x = _mm_add_ps(x, _mm_shuffle_ps(x, x, _MM_SHUFFLE(2, 3, 0, 1)));

			__m128 y = _mm_mul_ps(m_rows[1], vec.m_vector);
			y = _mm_add_ps(y, _mm_shuffle_ps(y, y, _MM_SHUFFLE(0, 1, 2, 3)));
			y = _mm_add_ps(y, _mm_shuffle_ps(y, y, _MM_SHUFFLE(2, 3, 0, 1)));

			__m128 z = _mm_mul_ps(m_rows[2], vec.m_vector);
			z = _mm_add_ps(z, _mm_shuffle_ps(z, z, _MM_SHUFFLE(0, 1, 2, 3)));
			z = _mm_add_ps(z, _mm_shuffle_ps(z, z, _MM_SHUFFLE(2, 3, 0, 1)));

			__m128 w = _mm_mul_ps(m_rows[2], vec.m_vector);
			w = _mm_add_ps(w, _mm_shuffle_ps(w, w, _MM_SHUFFLE(0, 1, 2, 3)));
			w = _mm_add_ps(w, _mm_shuffle_ps(w, w, _MM_SHUFFLE(2, 3, 0, 1)));

			result.m_vector = _mm_movelh_ps(_mm_unpacklo_ps(x, y), _mm_unpacklo_ps(z, w));

			return result;
        }

        Matrix4::operator Matrix3()
        {
			Matrix3 result;

			float zero = 0;
			__m128 w = _mm_load_ss(&zero);

			result.m_rows[0] = _mm_movelh_ps(m_rows[0], _mm_unpackhi_ps(m_rows[0], w));
			result.m_rows[1] = _mm_movelh_ps(m_rows[1], _mm_unpackhi_ps(m_rows[1], w));
			result.m_rows[2] = _mm_movelh_ps(m_rows[2], _mm_unpackhi_ps(m_rows[2], w));

			return result; //mat;
        }

		//Extraction
		std::ostream& operator<<(std::ostream& output, Matrix4& m)
		{
			output	<< m[0][0] << " " << m[0][1] << " " << m[0][2] << " " << m[0][3] << std::endl
					<< m[1][0] << " " << m[1][1] << " " << m[1][2] << " " << m[1][3] << std::endl
					<< m[2][0] << " " << m[2][1] << " " << m[2][2] << " " << m[2][3] << std::endl
					<< m[3][0] << " " << m[3][1] << " " << m[3][2] << " " << m[3][3];
			return output;
		}

		//Insertion
		std::istream& operator>>(std::istream& input, Matrix4& m)
		{
			float	xx, xy, xz, xw,
					yx, yy, yz, yw,
					zx, zy, zz, zw,
					wx, wy, wz, ww;

			input	>> xx >> xy >> xz >> xw
					>> yx >> yy >> yz >> yw
					>> zx >> zy >> zz >> zw
					>> wx >> wy >> wz >> ww;

			m = Matrix4(xx, xy, xz, xw,
						yx, yy, yz, yw,
						zx, zy, zz, zw,
						wx, wy, wz, ww);

			return input;
		}
    }
}
