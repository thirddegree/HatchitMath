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

#include <ht_quaternion.h>
#include <ht_matrix4.h>

namespace Hatchit {

    namespace Math {

        /*
        Constructors
        */

        Quaternion::Quaternion()
        {
			float zero = 0;
			__m128 z = _mm_load_ps1(&zero);
        }

		Quaternion::Quaternion(float * m_vector)
		{
			this->m_vector = _mm_loadu_ps(m_vector);
		}

        Quaternion::Quaternion(float w, float x, float y, float z)
        {
			_MM_ALIGN16 float temp[4];
			temp[0] = w;
			temp[1] = x;
			temp[2] = y;
			temp[3] = z;
			this->m_vector = _mm_load_ps(temp);
        }

        //Assuming from euler angles
        Quaternion::Quaternion(Vector3 v)
        {
            //Thanks to: http://www.euclideanspace.com/maths/geometry/rotations/conversions/eulerToQuaternion/
            //Attitude = X rotation = pitch
            //Heading = Y rotation = yaw
            //Bank = Z rotation = roll

            float attitudeCos = cosf(v[0] / 2.0f);
            float attitudeSin = sinf(v[0] / 2.0f);

            float headingCos = cosf(v[1] / 2.0f);
            float headingSin = sinf(v[1] / 2.0f);

            float bankCos = cosf(v[2] / 2.0f);
            float bankSin = sinf(v[2] / 2.0f);

            float temp[4];

			temp[0] = (headingCos * attitudeCos * bankCos) -
                (headingSin * attitudeSin * bankSin);
			temp[2] = (headingSin * attitudeSin * bankCos) +
                (headingCos * attitudeCos * bankSin);
			temp[2] = (headingSin * attitudeCos * bankCos) +
                (headingCos * attitudeSin * bankSin);
			temp[3] = (headingCos * attitudeSin * bankCos) +
                (headingSin * attitudeCos * bankSin);

			
			this->m_vector = _mm_load_ps(temp);
        }

        //Assuming from Angle-Axis
        Quaternion::Quaternion(Vector4 v)
        {
            float halfAngle = v[3] / 2.0f;

			_MM_ALIGN16 float temp[4];

			temp[0] = cosf(halfAngle);
			temp[1] = v[0] * sinf(halfAngle);
			temp[2] = v[1] * sinf(halfAngle);
			temp[3] = v[2] * sinf(halfAngle);

			m_vector = _mm_load_ps(temp);
        }

        Quaternion::~Quaternion(void)
        {
        }

        Quaternion Quaternion::getInverse()
        {
			Quaternion result;
			result.m_vector = _mm_shuffle_ps(m_vector, m_vector, _MM_SHUFFLE(0, 1, 2, 3));
			return result;
        }

        Quaternion Quaternion::getQuaternionIdentity()
        {
            return Quaternion(0, 0, 0, 1);
        }

        Vector4 Quaternion::getAxisAngle()
        {
			Vector4 result;

			__m128 sq = _mm_mul_ps(m_vector, m_vector);
			sq =	_mm_add_ps(	_mm_shuffle_ps(sq, sq, _MM_SHUFFLE(1, 1, 1, 1)),
					_mm_add_ps(	_mm_shuffle_ps(sq, sq, _MM_SHUFFLE(2, 2, 2, 2)),
								_mm_shuffle_ps(sq, sq, _MM_SHUFFLE(3, 3, 3, 3))));
			sq = _mm_sqrt_ss(sq);
			sq = _mm_shuffle_ps(sq, sq, _MM_SHUFFLE(0, 0, 0, 0));

			sq = _mm_div_ps(m_vector, sq);

			float angle;
			_mm_store_ss(&angle, m_vector);
			angle = acos(angle) * 2.0f;
			__m128 a = _mm_load_ss(&angle);

			sq = _mm_move_ss(sq, a);
			sq = _mm_shuffle_ps(sq, sq, _MM_SHUFFLE(0, 3, 2, 1));
			result.m_vector = sq;
			return result;
        }

