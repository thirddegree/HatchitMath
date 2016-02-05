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

#include <ht_vector4.h>
#include <ht_vector3.h>

namespace Hatchit {

    namespace Math {

        /*
        Constructors
        */

        Vector4::Vector4()
        {

        }

        Vector4::Vector4(float x, float y, float z, float w)
        {
            //NOTE:
            //_mm_load_ss:
            // Takes float val and store into __m128 like so:
            // r0 = *val, r1=0.0, r2=0.0, r3=0.0
            __m128 xx = _mm_load_ss(&x);
            __m128 xy = _mm_load_ss(&y);
            __m128 xz = _mm_load_ss(&z);
            __m128 xw = _mm_load_ss(&w);

            //NOTE:
            // _mm_unpacklo_ps:
            // Selects the lowest two single-precision values from (a, b)
            // Thus, _mm_unpacklo_ps(xx,yy) --> r0=a0, r1=b0, r2=a1, r3=b1
            //
            // Using this, we can then take the  values (XX,XY) and (XZ,XW)
            // and combine them each into two single values
            // After doing so:
            // __m128 unpack(XX,XY) -> r0=x, r1=y, r2=0.0, r3=0.0
            // __m128 unpack(XZ,XW) -> r0=z, r1=w, r2=0.0, r3=0.0
            //
            // _mm_movelh_ps:
            // Moves the lower two single-precision values
            // Finally we can combine the results of the previous unpacks,
            // in this single call the result will give us the correct memory layout we want.
            //
            // movelh(unpack(XX,XY), unpack(XW,XZ) -> r0=x, r1=y, r2=z, r3=w
			this->m_vector = _mm_movelh_ps(_mm_unpacklo_ps(xx, xy), _mm_unpacklo_ps(xz, xw));

        }

        Vector4::Vector4(Vector3 v, float w)
        {
			__m128 xx = _mm_load_ss(&v[0]);
			__m128 xy = _mm_load_ss(&v[1]);
			__m128 xz = _mm_load_ss(&v[2]);
			__m128 xw = _mm_load_ss(&w);

			this->m_vector = _mm_movelh_ps(_mm_unpacklo_ps(xx, xy), _mm_unpacklo_ps(xz, xw));
        }

        Vector4::Vector4(const Vector4 & other)
        {
			this->m_vector = other.m_vector;
        }

        /*
        Destructor
        */

        Vector4::~Vector4()
        {

        }

        /*
        Accessors and Mutators
        */

        float Vector4::getX()
		{ 
			float x;
			_mm_store_ss(&x, m_vector);

			return x;
		}
        float Vector4::getY()
		{
			float y;
			_mm_store_ss(&y, _mm_shuffle_ps(m_vector, m_vector, _MM_SHUFFLE(1, 1, 1, 1)));

			return y;
		}
        float Vector4::getZ()
		{
			float z;
			_mm_store_ss(&z, _mm_movehl_ps(m_vector, m_vector));

			return z;
		}
        float Vector4::getW()
		{
			float w;
			_mm_store_ss(&w, _mm_shuffle_ps(m_vector, m_vector, _MM_SHUFFLE(3, 3, 3, 3)));

			return w;
		}

		//TODO: Redo with SSE Optimizations
        float Vector4::getMagnitude()
		{
			return sqrt((m_vec_array[0] * m_vec_array[0]) + (m_vec_array[1] * m_vec_array[1]) + (m_vec_array[2] * m_vec_array[2]) + (m_vec_array[3] * m_vec_array[3]));
		}

        float* Vector4::getAsArray()
		{
			_mm_store_ps(m_vec_array, m_vector);
			return m_vec_array;
		}

        void Vector4::setX(float x)
		{ 
			_MM_ALIGN16 float temp[4];
			_mm_store_ps(temp, m_vector);

			m_vector = _mm_set_ps(temp[3], temp[2], temp[1], x);
		}
        void Vector4::setY(float y)
		{
			_MM_ALIGN16 float temp[4];
			_mm_store_ps(temp, m_vector);

			m_vector = _mm_set_ps(temp[3], temp[2], y, temp[0]);
		}
        void Vector4::setZ(float z)
		{
			_MM_ALIGN16 float temp[4];
			_mm_store_ps(temp, m_vector);

			m_vector = _mm_set_ps(temp[3], z, temp[1], temp[0]);
		}
        void Vector4::setW(float w)
		{
			_MM_ALIGN16 float temp[4];
			_mm_store_ps(temp, m_vector);

			m_vector = _mm_set_ps(w, temp[2], temp[1], temp[0]);
		}

        /*
        Operators
        */

        float& Vector4::operator[](int i)
        {
			_mm_store_ps(m_vec_array, m_vector);
            return m_vec_array[i];
        }

        //Typecasting Operators

        Vector4::operator Vector3()
        {
            return Vector3((*this));
        }

        //Extraction
        std::ostream& operator<<(std::ostream& output, Vector4& v4)
        {
            output << v4.getX() << std::endl << v4.getY() << std::endl << v4.getZ() << std::endl << v4.getW() << std::endl;
            return output;
        }

        //Insertion
        std::istream& operator>> (std::istream& input, Vector4& v4)
        {
            float x, y, z, w;
            input >> x >> y >> z >> w;

			v4 = Vector4(x, y, z, w);

            return input;
        }


    }

}
