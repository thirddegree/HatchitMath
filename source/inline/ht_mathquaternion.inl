#include <ht_math.h>

namespace Hatchit {

    namespace Math {

        inline Quaternion::Quaternion() : m_quaternion(MMVectorSet(0.0f, 0.0f, 0.0f, 1.0f)) {}
        inline Quaternion::Quaternion(float x, float y, float z, float w) : m_quaternion(MMVectorSet(x, y, z, w)) {}
        inline Quaternion::Quaternion(const Vector3& axis, float angle) : m_quaternion(MMVectorSetW(static_cast<__m128>(axis * sinf(angle / 2)), cosf(angle / 2))) {}
        inline Quaternion::Quaternion(float roll, float pitch, float yaw) : m_quaternion()
        {
            //TODO: Who wants to make this intrinsic?  Anyone?
            float cosRoll = cosf(roll);
            float cosPitch = cosf(pitch);
            float cosYaw = cosf(yaw);
            float sinRoll = sinf(roll);
            float sinPitch = sinf(pitch);
            float sinYaw = sinf(yaw);

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

        inline Quaternion::Quaternion(__m128 quatData) : m_quaternion(std::move(quatData)) {}

        inline bool Quaternion::operator==(const Quaternion& p_rhs) const
        {
            return MMVectorEqual(m_quaternion, p_rhs.m_quaternion);
        }

        inline bool Quaternion::operator!=(const Quaternion& p_rhs) const
        {
            return !operator==(p_rhs);
        }

        inline Quaternion Quaternion::operator+(const Quaternion& p_rhs) const
        {
            return Quaternion(_mm_add_ps(m_quaternion, p_rhs.m_quaternion));
        }
        inline Quaternion Quaternion::operator-(const Quaternion& p_rhs) const
        {
            return Quaternion(_mm_sub_ps(m_quaternion, p_rhs.m_quaternion));
        }
        inline Quaternion Quaternion::operator*(const Quaternion& p_rhs) const
        {
            static const __m128 maskB = _mm_castsi128_ps(_mm_setr_epi32(-1, 0, -1, 0));
            static const __m128 maskC = _mm_castsi128_ps(_mm_setr_epi32(-1, 0, 0, -1));
            static const __m128 maskD = _mm_castsi128_ps(_mm_setr_epi32(-1, -1, 0, 0));
            __m128 splatA = _mm_shuffle_ps(m_quaternion, m_quaternion, _MM_SHUFFLE(3, 3, 3, 3));
            __m128 splatB = _mm_shuffle_ps(m_quaternion, m_quaternion, _MM_SHUFFLE(2, 2, 2, 2));
            __m128 splatC = _mm_shuffle_ps(m_quaternion, m_quaternion, _MM_SHUFFLE(1, 1, 1, 1));
            __m128 splatD = _mm_shuffle_ps(m_quaternion, m_quaternion, _MM_SHUFFLE(0, 0, 0, 0));
            
            splatA = _mm_mul_ps(splatA, p_rhs.m_quaternion);
            splatB = _mm_mul_ps(_mm_xor_ps(splatB, maskB), _mm_shuffle_ps(p_rhs.m_quaternion, p_rhs.m_quaternion, _MM_SHUFFLE(2, 3, 0, 1)));
            splatC = _mm_mul_ps(_mm_xor_ps(splatC, maskC), _mm_shuffle_ps(p_rhs.m_quaternion, p_rhs.m_quaternion, _MM_SHUFFLE(1, 0, 3, 2)));
            splatD = _mm_mul_ps(_mm_xor_ps(splatD, maskD), _mm_shuffle_ps(p_rhs.m_quaternion, p_rhs.m_quaternion, _MM_SHUFFLE(0, 1, 2, 3)));
            
            splatA = _mm_add_ps(splatA, splatB);
            splatC = _mm_add_ps(splatC, splatD);

            return Quaternion(_mm_add_ps(splatA, splatC));
        }

        inline Quaternion& Quaternion::operator+=(const Quaternion& p_rhs)
        {
            m_quaternion = _mm_add_ps(m_quaternion, p_rhs.m_quaternion);
            return *this;
        }
        inline Quaternion& Quaternion::operator-=(const Quaternion& p_rhs)
        {
            m_quaternion = _mm_sub_ps(m_quaternion, p_rhs.m_quaternion);
            return *this;
        }
        inline Quaternion& Quaternion::operator*=(const Quaternion& p_rhs)
        {
            static const __m128 maskB = _mm_castsi128_ps(_mm_setr_epi32(-1, 0, -1, 0));
            static const __m128 maskC = _mm_castsi128_ps(_mm_setr_epi32(-1, 0, 0, -1));
            static const __m128 maskD = _mm_castsi128_ps(_mm_setr_epi32(-1, -1, 0, 0));
            __m128 splatA = _mm_shuffle_ps(m_quaternion, m_quaternion, _MM_SHUFFLE(3, 3, 3, 3));
            __m128 splatB = _mm_shuffle_ps(m_quaternion, m_quaternion, _MM_SHUFFLE(2, 2, 2, 2));
            __m128 splatC = _mm_shuffle_ps(m_quaternion, m_quaternion, _MM_SHUFFLE(1, 1, 1, 1));
            __m128 splatD = _mm_shuffle_ps(m_quaternion, m_quaternion, _MM_SHUFFLE(0, 0, 0, 0));

            splatA = _mm_mul_ps(splatA, p_rhs.m_quaternion);
            splatB = _mm_mul_ps(_mm_xor_ps(splatB, maskB), _mm_shuffle_ps(p_rhs.m_quaternion, p_rhs.m_quaternion, _MM_SHUFFLE(2, 3, 0, 1)));
            splatC = _mm_mul_ps(_mm_xor_ps(splatC, maskC), _mm_shuffle_ps(p_rhs.m_quaternion, p_rhs.m_quaternion, _MM_SHUFFLE(1, 0, 3, 2)));
            splatD = _mm_mul_ps(_mm_xor_ps(splatD, maskD), _mm_shuffle_ps(p_rhs.m_quaternion, p_rhs.m_quaternion, _MM_SHUFFLE(0, 1, 2, 3)));

            splatA = _mm_add_ps(splatA, splatB);
            splatC = _mm_add_ps(splatC, splatD);

            m_quaternion = _mm_add_ps(splatA, splatC);
            return *this;
        }

        inline Quaternion::operator __m128() const
        {
            return m_quaternion;
        }

        inline float _MM_CALLCONV MMQuaternionDot(const Quaternion& q, const Quaternion& r)
        {
            __m128 dotProd = _mm_mul_ps(q.m_quaternion, r.m_quaternion);
            dotProd = _mm_add_ps(dotProd, _mm_shuffle_ps(dotProd, dotProd, _MM_SHUFFLE(2, 3, 0, 1)));
            dotProd = _mm_add_ps(dotProd, _mm_shuffle_ps(dotProd, dotProd, _MM_SHUFFLE(0, 1, 2, 3)));
            return MMVectorGetX(dotProd);
        }

        inline Quaternion _MM_CALLCONV MMQuaternionNormalize(const Quaternion& q)
        {
            __m128 dotProd = _mm_mul_ps(q.m_quaternion, q.m_quaternion);
            dotProd = _mm_add_ps(dotProd, _mm_shuffle_ps(dotProd, dotProd, _MM_SHUFFLE(2, 3, 0, 1)));
            dotProd = _mm_add_ps(dotProd, _mm_shuffle_ps(dotProd, dotProd, _MM_SHUFFLE(0, 1, 2, 3)));
            dotProd = _mm_rsqrt_ps(dotProd);
            return Quaternion(_mm_div_ps(q.m_quaternion, dotProd));
        }

        inline float _MM_CALLCONV MMQuaternionMagnitude(const Quaternion& q)
        {
            return sqrtf(MMQuaternionMagnitudeSqr(q));
        }

        inline float _MM_CALLCONV MMQuaternionMagnitudeSqr(const Quaternion& q)
        {
            return MMQuaternionDot(q, q);
        }

        inline Quaternion _MM_CALLCONV MMQuaternionConjugate(const Quaternion& q)
        {
            static const __m128 signMask = _mm_castsi128_ps(_mm_setr_epi32(0, -1, 0, -1));
            return Quaternion(_mm_xor_ps(q.m_quaternion, signMask));
        }
    }
}