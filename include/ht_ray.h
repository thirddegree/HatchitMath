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

/**
 * \class Ray
 * \ingroup HachitMath
 *
 * \brief A ray described by an origin and a direction
 *
 */

#pragma once

#include <ht_platform.h>
#include <ht_vector3.h>

namespace Hatchit
{
	namespace Math
	{
		class HT_API Ray
		{
		public:
			Ray(Vector3 direction);
			Ray(Vector3 origin, Vector3 direction);

			Vector3 getOrigin();
			Vector3 getDirection();

			void setOrigin(Vector3 origin);
			void setDirection(Vector3 direction);

		private:
			Vector3 origin;
			Vector3 direction;
		};
	}
}
