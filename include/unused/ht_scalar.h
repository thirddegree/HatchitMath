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

#include <ht_platform.h>
#include <ht_intrin.h>
#include <ht_mmbasevector.h>

namespace Hatchit {

    namespace Math {

        class HT_API Scalar : public MMBaseVector
        {
        public:
            Scalar(void);
            Scalar(float  _val);
            Scalar(__m128 _val);
            
            const float operator[] (int index);
                
            operator float(void) const;
        };
    }
}
