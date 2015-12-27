/**
 * \class Vector4
 * \ingroup HachitMath
 *
 * \brief A four dimensional vector
 *
 * A collection of 4 floats: X, Y, Z and W
 */

#ifndef VECTOR4_H
#define VECTOR4_H

//DLL Header
#include "HachitMath/HachitMathDLL.h"

//System Level Headers
#include <iostream>
#include <cmath>

namespace Hachit
{
	namespace Math
	{
		class Vector3;

		class HACHIT_MATH_API Vector4
		{
		public:
			//Constructors
			///Create a Vector4 with all 4 elements being 0
			Vector4();
			///Create a Vector4 with the elements x, y, z, w
			Vector4(float x, float y, float z, float w);
			///Create a Vector4 with the first 3 elements from a Vector3 and the last element w
			Vector4(Vector3 v, float w);
			///Create a copy of an existing Vector4
			Vector4(const Vector4& other);

			//Destructor
			virtual ~Vector4();

			//Accessors and mutators
			///Returns the X element \return The X element
			float getX();
			///Returns the Y element \return The Y element
			float getY();
			///Returns the Z element \return The Z element
			float getZ();
			///Returns the W element \return The W element
			float getW();

			/** Returns the magnitude of the vector
			* \return The magnitude as a float
			*/
			float getMagnitude();
			///Returns this Vector3 as a pointer to an array of floats
			float* getAsArray();

			///Sets the X element to x
			void setX(float x);
			///Sets the Y element to y
			void setY(float y);
			///Sets the Z element to z
			void setZ(float z);
			///Sets the W element to w
			void setW(float w);

			/** Fetches an element of this Vector at the index i
			 * \param i The index of the element to fetch
			 * \return A float that is stored in this Vector2 at the index i
			 * This will throw an index out of range exception if you go beyond an index if 1
			 */
			float& operator[] (int i);

			///Returns a Vector3 with the first three elements of this Vector4 all divided by the 4th element
			operator Vector3();

		private:
			float vector[4];
		};

		/** An insertion operator for a Vector3 to interace with an ostream
		* \param output The ostream to output to
		* \param h The Vector3 to interface with the ostream
		*/
		HACHIT_MATH_API std::ostream& operator<< (std::ostream& output, Vector4& h);
		/** An insertion operator for a Vector3 to interace with an ostream
		* \param output The ostream to output to
		* \param h The Vector3 to interface with the ostream
		*/
		HACHIT_MATH_API std::istream& operator>> (std::istream& input, Vector4& h);
	}
}
#endif
