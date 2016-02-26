
namespace Hatchit {

    namespace Math {


        //////////////////////////////////////////////////////////////////////
        // MMVECTOR3 Implementation
        //////////////////////////////////////////////////////////////////////

        //Create a Vector3 with all 3 elements being 0
        inline Vector3::Vector3()
        {
            this->m_vector = _mm_setzero_ps();
        }

        //Create a Vector3 with the elements x, y and z
        inline Vector3::Vector3(float x, float y, float z)
        {
            float zero = 0;

            __m128 xx = _mm_load_ss(&x);
            __m128 xy = _mm_load_ss(&y);
            __m128 xz = _mm_load_ss(&z);
            __m128 xw = _mm_load_ss(&zero);

            this->m_vector = _mm_movelh_ps(_mm_unpacklo_ps(xx, xy), _mm_unpacklo_ps(xz, xw));
        }

        //Create a copy of an existing Vector3
        inline Vector3::Vector3(const Vector3& other)
        {
            this->m_vector = other.m_vector;
        }

        //Create a Vector3 with the first three elements of a given Vector4 all divided by the 4th element
        inline Vector3::Vector3(Hatchit::Math::Vector4& v4)
        {
            //We'll just ignore the last element of the __m128 so just do a copy by value
            this->m_vector = (__m128)v4;

            _MM_ALIGN16 float temp[4];
            _mm_store_ps(temp, m_vector);
            m_vector = _mm_set_ps(0, temp[2], temp[1], temp[0]);
        }

        //Allocate a 16byte aligned array of Vector3
        inline void* Vector3::operator new(size_t _size)
        {
            return aligned_malloc(sizeof(__m128), _size);
        }

        //Delete an array of Vector3
        inline void Vector3::operator delete(void* p)
        {
            aligned_free(p);
        }

        /** Casts a Vector3 object to a __m128
        * This operator casts a Vector3 to an instrinsic __m128
        */
        inline Vector3::operator const __m128(void) const
        {
            return m_vector;
        }

        /** Multiplies all elements in this Vector3 by a given scalar
        * This operation returns a new Vector3
        * \param s The scalar to multiply this Vector3 by
        * \return A Vector3 after all the elements have been multiplied by s
        */
        inline Vector3 Vector3::operator*(float s)
        {
            Vector3 vec;

            __m128 product = _mm_mul_ps(m_vector, _mm_set_ps1(s));

            vec.m_vector = product;

            return vec;
        }

        /** Divides all elements in this Vector3 by a given scalar
        * This operation returns a new Vector3
        * \param s The scalar to divide this Vector3 by
        * \return A Vector3 after all the elements have been divided by s
        */
        inline Vector3 Vector3::operator/(float s)
        {
            Vector3 vec;

            //Do division only once and then multiply by the inverse
            float invS = 1 / s;

            __m128 product = _mm_mul_ps(m_vector, _mm_set_ps1(invS));

            vec.m_vector = product;

            return vec;
        }

        /** Subtracts all elements in this Vector3 by a given scalar
        * This operation returns a new Vector3
        * \param s The scalar to subtract this Vector3 by
        * \return A Vector3 after all the elements have been subtracted by s
        */
        inline Vector3 Vector3::operator-(float s)
        {
            Vector3 vec;

            __m128 product = _mm_sub_ps(m_vector, _mm_set_ps1(s));

            vec.m_vector = product;

            return vec;
        }

        /** Adds all elements in this Vector3 by a given scalar
        * This operation returns a new Vector3
        * \param s The scalar to add this Vector3 by
        * \return A Vector3 after all the elements have been added by s
        */
        inline Vector3 Vector3::operator+(float s)
        {
            Vector3 vec;

            __m128 product = _mm_add_ps(m_vector, _mm_set_ps1(s));

            vec.m_vector = product;

            return vec;
        }

        /** Multiplies all elements in this Vector3 by a given scalar
        * This operation affects the elements in this Vector3
        * \param s The scalar to multiply this Vector3 by
        * \return This Vector3 after all the elements have been multiplied by s
        */
        inline Vector3 Vector3::operator*=(float s)
        {
            m_vector = _mm_mul_ps(m_vector, _mm_set_ps1(s));

            return (*this);
        }

