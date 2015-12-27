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
			///Create a Vector3 with the first three elements of a given Vector4 all divided by the 4th element
			Vector3(Vector4& v4);

			//Destructor
			virtual ~Vector3();

			//Accessors & Mutators
			///Returns the X element \return The X element
			float getX();
			///Returns the Y element \return The Y element
			float getY();
			///Returns the Z element \return The Z element
			float getZ();

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

			//Static functions

			/** Executes the cross product on two given Vector3s as v X u
			 * \param v The first Vector3
			 * \param u The second Vector3
			 * \return The corss product of v and u as a Vector3
			 */
			static Vector3 Cross(Vector3 v, Vector3 u);
			/** Executes the Dot product on two Vector3s as v * u
			* \param v The first Vector3
			* \param u The second Vector3
			* \return The Dot product of v and u as a float
			*/
			static float Dot(Vector3 v, Vector3 u);
			/** Normalizes a Vector3
			* \param v The Vector3 to normalize
			* \return A normalized version of v
			*/
			static Vector3 Normalize(Vector3 v);

			//Operators

			/** Multiplies all elements in this Vector3 by a given scalar
			 * This operation returns a new Vector3
			 * \param s The scalar to multiply this Vector3 by
			 * \return A Vector3 after all the elements have been multiplied by s
			 */
			Vector3 operator* (float s);
			/** Divides all elements in this Vector3 by a given scalar
			 * This operation returns a new Vector3
			 * \param s The scalar to divide this Vector3 by
			 * \return A Vector3 after all the elements have been divided by s
			 */
			Vector3 operator/ (float s);
			/** Subtracts all elements in this Vector3 by a given scalar
			 * This operation returns a new Vector3
			 * \param s The scalar to subtract this Vector3 by
			 * \return A Vector3 after all the elements have been subtracted by s
			 */
			Vector3 operator- (float s);
			/** Adds all elements in this Vector3 by a given scalar
			 * This operation returns a new Vector3
			 * \param s The scalar to add this Vector3 by
			 * \return A Vector3 after all the elements have been added by s
			 */
			Vector3 operator+ (float s);

			/** Multiplies all elements in this Vector3 by a given scalar
			 * This operation affects the elements in this Vector3
			 * \param s The scalar to multiply this Vector3 by
			 * \return This Vector3 after all the elements have been multiplied by s
			 */
			Vector3 operator*= (float s);
			/** Divides all elements in this Vector3 by a given scalar
			 * This operation affects the elements in this Vector3
			 * \param s The scalar to divide this Vector3 by
			 * \return This Vector3 after all the elements have been divided by s
			 */
			Vector3 operator/= (float s);
			/** Subtracts all elements in this Vector3 by a given scalar
			 * This operation affects the elements in this Vector3
			 * \param s The scalar to subtract this Vector3 by
			 * \return This Vector3 after all the elements have been subtracted by s
			 */
			Vector3 operator-= (float s);
			/** Adds all elements in this Vector3 by a given scalar
			 * This operation affects the elements in this Vector3
			 * \param s The scalar to add this Vector3 by
			 * \return This Vector3 after all the elements have been added by s
			 */
			Vector3 operator+= (float s);

			/** Compares the magnitue of this Vector3 to another given Vector3
			 * \param u The other Vector3
			 * \return True if this Vector3 has a larger magnitude than the other Vector3
			 */
			bool operator>(Vector3 u);
			/** Compares the magnitue of this Vector3 to another given Vector3
			 * \param u The other Vector3
			 * \return True if this Vector3 has a smaller magnitude than the other Vector3
			 */
			bool operator<(Vector3 u);
			/** Compares the magnitue of this Vector3 to another given Vector3
			 * \param u The other Vector3
			 * \return True if this Vector3 has the same magnitude of the other Vector3
			 */
			bool operator==(Vector3 u);
			/** Compares the magnitue of this Vector3 to another given Vector3
			 * \param u The other Vector3
			 * \return True if this Vector3 does not have the same magnitude as the other Vector3
			 */
			bool operator!=(Vector3 u);

			/** Executes the Dot product this Vector3 and another as this * other
			 * \param u The other Vector3
			 * \return The Dot product of this * u as a float
			 */
			float operator* (Vector3 u);

			/** Adds all of the elements from a given vector to this one
			 * \param u The other Vector3
			 * \return A new vector with the sums of all the pairs of elements
			 */
			Vector3 operator+ (Vector3 u);
			/** Subtracts all of the elements from this vector by a given vector
			 * \param u The other Vector3
			 * \return A new vector with the differences of all the pairs of elemens
			 */
			Vector3 operator- (Vector3 u);
			/** Adds all of the elements from a given vector to this one
			 * \param u The other Vector3
			 * \return This vector with the sums of all the pairs of elements
			 */
			Vector3 operator+= (Vector3 u);
			/** Subtracts all of the elements from this vector by a given one
			 * \param u The other Vector3
			 * \return This vector with the differences of all the pairs of elements
			 */
			Vector3 operator-= (Vector3 u);

			/** Fetches an element of this Vector at the index i
			 * \param i The index of the element to fetch
			 * \return A float that is stored in this Vector2 at the index i
			 * This will throw an index out of range exception if you go beyond an index if 1
			 */
			float& operator[] (int i);

			///Returns a Vector4 with the first three elements from this vector and the last one being 0
			operator Vector4();
			///Returns a Vector2 with the fist two elements from this vector
			operator Vector2();

		private:
			float vector[3];
		};

		/** An insertion operator for a Vector3 to interace with an ostream
		 * \param output The ostream to output to
		 * \param h The Vector3 to interface with the ostream
		 */
		HACHIT_MATH_API std::ostream& operator<< (std::ostream& output, Vector3& h);
		/** An insertion operator for a Vector3 to interace with an ostream
		 * \param output The ostream to output to
		 * \param h The Vector3 to interface with the ostream
		 */
		HACHIT_MATH_API std::istream& operator>> (std::istream& input, Vector3& h);
	}
}
#endif
