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

#include <ht_vector2.h>
#include <ht_vector3.h>
#include <ht_vector4.h>
#include <ht_malloc.h>

namespace Hatchit {

    namespace Math {

        /*
        Constructors
        */
        Vector3::Vector3()
        {
			float zero;
			this->m_vector = _mm_load_ps1(&zero);
        }

        Vector3::Vector3(float x, float y, float z)
        {
			float zero = 0;

			__m128 xx = _mm_load_ss(&x);
			__m128 xy = _mm_load_ss(&y);
			__m128 xz = _mm_load_ss(&z);
			__m128 xw = _mm_load_ss(&zero);

			this->m_vector = _mm_movelh_ps(_mm_unpacklo_ps(xx, xy), _mm_unpacklo_ps(xz, xw));
        }

        Vector3::Vector3(const Vector3& other)
        {
			this->m_vector = other.m_vector;
        }

        Vector3::Vector3(Vector4& v4)
        {
            //We'll just ignore the last element of the __m128 so just do a copy by value
			this->m_vector = (__m128)v4;

			_MM_ALIGN16 float temp[4];
			_mm_store_ps(temp, m_vector);
			m_vector = _mm_set_ps(0, temp[2], temp[1], temp[0]);
        }

		void* Vector3::operator new(size_t _size)
		{
    		return aligned_malloc(sizeof(__m128), _size);
		}

		void Vector3::operator delete(void* p)
		{
			aligned_free(p);
		}

		Vector3::operator const __m128(void) const
		{
			return m_vector;
		}

        /*
        Accessors & Mutators
        */

		float Vector3::getX()
		{
			float x;
			_mm_store_ss(&x, m_vector);

			return x;
		}
		float Vector3::getY()
		{
			float y;
			_mm_store_ss(&y, _mm_shuffle_ps(m_vector, m_vector, _MM_SHUFFLE(1, 1, 1, 1)));

			return y;
		}
		float Vector3::getZ()
		{
			float z;
			_mm_store_ss(&z, _mm_movehl_ps(m_vector, m_vector));

			return z;
		}

		float Vector3::getMagnitude()
		{
			Scalar mag = (*this) * (*this);
			mag = _mm_sqrt_ps(mag);

			return (float)mag;
		}
		
		float* Vector3::getAsArray()
		{
			static _MM_ALIGN16 float vec_array[4];
			_mm_store_ps(vec_array, m_vector);
			return vec_array;
		}

		void Vector3::setX(float x)
		{
			_MM_ALIGN16 float temp[4];
			_mm_store_ps(temp, m_vector);

			m_vector = _mm_set_ps(temp[3], temp[2], temp[1], x);
		}
		void Vector3::setY(float y)
		{
			_MM_ALIGN16 float temp[4];
			_mm_store_ps(temp, m_vector);

			m_vector = _mm_set_ps(temp[3], temp[2], y, temp[0]);
		}
		void Vector3::setZ(float z)
		{
			_MM_ALIGN16 float temp[4];
			_mm_store_ps(temp, m_vector);

			m_vector = _mm_set_ps(temp[3], z, temp[1], temp[0]);
		}

        /*
        Static Functions
        */

        //Cross product between vectors
        Vector3 Vector3::Cross(Vector3 v, Vector3 u)
        {
            Vector3 output;

			__m128 x00 = _mm_shuffle_ps(v.m_vector, v.m_vector, _MM_SHUFFLE(3, 0, 2, 1));
			__m128 x10 = _mm_shuffle_ps(u.m_vector, u.m_vector, _MM_SHUFFLE(3, 1, 0, 2));
			__m128 x01 = _mm_shuffle_ps(v.m_vector, v.m_vector, _MM_SHUFFLE(3, 1, 0, 2));
			__m128 x11 = _mm_shuffle_ps(u.m_vector, u.m_vector, _MM_SHUFFLE(3, 0, 2, 1));

			 x00 = _mm_mul_ps(x00, x10);
			 x11 = _mm_mul_ps(x01, x11);

			__m128 val = _mm_sub_ps(x00, x11);

			output.m_vector = val;
            return output;
        }

        //Dot product between two vectors
        float Vector3::Dot(Vector3 v, Vector3 u)
        {
			__m128 temp;
			__m128 sq = _mm_mul_ps(v.m_vector, u.m_vector);
			temp = _mm_add_ps(sq, _mm_shuffle_ps(sq, sq, _MM_SHUFFLE(3, 1, 0, 2)));
			temp = _mm_add_ps(temp, _mm_shuffle_ps(sq, sq, _MM_SHUFFLE(3, 0, 2, 1)));
			return (float)Scalar(temp);
        }

