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

namespace Hatchit {

    namespace Math {

        /*
        Constructors
        */

        Quaternion::Quaternion()
        {
            q[0] = 1;
            q[1] = 0;
            q[2] = 0;
            q[3] = 0;
        }

        Quaternion::Quaternion(float w, float x, float y, float z)
        {
            q[0] = w;
            q[1] = x;
            q[2] = y;
            q[3] = z;
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

            float w,x,y,z;

            w = (headingCos * attitudeCos * bankCos) -
                (headingSin * attitudeSin * bankSin);
            x = (headingSin * attitudeSin * bankCos) +
                (headingCos * attitudeCos * bankSin);
            y = (headingSin * attitudeCos * bankCos) +
                (headingCos * attitudeSin * bankSin);
            z = (headingCos * attitudeSin * bankCos) +
                (headingSin * attitudeCos * bankSin);

            q[0] = w;
            q[1] = x;
            q[2] = y;
            q[3] = z;
        }

        //Assuming from Angle-Axis
        Quaternion::Quaternion(Vector4 v)
        {
            float halfAngle = v[3] / 2.0f;

            q[0] = cosf(halfAngle);
            q[1] = v[0] * sinf(halfAngle);
            q[2] = v[1] * sinf(halfAngle);
            q[3] = v[2] * sinf(halfAngle);
        }

        Quaternion::~Quaternion(void)
        {
        }

        Quaternion Quaternion::getInverse()
        {
            return Quaternion(q[0], -q[1], -q[2], -q[3]);
        }

        Quaternion Quaternion::getQuaternionIdentity()
        {
            return Quaternion(0, 0, 0, 1);
        }

        Vector4 Quaternion::getAxisAngle()
        {
            float xsq = powf(q[1], 2);
            float ysq = powf(q[2], 2);
            float zsq = powf(q[3], 2);

            float scale = sqrtf(xsq + ysq + zsq);

            float x = q[1] / scale;
            float y = q[2] / scale;
            float z = q[3] / scale;
            float angle = acos(q[0]) * 2.0f;

            return Vector4(x, y, z, angle);
        }

        Matrix3 Quaternion::getRotationMatrix()
        {
            float w = q[0];
            float x = q[1];
            float y = q[2];
            float z = q[3];

            float wsq = powf(w, 2);
            float xsq = powf(x, 2);
            float ysq = powf(y, 2);
            float zsq = powf(z, 2);

            float m00 = 1 - (2 * (ysq + zsq));
            float m11 = 1 - (2 * (xsq + zsq));
            float m22 = 1 - (2 * (xsq + ysq));

            float m01 = 2 * ((x * y) + (z * w));
            float m02 = 2 * ((x * z) - (y * w));

            float m10 = 2 * ((x * y) - (z * w));
            float m12 = 2 * ((y * z) + (x * w));

            float m20 = 2 * ((x * z) + (y * w));
            float m21 = 2 * ((y * z) - (x * w));

            Matrix3 rotationMat(m00, m01, m02,
                                m10, m11, m12,
                                m20, m21, m22);

            return rotationMat;
        }

        void Quaternion::normalize()
        {
            float wsq = powf(q[0], 2);
            float xsq = powf(q[1], 2);
            float ysq = powf(q[2], 2);
            float zsq = powf(q[3], 2);

            float magSq = (wsq + xsq + ysq + zsq);
            if (fabsf(magSq) > 0.00001f &&
                fabsf(magSq - 1.0f) > 0.00001f)
            {
                float mag = sqrtf(magSq);
                q[0] /= mag;
                q[1] /= mag;
                q[2] /= mag;
                q[3] /= mag;
            }
        }

        /*
        Accessors and Mutators
        */

        float Quaternion::getW(){ return q[0]; }
        float Quaternion::getX(){ return q[1]; }
        float Quaternion::getY(){ return q[2]; }
        float Quaternion::getZ(){ return q[3]; }

        void Quaternion::setW(float w){ q[0] = w; }
        void Quaternion::setX(float x){ q[1] = x; }
        void Quaternion::setY(float y){ q[2] = y; }
        void Quaternion::setZ(float z){ q[3] = z; }

        /*
        Operators
        */

        float& Quaternion::operator[](int i)
        {
            return q[i];
        }

        Quaternion Quaternion::operator*(Quaternion o)
        {
            float thisScalar = q[0];
            float otherScalar = o[0];

            Vector3 thisVector = Vector3(q[1], q[2], q[3]);
            Vector3 otherVector = Vector3(o[1], o[2], o[3]);

            float prodScalar = (thisScalar * otherScalar) -
                               (Vector3::Dot(thisVector, otherVector));

            Vector3 prodVector = Vector3::Cross(thisVector, otherVector) +
                                 (otherVector * thisScalar) +
                                 (thisVector * otherScalar);

            return Quaternion(prodScalar, prodVector[0], prodVector[1], prodVector[2]);
        }

        //Extraction
        std::ostream& operator<<(std::ostream& output, Quaternion& q)
        {
            output << q[0] << "," << q[1] << "," << q[2] << "," << q[3];
            return output;
        }

        //Insertion
        std::istream& operator>> (std::istream& input, Quaternion& q)
        {
            input >> q[0] >> q[1] >> q[2] >> q[3];
            return input;
        }
    }

}
