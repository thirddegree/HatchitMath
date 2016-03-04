
namespace Hatchit {

    namespace Math {

        inline __m128 _MM_CALLCONV MMVectorZero()
        {
            return _mm_setzero_ps();
        }

        inline __m128 _MM_CALLCONV MMVectorSet(float x, float y, float z, float w)
        {
            return _mm_set_ps(w, z, y, x);
        }

        inline __m128 _MM_CALLCONV MMVectorSetInt(uint32_t x, uint32_t y, uint32_t z, uint32_t w)
        {
            __m128i v = _mm_set_epi32(w, z, y, z);

            return _mm_castsi128_ps(v);
        }

        inline float _MM_CALLCONV MMVectorGetX(__m128 v)
        {
            //extract the lowest bit value (x)
            return _mm_cvtss_f32(v);
        }

        inline float _MM_CALLCONV MMVectorGetY(__m128 v)
        {
            // place y into all locations
            __m128 temp = _mm_shuffle_ps(v, v, _MM_SHUFFLE(1, 1, 1, 1));

            return _mm_cvtss_f32(temp);
        }

        inline float _MM_CALLCONV MMVectorGetZ(__m128 v)
        {
            //place z into all locations
            __m128 temp = _mm_shuffle_ps(v, v, _MM_SHUFFLE(2, 2, 2, 2));

            return _mm_cvtss_f32(temp);
        }

        inline float _MM_CALLCONV MMVectorGetW(__m128 v)
        {
            //place w into all locations
            __m128 temp = _mm_shuffle_ps(v, v, _MM_SHUFFLE(3, 3, 3, 3));

            return _mm_cvtss_f32(temp);
        }

        inline void _MM_CALLCONV MMVectorGetXRaw(float* x, __m128 v)
        {
            _mm_store_ss(x, v);
        }

        inline void _MM_CALLCONV MMVectorGetYRaw(float* y, __m128 v)
        {
            _mm_shuffle_ps(v, v, _MM_SHUFFLE(1, 1, 1, 1));

            _mm_store_ss(y, v);
        }

        inline void _MM_CALLCONV MMVectorGetZRaw(float* z, __m128 v)
        {
            _mm_shuffle_ps(v, v, _MM_SHUFFLE(2, 2, 2, 2));

            _mm_store_ss(z, v);
        }

        inline void _MM_CALLCONV MMVectorGetWRaw(float* w, __m128 v)
        {
            _mm_shuffle_ps(v, v, _MM_SHUFFLE(3, 3, 3, 3));

            _mm_store_ss(w, v);
        }

        inline __m128 _MM_CALLCONV MMVectorSetX(__m128 v, float x)
        {
            //set X value, rest default to 0
            __m128 result = _mm_set_ss(x);

            //move Y, Z, W values to result
            result = _mm_move_ss(v, result);

            return result;
        }

        inline __m128 _MM_CALLCONV MMVectorSetY(__m128 v, float y)
        {
            //swap Y and X. RESULT: (yOrig, xOrig, zOrig, wOrig)
            __m128 result = _mm_shuffle_ps(v, v, _MM_SHUFFLE(3, 2, 0, 1));
            __m128 temp = _mm_set_ss(y); // RESULT: (y, 0, 0, 0)

            result = _mm_move_ss(result, temp); //RESULT: (y, xOrig, zOrig, wOrig)
            //swap Y and X back. RESULT: (xOrig, y, zOrig, wOrig)
            result = _mm_shuffle_ps(result, result, _MM_SHUFFLE(3, 2, 0, 1));

            return result;
        }

        inline __m128 _MM_CALLCONV MMVectorSetZ(__m128 v, float z)
        {
            __m128 result = _mm_shuffle_ps(v, v, _MM_SHUFFLE(3, 0, 1, 2));
            __m128 temp = _mm_set_ss(z);

            result = _mm_move_ss(result, temp);
            result = _mm_shuffle_ps(result, result, _MM_SHUFFLE(3, 0, 1, 2));

            return result;
        }

        inline __m128 _MM_CALLCONV MMVectorSetW(__m128 v, float w)
        {
            __m128 result = _mm_shuffle_ps(v, v, _MM_SHUFFLE(0, 2, 1, 3));
            __m128 temp = _mm_set_ss(w);

            result = _mm_move_ss(result, temp);
            result = _mm_shuffle_ps(result, result, _MM_SHUFFLE(0, 2, 1, 3));

            return result;
        }

        inline __m128 _MM_CALLCONV MMVectorSetXRaw(__m128 v, const float* x)
        {
            __m128 result = _mm_load_ss(x);

            result = _mm_move_ss(v, result);

            return result;
        }

        inline __m128 _MM_CALLCONV MMVectorSetYRaw(__m128 v, const float* y)
        {
            __m128 result = _mm_shuffle_ps(v, v, _MM_SHUFFLE(3, 2, 0, 1));
            __m128 temp = _mm_load_ss(y);

            result = _mm_move_ss(result, temp);
            result = _mm_shuffle_ps(result, result, _MM_SHUFFLE(3, 2, 0, 1));

            return result;
        }

        inline __m128 _MM_CALLCONV MMVectorSetZRaw(__m128 v, const float* z)
        {
            __m128 result = _mm_shuffle_ps(v, v, _MM_SHUFFLE(3, 0, 1, 2));
            __m128 temp = _mm_load_ss(z);

            result = _mm_move_ss(result, temp);
            result = _mm_shuffle_ps(result, result, _MM_SHUFFLE(3, 0, 1, 2));

            return result;
        }

        inline __m128 _MM_CALLCONV MMVectorSetWRaw(__m128 v, const float* w)
        {
            __m128 result = _mm_shuffle_ps(v, v, _MM_SHUFFLE(0, 2, 1, 3));
            __m128 temp = _mm_load_ss(w);

            result = _mm_move_ss(result, temp);
            result = _mm_shuffle_ps(result, result, _MM_SHUFFLE(0, 2, 1, 3));

            return result;
        }

        inline bool _MM_CALLCONV MMVectorEqual(__m128 v, __m128 u)
        {
            __m128 compMask = _mm_cmpeq_ps(v, u);
            return _mm_movemask_ps(compMask) == 15;
        }
    }
}
