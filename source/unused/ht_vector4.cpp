/**
**    Hatchit Engine
**    Copyright(c) 2015 Third-Degree
**
**    GNU Lesser General Public License
**    This file may be used under the terms of the GNU Lesser
**    General Public License version 4 as published by the Free
**    Software Foundation and appearing in the file LICENSE.LGPLv4 included
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
		Vector4::Vector4()
		{
			float zero;
			this->m_vector = _mm_load_ps1(&zero);
		}

		Vector4::Vector4(float x, float y, float z, float w)
		{
			__m128 xx = _mm_load_ss(&x);
			__m128 xy = _mm_load_ss(&y);
			__m128 xz = _mm_load_ss(&z);
			__m128 xw = _mm_load_ss(&w);

			this->m_vector = _mm_movelh_ps(_mm_unpacklo_ps(xx, xy), _mm_unpacklo_ps(xz, xw));
		}

		Vector4::Vector4(const Vector4& other)
		{
			this->m_vector = other.m_vector;
		}

		Vector4::Vector4(Vector3& v3, float w)
		{
			this->m_vector = (__m128)v3;

			this->m_vector = _mm_shuffle_ps(m_vector, m_vector, _MM_SHUFFLE(0, 1, 2, 3));
			__m128 xw = _mm_load_ss(&w);


			m_vector = _mm_move_ss(m_vector, xw);
			this->m_vector = _mm_shuffle_ps(m_vector, m_vector, _MM_SHUFFLE(0, 1, 2, 3));
		}

		void* Vector4::operator new(size_t _size)
		{
		    return aligned_malloc(sizeof(__m128), _size);
		}

		void Vector4::operator delete(void* p)
		{
			aligned_free(p);
		}

		Vector4::operator const __m128(void) const
		{
			return m_vector;
		}


		//magnitude of this vector squared
		float Vector4::magSqr()
		{
			__m128 val = _mm_mul_ps(m_vector, m_vector);
			val = _mm_add_ps(val, _mm_shuffle_ps(val, val, _MM_SHUFFLE(2, 3, 0, 1)));
			val = _mm_add_ps(val, _mm_shuffle_ps(val, val, _MM_SHUFFLE(0, 1, 2, 3)));
			float x;
			_mm_store_ss(&x, m_vector);
			return x;
		}

		//magnitude of this vector
		float Vector4::mag()
		{
			__m128 val = _mm_mul_ps(m_vector, m_vector);
			val = _mm_add_ps(val, _mm_shuffle_ps(val, val, _MM_SHUFFLE(2, 3, 0, 1)));
			val = _mm_add_ps(val, _mm_shuffle_ps(val, val, _MM_SHUFFLE(0, 1, 2, 3)));
			val = _mm_sqrt_ss(val);
			float x;
			_mm_store_ss(&x, m_vector);
			return x;
		}

		//Normalize a vector
		Vector4 Vector4::normalized()
		{
			Vector4 normalized;
			normalized.m_vector = _mm_mul_ps(m_vector, m_vector);
			normalized.m_vector = _mm_add_ps(normalized.m_vector, _mm_shuffle_ps(normalized.m_vector, normalized.m_vector, _MM_SHUFFLE(2, 3, 0, 1)));
			normalized.m_vector = _mm_add_ps(normalized.m_vector, _mm_shuffle_ps(normalized.m_vector, normalized.m_vector, _MM_SHUFFLE(0, 1, 2, 3)));

			float x;
			_mm_store_ss(&x, normalized.m_vector);
			if (x == 0) {
				x = 1;
				_mm_store_ps(&x, normalized.m_vector);
			}

			normalized.m_vector = _mm_sqrt_ss(normalized.m_vector);
			normalized.m_vector = _mm_mul_ps(m_vector, normalized.m_vector);

			return normalized;
		}

		float* Vector4::getAsArray()
		{
			static _MM_ALIGN16 float vec_array[4];
			_mm_store_ps(vec_array, m_vector);
			return vec_array;
		}
		

		/*
		Static Functions
		*/

		//Dot product between two vectors
		float Vector4::Dot(Vector4 v, Vector4 u)
		{
			__m128 temp;
			__m128 prod = _mm_mul_ps(v.m_vector, u.m_vector);
			temp = _mm_add_ps(prod, _mm_shuffle_ps(prod, prod, _MM_SHUFFLE(0, 1, 2, 3)));
			temp = _mm_add_ps(temp, _mm_shuffle_ps(temp, temp, _MM_SHUFFLE(2, 3, 0, 1)));

			float dot;
			_mm_store_ss(&dot, temp);
			return dot;
		}

		/*
		Operators
		*/

		//Scalar operators
		Vector4 Vector4::operator*(float s)
		{
			Vector4 vec;

			__m128 product = _mm_mul_ps(m_vector, Scalar(s));

			vec.m_vector = product;

			return vec;
		}
		Vector4 Vector4::operator/(float s)
		{
			Vector4 vec;

			//Do division only once and then multiply by the inverse
			float invS = 1 / s;
			__m128 product = _mm_mul_ps(m_vector, Scalar(invS));

			vec.m_vector = product;

			return vec;
		}
		Vector4 Vector4::operator-(float s)
		{
			Vector4 vec;
			vec.m_vector = _mm_sub_ps(m_vector, Scalar(s));
			return vec;
		}
		Vector4 Vector4::operator+(float s)
		{
			Vector4 vec;
			vec.m_vector = _mm_add_ps(m_vector, Scalar(s));
			return vec;
		}

		Vector4 Vector4::operator*=(float s)
		{
			m_vector = _mm_mul_ps(m_vector, Scalar(s));

			return (*this);
		}
		Vector4 Vector4::operator/=(float s)
		{
			//Do division only once and then multiply by the inverse
			float invS = 1 / s;

			m_vector = _mm_mul_ps(m_vector, Scalar(invS));

			return (*this);
		}
		Vector4 Vector4::operator-=(float s)
		{
			m_vector = _mm_sub_ps(m_vector, Scalar(s));

			return (*this);
		}
		Vector4 Vector4::operator+=(float s)
		{
			m_vector = _mm_add_ps(m_vector, Scalar(s));

			return (*this);
		}

		bool Vector4::operator>(Vector4 u) { return magSqr() > u.magSqr(); }
		bool Vector4::operator<(Vector4 u) { return magSqr() < u.magSqr(); }
		bool Vector4::operator==(Vector4 u)
		{
			return _mm_movemask_ps(_mm_cmpeq_ps(m_vector, u.m_vector)) == 7;
		}
		bool Vector4::operator!=(Vector4 u)
		{
			return _mm_movemask_ps(_mm_cmpeq_ps(m_vector, u.m_vector)) != 7;
		}

		//Vector operators
		float Vector4::operator* (Vector4 u)
		{
			__m128 temp;
			__m128 prod = _mm_mul_ps(m_vector, u.m_vector);
			temp = _mm_add_ps(prod, _mm_shuffle_ps(prod, prod, _MM_SHUFFLE(0, 1, 2, 3)));
			temp = _mm_add_ps(temp, _mm_shuffle_ps(temp, temp, _MM_SHUFFLE(2, 3, 0, 1)));
			return (float)Scalar(temp);
		}
		Vector4 Vector4::operator+(Vector4 u)
		{
			Vector4 vec;

			__m128 sum = _mm_add_ps(m_vector, u.m_vector);

			vec.m_vector = sum;

			return vec;
		}
		Vector4 Vector4::operator-(Vector4 u)
		{
			Vector4 vec;

			__m128 diff = _mm_sub_ps(m_vector, u.m_vector);

			vec.m_vector = diff;

			return vec;
		}
		Vector4 Vector4::operator+=(Vector4 u)
		{
			m_vector = _mm_add_ps(m_vector, u.m_vector);

			return (*this);
		}
		Vector4 Vector4::operator-=(Vector4 u)
		{
			m_vector = _mm_sub_ps(m_vector, u.m_vector);

			return (*this);
		}

		float& Vector4::operator[](int i)
		{
			return data[i];
		}

		Vector4::operator Vector3()
		{
			_MM_ALIGN16 float vec_array[4];
			_mm_store_ps(vec_array, m_vector);
			return Vector3(vec_array[0], vec_array[1], vec_array[2]);
		}

		Vector4::operator Vector2()
		{
			_MM_ALIGN16 float vec_array[4];
			_mm_store_ps(vec_array, m_vector);
			return Vector2(vec_array[0], vec_array[1]);
		}


		//Extraction
		std::ostream& operator<<(std::ostream& output, Vector4& v)
		{
			output << v.x << " " << v.y << " " << v.z << " " << v.w;
			return output;
		}

		//Insertion
		std::istream& operator>>(std::istream& input, Vector4& v)
		{
			float x, y, z, w;
			input >> x >> y >> z >> w;

			v.x = x;
			v.y = y;
			v.z = z;
			v.w = w;

			return input;
		}


	}
}
