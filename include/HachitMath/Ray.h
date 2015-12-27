/**
 * \class Ray
 * \ingroup HachitMath
 *
 * \brief A ray described by an origin and a direction
 *
 */

#ifndef RAY_H
#define RAY_H

#include "HachitMathDLL.h"

#include "Vector3.h"

namespace Hachit
{
	namespace Math
	{
		class HACHIT_MATH_API Ray
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

#endif
