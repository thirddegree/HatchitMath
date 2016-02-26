
//////////////////////////////////////////////////////////////////////
// MMVECTOR3 Implementation
//////////////////////////////////////////////////////////////////////

///Create a Vector3 with all 3 elements being 0
inline Hatchit::Math::Vector3::Vector3()
{
    this->m_vector = _mm_setzero_ps();
}

///Create a Vector3 with the elements x, y and z
inline Hatchit::Math::Vector3::Vector3(float x, float y, float z)
{
    float zero = 0;

    __m128 xx = _mm_load_ss(&x);
    __m128 xy = _mm_load_ss(&y);
    __m128 xz = _mm_load_ss(&z);
    __m128 xw = _mm_load_ss(&zero);

    this->m_vector = _mm_movelh_ps(_mm_unpacklo_ps(xx, xy), _mm_unpacklo_ps(xz, xw));
}

///Create a copy of an existing Vector3
inline Hatchit::Math::Vector3::Vector3(const Vector3& other)
{
    this->m_vector = other.m_vector;
}

///Create a Vector3 with the first three elements of a given Vector4 all divided by the 4th element
inline Hatchit::Math::Vector3::Vector3(Hatchit::Math::Vector4& v4)
{
    //We'll just ignore the last element of the __m128 so just do a copy by value
    this->m_vector = (__m128)v4;

    _MM_ALIGN16 float temp[4];
    _mm_store_ps(temp, m_vector);
    m_vector = _mm_set_ps(0, temp[2], temp[1], temp[0]);
}

//Allocate a 16byte aligned array of Vector3
void* Hatchit::Math::Vector3::operator new(size_t _size)
{
    return aligned_malloc(sizeof(__m128), _size);
}

//Delete an array of Vector3
void Hatchit::Math::Vector3::operator delete(void* p)
{
    aligned_free(p);
}

/** Casts a Vector3 object to a __m128
* This operator casts a Vector3 to an instrinsic __m128
*/
Hatchit::Math::Vector3::operator const __m128(void) const
{
    return m_vector;
}

//Scalar operators
Hatchit::Math::Vector3 Hatchit::Math::Vector3::operator*(float s)
{
    Vector3 vec;

    __m128 product = _mm_mul_ps(m_vector, Scalar(s));

    vec.m_vector = product;

    return vec;
}

Hatchit::Math::Vector3 Hatchit::Math::Vector3::operator/(float s)
{
    Vector3 vec;

    //Do division only once and then multiply by the inverse
    float invS = 1 / s;
    __m128 product = _mm_mul_ps(m_vector, Scalar(invS));

    vec.m_vector = product;

    return vec;
}

Hatchit::Math::Vector3 Hatchit::Math::Vector3::operator-(float s)
{
    Vector3 vec;

    __m128 product = _mm_sub_ps(m_vector, Scalar(s));

    vec.m_vector = product;

    return vec;
}

Hatchit::Math::Vector3 Hatchit::Math::Vector3::operator+(float s)
{
    Vector3 vec;

    __m128 product = _mm_add_ps(m_vector, Scalar(s));

    vec.m_vector = product;

    return vec;
}

Hatchit::Math::Vector3 Hatchit::Math::Vector3::operator*=(float s)
{
    m_vector = _mm_mul_ps(m_vector, Scalar(s));

    return (*this);
}

Hatchit::Math::Vector3 Hatchit::Math::Vector3::operator/=(float s)
{
    //Do division only once and then multiply by the inverse
    float invS = 1 / s;

    m_vector = _mm_mul_ps(m_vector, Scalar(invS));

    return (*this);
}

Hatchit::Math::Vector3 Hatchit::Math::Vector3::operator-=(float s)
{
    m_vector = _mm_sub_ps(m_vector, Scalar(s));

    return (*this);
}

Hatchit::Math::Vector3 Hatchit::Math::Vector3::operator+=(float s)
{
    m_vector = _mm_add_ps(m_vector, Scalar(s));

    return (*this);
}

bool Hatchit::Math::Vector3::operator>(Vector3 u)
{ 
    return Hatchit::Math::MMVector3Magnitude(*this) > Hatchit::Math::MMVector3Magnitude(u);
}

bool Hatchit::Math::Vector3::operator<(Vector3 u) 
{ 
    return Hatchit::Math::MMVector3Magnitude(*this) < Hatchit::Math::MMVector3Magnitude(u);
}

bool Hatchit::Math::Vector3::operator==(Vector3 u)
{
    return _mm_movemask_ps(_mm_cmpeq_ps(m_vector, u.m_vector)) == 15;
}
bool Hatchit::Math::Vector3::operator!=(Vector3 u)
{
    return _mm_movemask_ps(_mm_cmpeq_ps(m_vector, u.m_vector)) != 15;
}

//Vector operators
Hatchit::Math::Vector3 Hatchit::Math::Vector3::operator* (Vector3 u)
{
    MMVECTOR3 v;
    v.m_vector = _mm_mul_ps(this->m_vector, u.m_vector);

    return v;
}

Hatchit::Math::Vector3 Hatchit::Math::Vector3::operator+(Vector3 u)
{
    Vector3 vec;

    __m128 sum = _mm_add_ps(m_vector, u.m_vector);

    vec.m_vector = sum;

    return vec;
}

Hatchit::Math::Vector3 Hatchit::Math::Vector3::operator-(Vector3 u)
{
    Vector3 vec;

    __m128 diff = _mm_sub_ps(m_vector, u.m_vector);

    vec.m_vector = diff;

    return vec;
}

Hatchit::Math::Vector3 Hatchit::Math::Vector3::operator+=(Vector3 u)
{
    m_vector = _mm_add_ps(m_vector, u.m_vector);

    return (*this);
}

Hatchit::Math::Vector3 Hatchit::Math::Vector3::operator-=(Vector3 u)
{
    m_vector = _mm_sub_ps(m_vector, u.m_vector);

    return (*this);
}

float& Hatchit::Math::Vector3::operator[](int i)
{
    assert(i < 3);

    return this->m_data[i];
}


/** Executes the Dot product on two Vector3s as v * u
* \param v The first Vector3
* \param u The second Vector3
* \return The Dot product of v and u as a float
*/
inline float _MM_CALLCONV MMVector3Dot(MMVECTOR3 v, MMVECTOR3 u)
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
inline MMVECTOR3 _MM_CALLCONV MMVector3Cross(MMVECTOR3 v, MMVECTOR3 u)
{
    MMVECTOR3 output;

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
inline MMVECTOR3 _MM_CALLCONV MMVector3Normalize(MMVECTOR3 v)
{
    float magnitude = v.getMagnitude();

    if (magnitude == 0)
        magnitude = 1;

    MMVECTOR3 normalizedVec;

    float invMag = 1 / magnitude;
    normalizedVec.m_vector = _mm_mul_ps(v.m_vector, Hatchit::Math::MMVectorSet(invMag, invMag, invMag, invMag));

    return normalizedVec;
}

/** Returns the magnitude of the vector
* \return The magnitude as a float
*/
inline float _MM_CALLCONV MMVector3Magnitude(MMVECTOR3 v)
{
    __m128 val = _mm_mul_ps(v.m_vector, v.m_vector);

    val = _mm_add_ps(val, _mm_shuffle_ps(val, val, _MM_SHUFFLE(3, 2, 1, 1)));
    val = _mm_add_ps(val, _mm_shuffle_ps(val, val, _MM_SHUFFLE(3, 2, 2, 2)));
    val = _mm_sqrt_ss(val);

    return Hatchit::Math::MMVectorGetX(val);
}