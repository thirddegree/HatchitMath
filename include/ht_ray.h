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
			//Constructors
			/** Create a ray with an origin as 0,0,0 and a given direction
			 * \param direction The direction as a Vector3
			 */
			Ray(Vector3 direction);
			/** Create a ray with a given origin and direction
			 * \param origin The origin as a Vector3
			 * \param direction The direction as a Vector3
			 */
			Ray(Vector3 origin, Vector3 direction);

			/** Returns the origin of the ray
			 * \return The origin as a Vector3
			 */
			Vector3 getOrigin();
			/** Returns the direction of the ray
			 * \return The direction as a Vector3
			 */
			Vector3 getDirection();

			/** Sets the origin of the ray
			 * \param origin The given origin as a Vector3
			 */
			void setOrigin(Vector3 origin);
			/** Sets the direction of the ray
			 * \param direction The given direction as a Vector3
			 */
			void setDirection(Vector3 direction);

		private:
			Vector3 origin;
			Vector3 direction;
		};
	}
}
