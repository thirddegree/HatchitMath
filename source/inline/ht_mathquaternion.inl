#include <ht_math.h>

namespace Hatchit {

    namespace Math {

        //////////////////////////////////////////////////////////////////////
        // MMVECTOR3 Implementation
        //////////////////////////////////////////////////////////////////////

        //Create an identity Quaternion
        inline Quaternion::Quaternion() : m_quaternion(MMVectorSet(0.0f, 0.0f, 0.0f, 1.0f)) {}

        //Create a Quaternion with elements x, y, z, w (q = w + xi + yj + zk)
        inline Quaternion::Quaternion(float x, float y, float z, float w) : m_quaternion(MMVectorSet(x, y, z, w)) {}

        //Create a Quaternion from a rotation based on axis and angle
        inline Quaternion::Quaternion(const Vector3& axis, float angle) : m_quaternion(MMVectorSetW(static_cast<__m128>(axis * sinf(angle / 2)), cosf(angle / 2))) {}

        //Create a Quaternion from rotation on x, y, and z axis
        inline Quaternion::Quaternion(float roll, float pitch, float yaw) : m_quaternion()
        {
            //TODO: Who wants to make this intrinsic?  Anyone?
            float cosRoll = cosf(roll * 0.5f);
            float cosPitch = cosf(pitch * 0.5f);
            float cosYaw = cosf(yaw * 0.5f);
            float sinRoll = sinf(roll * 0.5f);
            float sinPitch = sinf(pitch * 0.5f);
            float sinYaw = sinf(yaw * 0.5f);

            __m128 vecA = MMVectorSet(sinPitch, sinPitch, cosPitch, cosPitch);
            __m128 vecB = MMVectorSet(sinYaw, cosYaw, sinYaw, cosYaw);
            __m128 vecC = _mm_set1_ps(cosRoll);

            __m128 vecD = MMVectorSet(cosPitch, cosPitch, -sinPitch, -sinPitch);
            __m128 vecE = MMVectorSet(cosYaw, sinYaw, cosYaw, sinYaw);
            __m128 vecF = _mm_set1_ps(sinRoll);

            vecA = _mm_mul_ps(vecA, _mm_mul_ps(vecB, vecC));
            vecD = _mm_mul_ps(vecD, _mm_mul_ps(vecE, vecF));

            m_quaternion = _mm_add_ps(vecA, vecD);
        }

        //Create a Quaternion from existing __m128 data
        inline Quaternion::Quaternion(__m128 quatData) : m_quaternion(std::move(quatData)) {}

        //Allocate a 16 byte aligned Quaternion
        inline void* Quaternion::operator new(size_t size)
        {
            return aligned_malloc(size, vectorAlignment);
        }
        
        //Delete a 16 byte aligned Quaternion
        inline void Quaternion::operator delete(void* p)
        {
            aligned_free(p);
        }

        //Allocate a 16 byte aligned Quaternion array
        inline void* Quaternion::operator new[](size_t size)
        {
            return aligned_malloc(size, vectorAlignment);
        }

        //Delete a 16 byte aligned Quaternion
        inline void Quaternion::operator delete[](void* p)
        {
            aligned_free(p);
        }

        /** Compares the values of this Quaternion to another given Quaternion
        * \param p_rhs The other Quaternion
        * \return True if this Quaternion has the same values of the other Quaternion
        */
        inline bool Quaternion::operator==(const Quaternion& p_rhs) const
        {
            return MMVectorEqual(m_quaternion, p_rhs.m_quaternion);
        }

        /** Compares the values of this Quaternion to another given Quaternion
        * \param p_rhs The Other Quaternion
        * \return True if this Quaternion does not have the same values of the other Quaternion
        */
        inline bool Quaternion::operator!=(const Quaternion& p_rhs) const
        {
            return !operator==(p_rhs);
        }

        /** Adds the components of this Quaternion to another given Quaternion
        * \param p_rhs The other Quaternion
        * \return Quaternion with components summed (w = w1 + w2, ...)
        */
        inline Quaternion Quaternion::operator+(const Quaternion& p_rhs) const
        {
            return Quaternion(_mm_add_ps(m_quaternion, p_rhs.m_quaternion));
        }