        Matrix4 Quaternion::getRotationMatrix()
        {
			//used to store temp variables for calculations
			float temp;

			//m00 m11 m22
			__m128 diag = _mm_mul_ps(m_vector, m_vector);

			//stored as ysq + zsq, xsq + zsq, xsq+ysq, wsq+wsq (w unused)
			diag = _mm_add_ps(_mm_shuffle_ps(diag, diag, _MM_SHUFFLE(0, 1, 3, 2)),
							_mm_shuffle_ps(diag, diag, _MM_SHUFFLE(0, 2, 1, 3)));

			//sub from .5 (-.5 to .5 range)
			temp = .5f;
			__m128 var = _mm_load1_ps(&temp);
			diag = _mm_sub_ps(var, diag);

			//mult all by 2 (-1 to 1 range)
			temp = 2;
			var = _mm_load1_ps(&temp);
			diag = _mm_mul_ps(diag, var);

			//xy, yz, zx, ww
			__m128 cross = _mm_mul_ps(m_vector, _mm_shuffle_ps(m_vector, m_vector, _MM_SHUFFLE(3, 0, 2, 1)));

			//xw, yw, zw, ww
			__m128 wscaled = _mm_mul_ps(m_vector, _mm_shuffle_ps(m_vector, m_vector, _MM_SHUFFLE(3, 3, 3, 3)));

			wscaled = _mm_shuffle_ps(wscaled, wscaled, _MM_SHUFFLE(3, 1, 0, 2));

			//m01 m12 m20 junk (addition)
			__m128 add = _mm_add_ps(cross, wscaled);
			//m10 m21 m02 junk (subtraction)
			__m128 sub = _mm_sub_ps(cross, wscaled);

			//multiply by var (currently 2)
			add = _mm_mul_ps(add, var);
			sub = _mm_mul_ps(sub, var);


			//begin constructing matrix
			Matrix4 result;

			__m128 zero;
			//build first row backwards
			var = _mm_shuffle_ps(sub, add, _MM_SHUFFLE(0, 0, 3, 3));
			//insert zero in front
			var = _mm_move_ss(var, zero);
			//flip and put m00 from diagonal in front
			var = _mm_move_ss(_mm_shuffle_ps(var, var, _MM_SHUFFLE(0, 1, 2, 3)), diag);
			//insert row into matrix
			result.m_rows[0] = var;


			//build second row backwards
			var = _mm_shuffle_ps(diag, add, _MM_SHUFFLE(1, 1, 1, 1));
			//insert zero in front
			var = _mm_move_ss(var, zero);
			//flip and put m10 from sub in front
			var = _mm_move_ss(_mm_shuffle_ps(var, var, _MM_SHUFFLE(0, 1, 2, 3)), sub);
			//insert row into matrix
			result.m_rows[1] = var;


			//build third row backwards
			var = _mm_shuffle_ps(sub, diag, _MM_SHUFFLE(2, 2, 1, 1));
			//insert zero in front
			var = _mm_move_ss(var, zero);
			//flip and put m20 from add in front
			var = _mm_move_ss(_mm_shuffle_ps(var, var, _MM_SHUFFLE(0, 1, 2, 3)), _mm_shuffle_ps(add, add, _MM_SHUFFLE(2, 2, 2, 2)));
			//insert row into matrix
			result.m_rows[2] = var;

			//fourth row
			var = _mm_setzero_ps();
			var = _mm_set_ss(1);
			var = _mm_shuffle_ps(var, var, _MM_SHUFFLE(0, 1, 2, 3));
			result.m_rows[3] = var;

            return result;
        }

        void Quaternion::normalize()
        {
			m_vector = _mm_mul_ps(m_vector, m_vector);
			m_vector = _mm_add_ps(m_vector, _mm_shuffle_ps(m_vector, m_vector, _MM_SHUFFLE(2, 3, 0, 1)));
			m_vector = _mm_add_ps(m_vector, _mm_shuffle_ps(m_vector, m_vector, _MM_SHUFFLE(0, 1, 2, 3)));

			float x;
			_mm_store_ss(&x, m_vector);
			if (x == 0) {
				x = 1;
				_mm_store_ps(&x, m_vector);
			}

			m_vector = _mm_sqrt_ss(m_vector);
			m_vector = _mm_mul_ps(m_vector, m_vector);
        }


        /*
        Operators
        */

        Quaternion Quaternion::operator*(Quaternion o)
        {
			//multiply together
			__m128 dot = _mm_mul_ps(m_vector, o.m_vector);
			//add together
			dot =	_mm_add_ps(	_mm_shuffle_ps(dot, dot, _MM_SHUFFLE(1, 1, 1, 1)),
					_mm_add_ps(	_mm_shuffle_ps(dot, dot, _MM_SHUFFLE(2, 2, 2, 2)),
								_mm_shuffle_ps(dot, dot, _MM_SHUFFLE(3, 3, 3, 3))));
			
			//get cross product
			__m128 prodVector;
			__m128 x00 = _mm_shuffle_ps(m_vector, m_vector, _MM_SHUFFLE(3, 0, 2, 1));
			__m128 x10 = _mm_shuffle_ps(o.m_vector, o.m_vector, _MM_SHUFFLE(3, 1, 0, 2));
			__m128 x01 = _mm_shuffle_ps(m_vector, m_vector, _MM_SHUFFLE(3, 1, 0, 2));
			__m128 x11 = _mm_shuffle_ps(o.m_vector, o.m_vector, _MM_SHUFFLE(3, 0, 2, 1));
			x00 = _mm_mul_ps(x00, x10);
			x11 = _mm_mul_ps(x01, x11);
			prodVector = _mm_sub_ps(x00, x11);

			//calc w
			__m128 prodScalar = _mm_mul_ss(m_vector, o.m_vector);
			prodScalar = _mm_sub_ss(prodScalar, dot);
			
			//calc xyz
			prodVector = _mm_add_ps(prodVector, _mm_mul_ps(o.m_vector, _mm_shuffle_ps(m_vector, m_vector, 0x00)));
			prodVector = _mm_add_ps(prodVector, _mm_mul_ps(m_vector, _mm_shuffle_ps(o.m_vector, o.m_vector, 0x00)));
			//reorder and put w in front
			prodVector = _mm_shuffle_ps(prodVector, prodVector, _MM_SHUFFLE(2, 1, 0, 3));
			prodVector = _mm_move_ss(prodVector, prodScalar);

			Quaternion result;
			result.m_vector = prodVector;

			return result;
        }

        //Extraction
        std::ostream& operator<<(std::ostream& output, Quaternion& q)
        {
            output << q.w << "," << q.x << "," << q.y << "," << q.z;
            return output;
        }

        //Insertion
        std::istream& operator>> (std::istream& input, Quaternion& q)
        {
            input >> q.w >> q.x >> q.y >> q.z;
            return input;
        }
    }

}