        /** Divides all elements in this Vector3 by a given scalar
        * This operation affects the elements in this Vector3
        * \param s The scalar to divide this Vector3 by
        * \return This Vector3 after all the elements have been divided by s
        */
        inline Vector3 Vector3::operator/=(float s)
        {
            //Do division only once and then multiply by the inverse
            float invS = 1 / s;

            m_vector = _mm_mul_ps(m_vector, _mm_set_ps1(invS));

            return (*this);
        }

        /** Subtracts all elements in this Vector3 by a given scalar
        * This operation affects the elements in this Vector3
        * \param s The scalar to subtract this Vector3 by
        * \return This Vector3 after all the elements have been subtracted by s
        */
        inline Vector3 Vector3::operator-=(float s)
        {
            m_vector = _mm_sub_ps(m_vector, _mm_set_ps1(s));

            return (*this);
        }

        /** Adds all elements in this Vector3 by a given scalar
        * This operation affects the elements in this Vector3
        * \param s The scalar to add this Vector3 by
        * \return This Vector3 after all the elements have been added by s
        */
        inline Vector3 Vector3::operator+=(float s)
        {
            m_vector = _mm_add_ps(m_vector, _mm_set_ps1(s));

            return (*this);
        }

        /** Compares the magnitue of this Vector3 to another given Vector3
        * \param u The other Vector3
        * \return True if this Vector3 has a larger magnitude than the other Vector3
        */
        inline bool Vector3::operator>(Vector3 u)
        {
            return Hatchit::Math::MMVector3Magnitude(*this) > Hatchit::Math::MMVector3Magnitude(u);
        }

        /** Compares the magnitue of this Vector3 to another given Vector3
        * \param u The other Vector3
        * \return True if this Vector3 has a smaller magnitude than the other Vector3
        */
        inline bool Vector3::operator<(Vector3 u)
        {
            return MMVector3Magnitude(*this) < MMVector3Magnitude(u);
        }

        /** Compares the values of this Vector3 to another given Vector3
        * \param u The other Vector3
        * \return True if this Vector3 has the same values of the other Vector3
        */
        inline bool Vector3::operator==(Vector3 u)
        {
            return _mm_movemask_ps(_mm_cmpeq_ps(m_vector, u.m_vector)) == 15;
        }

        /** Compares the values of this Vector3 to another given Vector3
        * \param u The other Vector3
        * \return True if this Vector3 does not have the same values as the other Vector3
        */
        inline bool Vector3::operator!=(Vector3 u)
        {
            return _mm_movemask_ps(_mm_cmpeq_ps(m_vector, u.m_vector)) != 15;
        }

        /** Executes memberwise multiplication on two vectors
        * \param u The other Vector3
        * \return The product of this * u as a vector
        */
        inline Vector3 Vector3::operator* (Vector3 u)
        {
            Vector3 v;
            v.m_vector = _mm_mul_ps(this->m_vector, u.m_vector);

            return v;
        }

        /** Adds all of the elements from a given vector to this one
        * \param u The other Vector3
        * \return A new vector with the sums of all the pairs of elements
        */
        inline Vector3 Vector3::operator+(Vector3 u)
        {
            Vector3 vec;

            __m128 sum = _mm_add_ps(m_vector, u.m_vector);

            vec.m_vector = sum;

            return vec;
        }

        /** Subtracts all of the elements from this vector by a given vector
        * \param u The other Vector3
        * \return A new vector with the differences of all the pairs of elemens
        */
        inline Vector3 Vector3::operator-(Vector3 u)
        {
            Vector3 vec;

            __m128 diff = _mm_sub_ps(m_vector, u.m_vector);

            vec.m_vector = diff;

            return vec;
        }

        /** Adds all of the elements from a given vector to this one
        * \param u The other Vector3
        * \return This vector with the sums of all the pairs of elements
        */
        inline Vector3 Vector3::operator+=(Vector3 u)
        {
            m_vector = _mm_add_ps(m_vector, u.m_vector);

            return (*this);
        }

        /** Subtracts all of the elements from this vector by a given one
        * \param u The other Vector3
        * \return This vector with the differences of all the pairs of elements
        */
        inline Vector3 Vector3::operator-=(Vector3 u)
        {
            m_vector = _mm_sub_ps(m_vector, u.m_vector);

            return (*this);
        }

