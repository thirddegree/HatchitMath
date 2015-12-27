/**
 * \class Vector3
 * \ingroup HachitMath
 *
 * \brief A three dimensional vector
 *
 * A collection of 3 floats: X, Y and Z
 */

#ifndef VECTOR3_H
#define VECTOR3_H

//DLL Header
#include "HachitMath/HachitMathDLL.h"

//System Level Headers
#include <iostream>
#include <ostream>

namespace Hachit
{
	namespace Math
	{
		class Vector4;
		class Vector2;

		class HACHIT_MATH_API Vector3
		{
		public:
			//Constructors
			///Create a Vector3 with all 3 elements being 0
			Vector3();
			///Create a Vector3 with the elements x, y and z
			Vector3(float x, float y, float z);
			///Create a copy of an existing Vector3
			Vector3(const Vector3& other);
			///Create a Vector3 with the first three elements of a given Vector4
			Vector3(Vector4& v4);

			//Destructor
			virtual ~Vector3();

			//Accessors & Mutators
			float getX();
			float getY();
			float getZ();

			float getMagnitude();
			float* getAsArray();

			void setX(float x);
			void setY(float y);
			void setZ(float z);

			//Static functions
			static Vector3 Cross(Vector3 v, Vector3 u);
			static float Dot(Vector3 v, Vector3 u);
			static Vector3 Normalize(Vector3 v);

			//Operators
			Vector3 operator* (float s);
			Vector3 operator/ (float s);
			Vector3 operator- (float s);
			Vector3 operator+ (float s);

			Vector3 operator*= (float s);
			Vector3 operator/= (float s);
			Vector3 operator-= (float s);
			Vector3 operator+= (float s);

			bool operator>(Vector3 u);
			bool operator<(Vector3 u);
			bool operator==(Vector3 u);
			bool operator!=(Vector3 u);

			float operator* (Vector3 u);
			Vector3 operator+ (Vector3 u);
			Vector3 operator- (Vector3 u);
			Vector3 operator+= (Vector3 u);
			Vector3 operator-= (Vector3 u);

			float& operator[] (int i);

			operator Vector4();
			operator Vector2();

		private:
			float vector[3];
		};

		HACHIT_MATH_API std::ostream& operator<< (std::ostream& output, Vector3& h);
		HACHIT_MATH_API std::istream& operator>> (std::istream& input, Vector3& h);
	}
}
#endif
