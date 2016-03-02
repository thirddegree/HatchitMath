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

        inline Quaternion Quaternion::operator*(const Quaternion& p_rhs) const
        {
            __m128 splatA = _mm_set1_ps(x);
            __m128 splatB = _mm_set_ps(-y, y, -y, y);
            __m128 splatC = _mm_set_ps(-z, z, z, -z);
            __m128 splatD = _mm_set_ps(-w, -w, w, w);

            splatA = _mm_mul_ps(splatA, p_rhs.m_quaternion);
            splatB = _mm_mul_ps(splatB, _mm_shuffle_ps(p_rhs.m_quaternion, p_rhs.m_quaternion, _MM_SHUFFLE(2, 3, 0, 1)));
            splatC = _mm_mul_ps(splatC, _mm_shuffle_ps(p_rhs.m_quaternion, p_rhs.m_quaternion, _MM_SHUFFLE(1, 0, 3, 2)));
            splatD = _mm_mul_ps(splatD, _mm_shuffle_ps(p_rhs.m_quaternion, p_rhs.m_quaternion, _MM_SHUFFLE(0, 1, 2, 3)));

            splatA = _mm_add_ps(splatA, splatB);
            splatC = _mm_add_ps(splatC, splatD);

            return Quaternion(_mm_add_ps(splatA, splatC));
        }

        inline Quaternion& Quaternion::operator*=(const Quaternion& p_rhs)
        {
            __m128 splatA = _mm_set1_ps(x);
            __m128 splatB = _mm_set_ps(-y, y, -y, y);
            __m128 splatC = _mm_set_ps(-z, z, z, -z);
            __m128 splatD = _mm_set_ps(-w, -w, w, w);

            splatA = _mm_mul_ps(splatA, p_rhs.m_quaternion);
            splatB = _mm_mul_ps(splatB, _mm_shuffle_ps(p_rhs.m_quaternion, p_rhs.m_quaternion, _MM_SHUFFLE(2, 3, 0, 1)));
            splatC = _mm_mul_ps(splatC, _mm_shuffle_ps(p_rhs.m_quaternion, p_rhs.m_quaternion, _MM_SHUFFLE(1, 0, 3, 2)));
            splatD = _mm_mul_ps(splatD, _mm_shuffle_ps(p_rhs.m_quaternion, p_rhs.m_quaternion, _MM_SHUFFLE(0, 1, 2, 3)));

            splatA = _mm_add_ps(splatA, splatB);
            splatC = _mm_add_ps(splatC, splatD);

            m_quaternion = _mm_add_ps(splatA, splatC);
            return *this;
        }

        inline Quaternion::operator __m128() const
        {
            return m_quaternion;
        }
    }
}