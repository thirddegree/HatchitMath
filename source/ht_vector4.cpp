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
			this->vector = _mm_set1_ps(0);
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
			this->vector = _mm_movelh_ps(_mm_unpacklo_ps(xx, xy), _mm_unpacklo_ps(xz, xw));

        }

        Vector4::Vector4(Vector3 v, float w)
        {
			this->vector = _mm_set_ps(v[0], v[1], v[2], w);
        }

        Vector4::Vector4(const Vector4 & other)
        {
			this->vector = other.vector;
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
			_mm_store_ps(vals, vector);
			return vals[0];
		}
        float Vector4::getY()
		{
			_mm_store_ps(vals, vector);
			return vals[1];
		}
        float Vector4::getZ()
		{
			_mm_store_ps(vals, vector);
			return vals[2];
		}
        float Vector4::getW()
		{
			_mm_store_ps(vals, vector);
			return vals[3];
		}

        float Vector4::getMagnitude()
		{
			return sqrt((vals[0] * vals[0]) + (vals[1] * vals[1]) + (vals[2] * vals[2]) + (vals[3] * vals[3]));
		}
        float* Vector4::getAsArray()
		{
			_mm_store_ps(vals, vector);
			return vals;
		}

        void Vector4::setX(float x)
		{ 
			vals[0] = x;
			vector = _mm_load_ps(vals);
		}
        void Vector4::setY(float y)
		{
			vals[1] = y;
			vector = _mm_load_ps(vals);
		}
        void Vector4::setZ(float z)
		{
			vals[2] = z;
			vector = _mm_load_ps(vals);
		}
        void Vector4::setW(float w)
		{
			vals[3] = w;
			vector = _mm_load_ps(vals);
		}

        /*
        Operators
        */

        float& Vector4::operator[](int i)
        {
			_mm_store_ps(vals, vector);
            return vals[i];
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
