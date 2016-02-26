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
 * \ingroup HatchitMath
 *
 * \brief A mathematical representation of an Axis Aligned Box
 *
 * A collection of a center point and half widths to describe a volume
 *
 * TODO: Allow the bounds to be constructed by passing a min and max bound
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
			///Constructors
			///Creates a Bounds centered at 0,0,0 with all widths being 1.0f
			Bounds();
			/** Creates a Bounds at the given center and given width
			 * across all axes
			 * \param center The Vector3 for this Bounds to be centered at
			 * \param width The width of this Bounds
			 */
			Bounds(Vector3 center, float width);
			/** Creates a bounds at the given center with the given widths
			 * \param center The Vector3 for this Bounds to be centered at
			 * \param xWidth The width of this Bounds along the global X-axis
			 * \param yWidth The width of this Bounds along the global Y-axis
			 * \param zWidth The width of this Bounds along the global Z-axis
			 */
			Bounds(Vector3 center, float xWidth, float yWidth, float zWidth);
			virtual ~Bounds();

			//Accessors and Mutators

			/** Returns the width along the X-axis
			 * \return The width of the Bounds along the X-axis
			 */
			float getXWidth();
			/** Returns the width along the Y-axis
			 * \return The width of the Bounds along the Y-axis
			 */
			float getYWidth();
			/** Returns the width along the Z-axis
			 * \return The width of the Bounds along the Z-axis
			 */
			float getZWidth();

			///Returns the center point \return The center as a Vector3
			Vector3 getCenter();

			/** Returns corner of the Bounds along all the
			 * negative widths
			 * \returns The minimum bound as a Vector3
			 */
			Vector3 getMinBound();
			/** Returns corner of the Bounds along all the
			 * positive widths
			 * \returns The maximum bound as a Vector3
			 */
			Vector3 getMaxBound();

			//For collisions

			/** Calculates and returns the furthest corner of the bounds along
			 * the given normal vector
			 * \param normal The normalized Vector3 that we want to get the corner from
			 * \return The corner of the bounds furthest along the given normal
			 */
			Vector3 getPositive(Vector3 normal);

			/** Calculates and returns the furthest corner of the bounds away from
			 * the given normal vector
			 * \param normal The normalized Vector3 that we want to get the corner from
			 * \return The corner of the bounds furthest away from the given normal
			 */
			Vector3 getNegative(Vector3 normal);

			/** Determines whether or not this Bounds collides with another Bounds
			 * \param other The other Bounds to test against
			 * \return True if this and the other Bounds intersect anywhere
			 */
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
