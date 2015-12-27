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
 * \class Bounds
 * \ingroup HachitMath
 *
 * \brief A mathematical representation of an Axis Aligned Box
 *
 * A collection of a center point and half widths to describe a volume
 */

#pragma once

#include <ht_platform.h>
#include <ht_vector3.h>
#include <cmath>

namespace Hatchit
{
	namespace Math
	{
		class HT_API Bounds
		{
		public:
			Bounds();
			Bounds(Vector3 center, float width);
			Bounds(Vector3 center, float xWidth, float yWidth, float zWidth);
			~Bounds();

			//Accessors and Mutators
			float getXWidth();
			float getYWidth();
			float getZWidth();

			Vector3 getCenter();

			Vector3 getMinBound();
			Vector3 getMaxBound();

			void setMinBound(Vector3 minBound);
			void setMaxBound(Vector3 maxBound);

			//For collisions
			Vector3 getPositive(Vector3 normal);
			Vector3 getNegative(Vector3 normal);

			bool isCollidingWithBounds(Bounds other);

		private:
			float xWidth;
			float yWidth;
			float zWidth;

			Vector3 center;

			Vector3 minBound;
			Vector3 maxBound;
		};
	}
}