        //Normalize a vector
        Vector3 Vector3::Normalize(Vector3 v)
        {
            float magnitude = v.getMagnitude();

            if (magnitude == 0)
                magnitude = 1;

			Vector3 normalizedVec;

			float invMag = 1 / magnitude;
			normalizedVec.m_vector = _mm_mul_ps(v.m_vector, Scalar(invMag));

            return normalizedVec;
        }

        /*
        Operators
        */

        //Scalar operators
        Vector3 Vector3::operator*(float s)
        {
			Vector3 vec;

			__m128 product = _mm_mul_ps(m_vector, Scalar(s));

			vec.m_vector = product;

			return vec;
        }
        Vector3 Vector3::operator/(float s)
        {
			Vector3 vec;

			//Do division only once and then multiply by the inverse
			float invS = 1 / s; 
			__m128 product = _mm_mul_ps(m_vector, Scalar(invS));

			vec.m_vector = product;

			return vec;
        }
        Vector3 Vector3::operator-(float s)
        {
			Vector3 vec;

			__m128 product = _mm_sub_ps(m_vector, Scalar(s));

			vec.m_vector = product;

			return vec;
        }
        Vector3 Vector3::operator+(float s)
        {
			Vector3 vec;

			__m128 product = _mm_add_ps(m_vector, Scalar(s));

			vec.m_vector = product;

			return vec;
        }

        Vector3 Vector3::operator*=(float s)
        {
			m_vector = _mm_mul_ps(m_vector, Scalar(s));

            return (*this);
        }
        Vector3 Vector3::operator/=(float s)
        {
			//Do division only once and then multiply by the inverse
			float invS = 1 / s;

			m_vector = _mm_mul_ps(m_vector, Scalar(invS));

			return (*this);
        }
        Vector3 Vector3::operator-=(float s)
        {
			m_vector = _mm_sub_ps(m_vector, Scalar(s));

			return (*this);
        }
        Vector3 Vector3::operator+=(float s)
        {
			m_vector = _mm_add_ps(m_vector, Scalar(s));

			return (*this);
        }

        bool Vector3::operator>(Vector3 u){ return getMagnitude() > u.getMagnitude(); }
        bool Vector3::operator<(Vector3 u){ return getMagnitude() < u.getMagnitude(); }
        bool Vector3::operator==(Vector3 u)
        {
			return _mm_movemask_ps(_mm_cmpeq_ps(m_vector, u.m_vector)) == 15;
        }
        bool Vector3::operator!=(Vector3 u)
        {
			return _mm_movemask_ps(_mm_cmpeq_ps(m_vector, u.m_vector)) != 15;
        }

        //Vector operators
        float Vector3::operator* (Vector3 u)
        {
			__m128 temp;
			__m128 sq = _mm_mul_ps(m_vector, u.m_vector);
			temp = _mm_add_ps(sq, _mm_shuffle_ps(sq, sq, _MM_SHUFFLE(3, 1, 0, 2)));
			temp = _mm_add_ps(temp, _mm_shuffle_ps(sq, sq, _MM_SHUFFLE(3, 0, 2, 1)));
			return (float)Scalar(temp);
        }
        Vector3 Vector3::operator+(Vector3 u)
        {
			Vector3 vec;

			__m128 sum = _mm_add_ps(m_vector, u.m_vector);

			vec.m_vector = sum;

			return vec;
        }
        Vector3 Vector3::operator-(Vector3 u)
        {
			Vector3 vec;

			__m128 diff = _mm_sub_ps(m_vector, u.m_vector);

			vec.m_vector = diff;

			return vec;
        }
        Vector3 Vector3::operator+=(Vector3 u)
        {
			m_vector = _mm_add_ps(m_vector, u.m_vector);

			return (*this);
        }
        Vector3 Vector3::operator-=(Vector3 u)
        {
			m_vector = _mm_sub_ps(m_vector, u.m_vector);

			return (*this);
        }

        float& Vector3::operator[](int i)
        {
			float* vec_array = getAsArray();
			return vec_array[i];
        }

        Vector3::operator Vector4()
        {
			_MM_ALIGN16 float temp[4];
			_mm_store_ps(temp, m_vector);
            return Vector4(temp[0], temp[1], temp[2], 1.0f);
        }

        Vector3::operator Vector2()
        {
			_MM_ALIGN16 float temp[4];
			_mm_store_ps(temp, m_vector);
            return Vector2(temp[0], temp[1]);
        }


        //Extraction
        std::ostream& operator<<(std::ostream& output, Vector3& v)
        {
            output << v.getX() << " " << v.getY() << " " << v.getZ();
            return output;
        }

        //Insertion
        std::istream& operator>>(std::istream& input, Vector3& v)
        {
            float x, y, z;
            input >> x >> y >> z;

            v.setX(x);
            v.setY(y);
            v.setZ(z);

            return input;
        }


    }
}