        /** Subtracts the components of this Quaternion with another given Quaternion
        * \param p_rhs The other Quaternion
        * \return Quaternion with components subtracted (w = w1 - w2, ...)
        */
        inline Quaternion Quaternion::operator-(const Quaternion& p_rhs) const
        {
            return Quaternion(_mm_sub_ps(m_quaternion, p_rhs.m_quaternion));
        }

        /** Multiplies the quaternion with another Quaternion using the Hamilton Product
        * \param p_rhs The other Quaternion
        * \return Quaternion result of the Hamilton product of the two quaternions.
        */
        inline Quaternion Quaternion::operator*(const Quaternion& p_rhs) const
        {
			static const __m128 maskB = MMVectorSet(1.f, -1.f, 1.f, -1.f);
			static const __m128 maskC = MMVectorSet(1.f, 1.f, -1.f, -1.f);
			static const __m128 maskD = MMVectorSet(-1.f, 1.f, 1.f, -1.f);
			__m128 splatA = _mm_shuffle_ps(m_quaternion, m_quaternion, _MM_SHUFFLE(3, 3, 3, 3));
			__m128 splatB = _mm_shuffle_ps(m_quaternion, m_quaternion, _MM_SHUFFLE(2, 2, 2, 2));
			__m128 splatC = _mm_shuffle_ps(m_quaternion, m_quaternion, _MM_SHUFFLE(1, 1, 1, 1));
			__m128 splatD = _mm_shuffle_ps(m_quaternion, m_quaternion, _MM_SHUFFLE(0, 0, 0, 0));

			splatA = _mm_mul_ps(splatA, p_rhs.m_quaternion);
			splatB = _mm_mul_ps(_mm_mul_ps(splatB, maskB), _mm_shuffle_ps(p_rhs.m_quaternion, p_rhs.m_quaternion, _MM_SHUFFLE(3, 0, 1, 2)));
			splatC = _mm_mul_ps(_mm_mul_ps(splatC, maskC), _mm_shuffle_ps(p_rhs.m_quaternion, p_rhs.m_quaternion, _MM_SHUFFLE(2, 1, 0, 3)));
			splatD = _mm_mul_ps(_mm_mul_ps(splatD, maskD), _mm_shuffle_ps(p_rhs.m_quaternion, p_rhs.m_quaternion, _MM_SHUFFLE(1, 2, 3, 0)));

			splatA = _mm_add_ps(splatA, splatB);
			splatC = _mm_add_ps(splatC, splatD);

            return Quaternion(_mm_add_ps(splatA, splatC));
        }

        /** Adds the components of the other quaternion into this quaternion
        * \param p_rhs The other Quaternion
        * \return Reference to modified quaternion
        */
        inline Quaternion& Quaternion::operator+=(const Quaternion& p_rhs)
        {
            m_quaternion = _mm_add_ps(m_quaternion, p_rhs.m_quaternion);
            return *this;
        }

        /** Subtracts the components of the other quaternion from this quaternion
        * \param p_rhs The other Quaternion
        * \return Reference to modified quaternion
        */
        inline Quaternion& Quaternion::operator-=(const Quaternion& p_rhs)
        {
            m_quaternion = _mm_sub_ps(m_quaternion, p_rhs.m_quaternion);
            return *this;
        }

