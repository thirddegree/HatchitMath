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

namespace Hatchit
{
    namespace Math
    {
        //////////////////////////////////////////////////////////
        // Angle Conversion Operations
        //////////////////////////////////////////////////////////

        /* Converts degrees to radians
        * \return A float with the given degrees now converted to radians
        */
        constexpr inline float _MM_CALLCONV MMDegreesToRadians(float degrees)
        {
            return degrees * 0.01745329f;
        }

        /* Converts radians to degrees
        * \return A float with the given radians now converted to degrees
        */
        constexpr inline float _MM_CALLCONV MMRadiansToDegrees(float radians)
        { 
            return radians * 57.2957795f; 
        }

    }
}