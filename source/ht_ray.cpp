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

#include <ht_ray.h>

namespace Hatchit {

    namespace Math {

        Ray::Ray(Vector3 direction)
        {
            this->origin = Vector3();
            this->direction = direction;
        }

        Ray::Ray(Vector3 origin, Vector3 direction)
        {
            this->origin = origin;
            this->direction = direction;
        }

        Vector3 Ray::getOrigin(){ return origin; }
        Vector3 Ray::getDirection(){ return direction; }

        void Ray::setOrigin(Vector3 origin){ this->origin = origin; }
        void Ray::setDirection(Vector3 direction){ this->direction = direction; }


    }

}
