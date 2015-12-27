/**
 * \class Vector2
 * \ingroup HachitMath
 *
 * \brief A two dimensional vector
 *
 * A collection of 2 floats: X and Y
 */

#ifndef VECTOR2_H
#define VECTOR2_H

//DLL Header
#include "HachitMath/HachitMathDLL.h"

//System Level Headers
#include <iostream>
#include <cmath>

namespace Hachit
{
	namespace Math
	{
		class HACHIT_MATH_API Vector2
		{
		public:
			//Constructors
			///Create a Vector2 with both elements being 0
			Vector2();
			///Create a Vector2 with the elements described by x and y
			Vector2(float x, float y);
			///Create a Vector2 with the elements of another Vector2
			Vector2(const Vector2& other);

			//Destructor
			virtual ~Vector2();

			//Accessors & Mutators
			///Returns the X element \return The X element
			float getX();
			///Returns the Y element \return The Y element
			float getY();

			/** Returns the magnitude
			 * \return The magnitude as a float
			 */
			float getMagnitude();
			///Returns this Vector2 a pointer to an array of floats
			float* getAsArray();

			///Sets the X element to x
			void setX(float x);
			///Sets the Y element to y
			void setY(float y);

			//Static functions
			/**Executes the Dot product on two Vector2s as v * u
			 * \param v The first Vector2
			 * \param u The second Vector2
			 * \return The Dot product of v and u as a float
			 */
			static float Dot(Vector2 v, Vector2 u);
			/**Normalizes a Vector2
			 * \param v The Vector2 to normalize
			 * \return A normalized version of v
			 */
			static Vector2 Normalize(Vector2 v);

			//Operators
			/** Performs the dot procduct between this Vector2 and another Vector2
			 * \param u The other Vector2
			 * \return The dot product between this vector and u
			 */
			float operator* (Vector2 u);
			/** Multiplies a scalar into this Vector2
			 * \param s The other scalar
			 * \return A Vector2 whose elements have been multiplied by s
			 */
			Vector2 operator* (float s);
			/** Adds another Vector2 to this one
			 * \param u The other Vector2
			 * \return A Vector2 whose elements are a result of this Vector2 added to u
			 */
			Vector2 operator+ (Vector2 u);
			/** Fetches an element of this Vector at the index i
			 * \param i The index of the element to fetch
			 * \return A float that is stored in this Vector2 at the index i
			 * This will throw an index out of range exception if you go beyond an index if 1
			 */
			float& operator[] (int i);

		private:
			float vector[2];
		};

		/** An insertion operator for a Vector2 to interace with an ostream
		* \param output The ostream to output to
		* \param h The Vector2 to interface with the ostream
		*/
		HACHIT_MATH_API std::ostream& operator<< (std::ostream& output, Vector2& h);
		/** An extraction operator for a Vector2 to interace with an istream
		* \param output The istream to input from
		* \param h The Vector2 to be filled by the istream
		*/
		HACHIT_MATH_API std::istream& operator>> (std::istream& input, Vector2& h);
	}
}
#endif
