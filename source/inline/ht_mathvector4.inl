namespace Hatchit
{
    namespace Math
    {
        inline Vector4::Vector4() : m_vector() {}

        inline Vector4::Vector4(float x, float y, float z, float w)
        {
            float dataArray[4] { w, z, y, x };
            m_vector = _mm_load_ps(&dataArray[0]);
        }

        inline Vector4::Vector4(const Vector4& other)
        {
            m_vector = other.m_vector;
        }

        //Why is this not allowed to be const?
        inline Vector4::Vector4(const Vector3& v3, float w)
        {
            m_vector = static_cast<__m128>(v3);
            m_vector = MMVectorSetWRaw(m_vector, &w);
        }

        inline Vector4::Vector4(__m128 intrinsicVec) : m_vector(std::move(intrinsicVec)) {}

        inline void* Vector4::operator new(size_t _size)
        {
            return aligned_malloc(sizeof(__m128), _size);
        }

        inline void Vector4::operator delete(void* p)
        {
            aligned_free(p);
        }

        inline Vector4::operator __m128(void) const
        {
            return m_vector;
        }

        inline float Vector4::magSqr() const
        {
            return MMVector4Dot(*this, *this);
        }

        inline float Vector4::mag() const
        {
            //Feel free to replace sqrtf with any preferred square root function.
            //Or we can rewrite this to use square root intrinsics.
            return sqrtf(magSqr());
        }

        inline Vector4 Vector4::normalized() const
        {
            __m128 normalizedVec = _mm_mul_ps(m_vector, m_vector);
            normalizedVec = _mm_add_ps(normalizedVec, _mm_shuffle_ps(normalizedVec, normalizedVec, _MM_SHUFFLE(2, 3, 0, 1)));
            normalizedVec = _mm_add_ps(normalizedVec, _mm_shuffle_ps(normalizedVec, normalizedVec, _MM_SHUFFLE(0, 1, 2, 3)));
            normalizedVec = _mm_rsqrt_ps(normalizedVec);
            Vector4 returnValue;
            returnValue.m_vector = _mm_mul_ps(m_vector, normalizedVec);
        }

        inline float MMVector4Dot(Vector4 lhs, Vector4 rhs)
        {
            __m128 dotProd = _mm_mul_ps(lhs.m_vector, rhs.m_vector);
            dotProd = _mm_add_ps(dotProd, _mm_shuffle_ps(dotProd, dotProd, _MM_SHUFFLE(2, 3, 0, 1)));
            dotProd = _mm_add_ps(dotProd, _mm_shuffle_ps(dotProd, dotProd, _MM_SHUFFLE(0, 1, 2, 3)));
            float returnValue;
            _mm_store_ss(&returnValue, dotProd);
            return returnValue;
        }

        inline Vector4 Vector4::operator* (float s) const
        {
            return Vector4(_mm_mul_ps(m_vector, _mm_set1_ps(s)));
        }

        inline Vector4 Vector4::operator/(float s) const
        {
            return Vector4(_mm_div_ps(m_vector, _mm_set1_ps(s)));
        }

        inline Vector4 Vector4::operator-(float s) const
        {
            return Vector4(_mm_sub_ps(m_vector, _mm_set1_ps(s)));
        }

        inline Vector4 Vector4::operator+(float s) const
        {
            return Vector4(_mm_add_ps(m_vector, _mm_set1_ps(s)));
        }

        inline Vector4& Vector4::operator*=(float s)
        {
            m_vector = _mm_add_ps(m_vector, _mm_set1_ps(s));
            return *this;
        }

        inline Vector4& Vector4::operator/=(float s)
        {
            m_vector = _mm_div_ps(m_vector, _mm_set1_ps(s));
            return *this;
        }

        inline Vector4& Vector4::operator+=(float s)
        {
            m_vector = _mm_add_ps(m_vector, _mm_set1_ps(s));
            return *this;
        }

        inline Vector4& Vector4::operator-=(float s)
        {
            m_vector = _mm_sub_ps(m_vector, _mm_set1_ps(s));
            return *this;
        }

        inline bool Vector4::operator>(Vector4 rhs) const
        {
            return magSqr() > rhs.magSqr();
        }
        inline bool Vector4::operator<(Vector4 rhs) const
        {
            return magSqr() < rhs.magSqr();
        }
        inline bool Vector4::operator==(Vector4 rhs) const
        {
            //This may have too little of epsilon to be considered accurate.
            //Could add and subtract epsilon from rhs.m_vector, compare less than /
            //greater than, logic and the components and then check in the future
            //If this is too strict.
            __m128 compMask = _mm_cmpeq_ps(m_vector, rhs.m_vector);
            return _mm_movemask_ps(compMask) == 7;
        }
        inline bool Vector4::operator!=(Vector4 rhs) const
        {
            return !operator==(rhs);
        }

        //Memberwise multiplication
        inline Vector4 Vector4::operator*(Vector4 rhs) const
        {
            return Vector4(_mm_mul_ps(m_vector, rhs.m_vector));
        }

        inline Vector4 Vector4::operator+(Vector4 rhs) const
        {
            return Vector4(_mm_add_ps(m_vector, rhs.m_vector));
        }

        inline Vector4& Vector4::operator+=(Vector4 rhs)
        {
            m_vector = _mm_add_ps(m_vector, rhs.m_vector);
            return *this;
        }

        inline Vector4& Vector4::operator-=(Vector4 rhs)
        {
            m_vector = _mm_sub_ps(m_vector, rhs.m_vector);
            return *this;
        }

        inline float& Vector4::operator[](size_t i)
        {
            return data[i];
        }

        inline const float& Vector4::operator[](size_t i) const
        {
            return data[i];
        }

        inline Vector4::operator Hatchit::Math::Vector3() const
        {
            _MM_ALIGN16 float vecArray[4];
            _mm_store_ps(&vecArray[0], m_vector);
            return Vector3(vecArray[0], vecArray[1], vecArray[2]);
        }

        inline Vector4::operator Hatchit::Math::Vector2() const
        {
            _MM_ALIGN16 float vecArray[4];
            _mm_store_ps(&vecArray[0], m_vector);
            return Vector2(vecArray[0], vecArray[1]);
        }
    }
}