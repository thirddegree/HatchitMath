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

#pragma once
#include <ht_math.h>

namespace Hatchit {

    namespace Math {

        inline Float4x4::Float4x4(float xx, float xy, float xz, float xw,
            float yx, float yy, float yz, float yw,
            float zx, float zy, float zz, float zw,
            float wx, float wy, float wz, float ww)
        {
            data[0][0] = xx;
            data[0][1] = xy;
            data[0][2] = xz;
            data[0][3] = xw;

            data[1][0] = yx;
            data[1][1] = yy;
            data[1][2] = yz;
            data[1][3] = yw;

            data[2][0] = zx;
            data[2][1] = zy;
            data[2][2] = zz;
            data[2][3] = zw;

            data[3][0] = wx;
            data[3][1] = wy;
            data[3][2] = wz;
            data[3][3] = ww;
        }

        inline Float4x4::Float4x4(const float* _data)
        {

            data[0][0] = _data[0];
            data[0][1] = _data[1];
            data[0][2] = _data[2];
            data[0][3] = _data[3];

            data[1][0] = _data[4];
            data[1][1] = _data[5];
            data[1][2] = _data[6];
            data[1][3] = _data[7];

            data[2][0] = _data[8];
            data[2][1] = _data[9];
            data[2][2] = _data[10];
            data[2][3] = _data[11];

            data[3][0] = _data[12];
            data[3][1] = _data[13];
            data[3][2] = _data[14];
            data[3][3] = _data[15];
        }

    }
}