        /** Multiplies the two given quaternions using the Hamilton Product and stores
        * the results back into the first Quaternion
        * \param p_rhs The other Quaternion
        * \return Reference to modified quaternion
        */
        inline Quaternion& Quaternion::operator*=(const Quaternion& p_rhs)
        {
			static const __m128 maskB = MMVectorSet(1.f, -1.f, 1.f, -1.f);
			static const __m128 maskC = MMVectorSet(1.f, 1.f, -1.f, -1.f);
			static const __m128 maskD = MMVectorSet(-1.f, 1.f, 1.f, -1.f);
			__m128 splatA = _mm_shuffle_ps(m_quaternion, m_quaternion, _MM_SHUFFLE(3, 3, 3, 3));
			__m128 splatB = _mm_shuffle_ps(m_quaternion, m_quaternion, _MM_SHUFFLE(2, 2, 2, 2));
			__m128 splatC = _mm_shuffle_ps(m_quaternion, m_quaternion, _MM_SHUFFLE(1, 1, 1, 1));
			__m128 splatD = _mm_shuffle_ps(m_quaternion, m_quaternion, _MM_SHUFFLE(0, 0, 0, 0));

			splatA = _mm_mul_ps(splatA, p_rhs.m_quaternion);
			splatB = _mm_mul_ps(_mm_mul_ps(splatB, maskB), _mm_shuffle_ps(p_rhs.m_quaternion, p_rhs.m_quaternion, _MM_SHUFFLE(3, 0, 1, 2)));
			splatC = _mm_mul_ps(_mm_mul_ps(splatC, maskC), _mm_shuffle_ps(p_rhs.m_quaternion, p_rhs.m_quaternion, _MM_SHUFFLE(2, 1, 0, 3)));
			splatD = _mm_mul_ps(_mm_mul_ps(splatD, maskD), _mm_shuffle_ps(p_rhs.m_quaternion, p_rhs.m_quaternion, _MM_SHUFFLE(1, 2, 3, 0)));

			splatA = _mm_add_ps(splatA, splatB);
			splatC = _mm_add_ps(splatC, splatD);

            m_quaternion = _mm_add_ps(splatA, splatC);
            return *this;
        }

        /** Returns copy of internal __m128 structure
        * \return Copy of internal __m128 structure.
        */
        inline Quaternion::operator __m128() const
        {
            return m_quaternion;
        }

        /** Performs dot product of two quaternions
        * (w1 * w2 + x1 * x2 + ...)
        * \param q The first quaternion
        * \param r The second quaternion
        * \return result of the dot product.
        */
        inline float _MM_CALLCONV MMQuaternionDot(const Quaternion& q, const Quaternion& r)
        {
            __m128 dotProd = _mm_mul_ps(q.m_quaternion, r.m_quaternion);
            dotProd = _mm_add_ps(dotProd, _mm_shuffle_ps(dotProd, dotProd, _MM_SHUFFLE(2, 3, 0, 1)));
            dotProd = _mm_add_ps(dotProd, _mm_shuffle_ps(dotProd, dotProd, _MM_SHUFFLE(0, 1, 2, 3)));
            return MMVectorGetX(dotProd);
        }

        /** Creates a copy of given quaternion with unit length
        * \param q Quaternion to normalize
        * \return Normalized Quaternion
        */
        inline Quaternion _MM_CALLCONV MMQuaternionNormalize(const Quaternion& q)
        {
			assert(MMQuaternionMagnitudeSqr(q) > 0.f);
            __m128 dotProd = _mm_mul_ps(q.m_quaternion, q.m_quaternion);
            dotProd = _mm_add_ps(dotProd, _mm_shuffle_ps(dotProd, dotProd, _MM_SHUFFLE(2, 3, 0, 1)));
            dotProd = _mm_add_ps(dotProd, _mm_shuffle_ps(dotProd, dotProd, _MM_SHUFFLE(0, 1, 2, 3)));
            dotProd = _mm_rsqrt_ps(dotProd);
            return Quaternion(_mm_mul_ps(q.m_quaternion, dotProd));
        }

        /** Calculates the magnitude (length) of the given quaternion
        * \param q Quaternion to calculate Magnitude from
        * \return magnitude (length) of quaternion
        */
        inline float _MM_CALLCONV MMQuaternionMagnitude(const Quaternion& q)
        {
            return sqrtf(MMQuaternionMagnitudeSqr(q));
        }

        /** Calculates the square magnitude (square length) of the given quaternion
        * NOTE: This function is faster then MMQuaternionMagnitude, use when comparing
        * magnitudes of quaternions
        * \param q Quaternion to calculate square magnitude from
        * \return Square of magnitude (length) of quaternion
        */
        inline float _MM_CALLCONV MMQuaternionMagnitudeSqr(const Quaternion& q)
        {
            return MMQuaternionDot(q, q);
        }

        /** Calculates the conjugate of the given Quaternion
        * \param q Quaternion to get conjugate from
        * \return Conjugate of Quaternion.
        */
        inline Quaternion _MM_CALLCONV MMQuaternionConjugate(const Quaternion& q)
        {
            static const __m128 signMask = MMVectorSet(-1.f, -1.f, -1.f, 1.f);
            return Quaternion(_mm_mul_ps(q.m_quaternion, signMask));
        }
    }
}