        /** Fetches an element of this Vector at the index i
        * \param i The index of the element to fetch
        * \return A float that is stored in this Vector3 at the index i
        * This will throw an index out of range exception if you go beyond an index if 1
        */
        inline float& Vector3::operator[](int i)
        {
            assert(i < 3);

            return this->m_data[i];
        }


        /** Executes the Dot product on two Vector3s as v * u
        * \param v The first Vector3
        * \param u The second Vector3
        * \return The Dot product of v and u as a float
        */
        inline float _MM_CALLCONV MMVector3Dot(Vector3 v, Vector3 u)
        {
            __m128 temp;
            __m128 sq = _mm_mul_ps(v.m_vector, u.m_vector);
            temp = _mm_add_ps(sq, _mm_shuffle_ps(sq, sq, _MM_SHUFFLE(3, 1, 0, 2)));
            temp = _mm_add_ps(temp, _mm_shuffle_ps(sq, sq, _MM_SHUFFLE(3, 0, 2, 1)));

            return Hatchit::Math::MMVectorGetX(temp);
        }

        /** Executes the cross product on two given Vector3s as v X u
        * \param v The first Vector3
        * \param u The second Vector3
        * \return The cross product of v and u as a Vector3
        */
        inline Vector3 _MM_CALLCONV MMVector3Cross(Vector3 v, Vector3 u)
        {
            Vector3 output;

            __m128 x00 = _mm_shuffle_ps(v.m_vector, v.m_vector, _MM_SHUFFLE(3, 0, 2, 1));
            __m128 x10 = _mm_shuffle_ps(u.m_vector, u.m_vector, _MM_SHUFFLE(3, 1, 0, 2));
            __m128 x01 = _mm_shuffle_ps(v.m_vector, v.m_vector, _MM_SHUFFLE(3, 1, 0, 2));
            __m128 x11 = _mm_shuffle_ps(u.m_vector, u.m_vector, _MM_SHUFFLE(3, 0, 2, 1));

            x00 = _mm_mul_ps(x00, x10);
            x11 = _mm_mul_ps(x01, x11);

            __m128 val = _mm_sub_ps(x00, x11);

            output.m_vector = val;
            return output;
        }

        /** Normalizes a Vector3
        * \param v The Vector3 to normalize
        * \return A normalized version of v
        * NOTE:
        * This function is only partially intrinsic
        */
        inline Vector3 _MM_CALLCONV MMVector3Normalize(Vector3 v)
        {
            float magnitude = MMVector3Magnitude(v);

            if (magnitude == 0)
                magnitude = 1;

            Vector3 normalizedVec;

            float invMag = 1 / magnitude;
            normalizedVec.m_vector = _mm_mul_ps(v.m_vector, MMVectorSet(invMag, invMag, invMag, invMag));

            return normalizedVec;
        }

        /** Returns the magnitude of the vector
        * \return The magnitude as a float
        */
        inline float _MM_CALLCONV MMVector3Magnitude(Vector3 v)
        {
            __m128 val = _mm_mul_ps(v.m_vector, v.m_vector);

            val = _mm_add_ps(val, _mm_shuffle_ps(val, val, _MM_SHUFFLE(3, 2, 1, 1)));
            val = _mm_add_ps(val, _mm_shuffle_ps(val, val, _MM_SHUFFLE(3, 2, 2, 2)));
            val = _mm_sqrt_ss(val);

            return ::MMVectorGetX(val);
        }

        /** An outstream operator for a Vector3 to interace with an ostream
        * \param output The ostream to output to
        * \param h The Vector3 to interface with the ostream
        */
        inline std::ostream& operator<<(std::ostream& output, Vector3& v)
        {
            output << v.x << " " << v.y << " " << v.z;

            return output;
        }

        /** An insertion operator for a Vector3 to interace with an ostream
        * \param output The ostream to output to
        * \param h The Vector3 to interface with the ostream
        */
        inline std::istream& operator>>(std::istream& input, Vector3& v)
        {
            input >> v.x >> v.y >> v.z;

            return input;
        }
    }
}