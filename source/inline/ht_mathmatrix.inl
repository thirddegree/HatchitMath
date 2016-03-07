#include <ht_math.h>

namespace Hatchit
{
    namespace Math
    {

        /////////////////////////////////////////////////////////////
        // Matrix4 Implementation
        /////////////////////////////////////////////////////////////

        /**Generates a translation matrix with the given vector3 values
        *\param v vector3 to translate by
        *\return the translation matrix
        */
        inline Matrix4 _MM_CALLCONV MMMatrixTranslation(const Vector3 & v)
        {
            return Matrix4(1, 0, 0, v.x,
                           0, 1, 0, v.y,
                           0, 0, 1, v.z,
                           0, 0, 0, 1);
        }

        inline Matrix4 _MM_CALLCONV MMMatrixRotationX(float r)
        {
            Matrix4 result;

            result.m_rows[0] = _mm_set_ss(1);
            result.m_rows[1] = _mm_setr_ps(0, cosf(r),-sinf(r), 0);
            result.m_rows[2] = _mm_setr_ps(0, sinf(r), cosf(r), 0);
            result.m_rows[3] = _mm_set_ss(1);
            result.m_rows[3] = _mm_shuffle_ps(result.m_rows[3], result.m_rows[3], _MM_SHUFFLE(0, 2, 2, 2));

            return result;
        }

        inline Matrix4 _MM_CALLCONV MMMatrixRotationY(float r)
        {
            Matrix4 result;

            result.m_rows[0] = _mm_setr_ps(cosf(r), 0, sinf(r), 0);
            result.m_rows[1] = _mm_set_ss(1);
            result.m_rows[1] = _mm_shuffle_ps(result.m_rows[1], result.m_rows[1], _MM_SHUFFLE(2, 2, 0, 2));
            result.m_rows[2] = _mm_setr_ps(-sinf(r), 0, cosf(r), 0);
            result.m_rows[3] = _mm_set_ss(1);
            result.m_rows[3] = _mm_shuffle_ps(result.m_rows[3], result.m_rows[3], _MM_SHUFFLE(0, 2, 2, 2));

            return result;
        }

        inline Matrix4 _MM_CALLCONV MMMatrixRotationZ(float r)
        {
            Matrix4 result;

            result.m_rows[0] = _mm_setr_ps(cosf(r), -sinf(r), 0, 0);
            result.m_rows[1] = _mm_setr_ps(sinf(r), cosf(r), 0, 0);
            result.m_rows[2] = _mm_set_ss(1);
            result.m_rows[2] = _mm_shuffle_ps(result.m_rows[2], result.m_rows[2], _MM_SHUFFLE(2, 0, 2, 2));
            result.m_rows[3] = _mm_set_ss(1);
            result.m_rows[3] = _mm_shuffle_ps(result.m_rows[3], result.m_rows[3], _MM_SHUFFLE(0, 2, 2, 2));

            return result;
        }

        inline Matrix4 _MM_CALLCONV MMMatrixRotationXYZ(const Vector3 & r)
        {
            return (MMMatrixRotationY(r.y) * MMMatrixRotationX(r.x)) * MMMatrixRotationZ(r.z);
        }


        inline Matrix4 _MM_CALLCONV MMMatrixScale(const Vector3 & scale)
        {
            Matrix4 result;

            result.m_rows[0] = _mm_set_ss(scale.x);
            result.m_rows[3] = _mm_set_ps(0, scale.y, scale.z, 1);
            result.m_rows[1] = _mm_shuffle_ps(result.m_rows[3], result.m_rows[3], _MM_SHUFFLE(0, 0, 1, 0));
            result.m_rows[2] = _mm_shuffle_ps(result.m_rows[3], result.m_rows[3], _MM_SHUFFLE(0, 2, 0, 0));
            result.m_rows[3] = _mm_shuffle_ps(result.m_rows[3], result.m_rows[3], _MM_SHUFFLE(3, 0, 0, 0));

            return result;
        }

        /** Generates an orthographic projection from the given values
        * \param left The lefthand bound
        * \param right The righthand bound
        * \param top The topmost bound
        * \param znear The near plane
        * \param zfar The far plane
        * \return The resulting orthographic projection in a Matrix4
        */
        inline Matrix4 _MM_CALLCONV MMMatrixOrthoProj(float left, float right, float bottom, float top, float znear, float zfar)
        {
            float a = 2 / (right - left);
            float b = 2 / (top - bottom);
            float c = 2 / (znear - zfar);
            float d = (right + left) / (left - right);
            float e = (top + bottom) / (bottom - top);
            float f = (zfar + znear) / (znear - zfar);

            return Matrix4(a, 0, 0, 0,
                           0, b, 0, 0,
                           0, 0, c, 0,
                           d, e, f, 1);
        }

        /** Generates a perspective projection from the given values
        * \param fov The field of view
        * \param aspect The aspect ratio
        * \param znear The near plane
        * \param zfar The far plane
        * \return The resulting perspective projection in a Matrix4
        */
        inline Matrix4 _MM_CALLCONV MMMatrixPerspProj(float fov, float aspect, float znear, float zfar)
        {
            //thanks to https://stackoverflow.com/questions/18404890/how-to-build-perspective-projection-matrix-no-api
            float height = 1 / tanf(0.5f * fov);
            float width = height * aspect;
            float depth = zfar - znear;

            return Matrix4( width,  0.0f,   0.0f,   0.0f,
                            0.0f,   height, 0.0f,   0.0f,
                            0.0f,   0.0f,   -(zfar + znear) / depth, -(2 * zfar * znear) / depth,
                            0.0f,   0.0f, -1.f , 0.0f);
        }

        /** Generates a view matrix from the given values
        * \param eye The point that the camera is located
        * \param lookAt The point for the camera to look at
        * \param up The vector representing which way is up for this camera
        * \return The resulting view matrix in a Matrix4
        */
        inline Matrix4 _MM_CALLCONV MMMatrixLookAt(const Vector3& eye, const Vector3& lookAt, const Vector3& up)
        {
            //Calculate axes
            Vector3 zAxis = MMVector3Normalize((lookAt - eye));
            Vector3 xAxis = MMVector3Normalize(MMVector3Cross(zAxis, up));
            Vector3 yAxis = MMVector3Cross(xAxis, zAxis);

            //Create view matrix;
            return Matrix4(xAxis.x, xAxis.y, xAxis.z, -MMVector3Dot(xAxis, eye),
                           yAxis.x, yAxis.y, yAxis.z, -MMVector3Dot(yAxis, eye),
                           -zAxis.x, -zAxis.y, -zAxis.z, MMVector3Dot(zAxis, eye),
                           0, 0, 0, 1);
        }

        /** Returns the transpose of a matrix as a Matrix4
        * \param mat matrix to transpose
        * \return A Matrix4 that is the transpoe of this matrix
        */
        inline Matrix4 _MM_CALLCONV MMMatrixTranspose(const Matrix4& mat)
        {
            Matrix4 transpose;
            transpose.m_rows[0] = mat.m_rows[0];
            transpose.m_rows[1] = mat.m_rows[1];
            transpose.m_rows[2] = mat.m_rows[2];
            transpose.m_rows[3] = mat.m_rows[3];
            _MM_TRANSPOSE4_PS(transpose.m_rows[0], transpose.m_rows[1], transpose.m_rows[2], transpose.m_rows[3]);
            return transpose;
        }

        /** Returns the inverse of this matrix as a Matrix4
        * \param mat matrix to invert
        * \return A Matrix4 that is the inverse of this matrix
        */
        inline Matrix4 _MM_CALLCONV MMMatrixInverse(const Matrix4& mat)
        {

            Matrix4 result;
            __m128 x, y, z, w;
            __m128 temp1, temp2;
            __m128 det;

            //xx, xy, xz, xw
            //yx, yy, yz, yw
            //zx, zy, zz, zw
            //wx, wy, wz, ww

            //calculate cofactor
            //xx,xy
            temp1 = _mm_mul_ps(_mm_shuffle_ps(mat.m_rows[2], mat.m_rows[2], _MM_SHUFFLE(1, 3, 2, 0)),  //row 2 shifted backwards (ignoring 1st value)
                               _mm_shuffle_ps(mat.m_rows[3], mat.m_rows[3], _MM_SHUFFLE(2, 1, 3, 0))); //row 3 shifted forwards (ignoring 1st value)
            temp2 = _mm_mul_ps(_mm_shuffle_ps(mat.m_rows[3], mat.m_rows[3], _MM_SHUFFLE(1, 3, 2, 0)),  //row 3 shifted backwards (ignoring 1st value)
                               _mm_shuffle_ps(mat.m_rows[2], mat.m_rows[2], _MM_SHUFFLE(2, 1, 3, 0))); //row 2 shifted forwards (ignoring 1st value)
                                                                                        //+
            x = _mm_mul_ps(_mm_sub_ps(temp1, temp2), mat.m_rows[1]); //multiply 3 rows together
            x = _mm_add_ps(_mm_shuffle_ps(x, x, _MM_SHUFFLE(3, 2, 1, 1)),
                _mm_add_ps(_mm_shuffle_ps(x, x, _MM_SHUFFLE(1, 3, 2, 2)),
                           _mm_shuffle_ps(x, x, _MM_SHUFFLE(2, 1, 3, 3)))); //add 3 values together into new vector
                                                                     //-
            y = _mm_mul_ps(_mm_sub_ps(temp2, temp1), mat.m_rows[0]); //multiply 3 rows together
            y = _mm_add_ps(_mm_shuffle_ps(y, y, _MM_SHUFFLE(3, 2, 1, 1)),
                _mm_add_ps(_mm_shuffle_ps(y, y, _MM_SHUFFLE(1, 3, 2, 2)),
                           _mm_shuffle_ps(y, y, _MM_SHUFFLE(2, 1, 3, 3)))); //add 3 values together into new vector

                                                                     //xz,xw
            temp1 = _mm_mul_ps(_mm_shuffle_ps(mat.m_rows[0], mat.m_rows[0], _MM_SHUFFLE(1, 3, 2, 0)),  //row 0 shifted backwards (ignoring 1st value)
                               _mm_shuffle_ps(mat.m_rows[1], mat.m_rows[1], _MM_SHUFFLE(2, 1, 3, 0))); //row 1 shifted forwards (ignoring 1st value)
            temp2 = _mm_mul_ps(_mm_shuffle_ps(mat.m_rows[1], mat.m_rows[1], _MM_SHUFFLE(1, 3, 2, 0)),  //row 1 shifted backwards (ignoring 1st value)
                               _mm_shuffle_ps(mat.m_rows[0], mat.m_rows[0], _MM_SHUFFLE(2, 1, 3, 0))); //row 0 shifted forwards (ignoring 1st value)
                                                                                        //+
            z = _mm_mul_ps(_mm_sub_ps(temp1, temp2), mat.m_rows[3]); //multiply 3 rows together
            z = _mm_add_ps(_mm_shuffle_ps(z, z, _MM_SHUFFLE(3, 2, 1, 1)),
                _mm_add_ps(_mm_shuffle_ps(z, z, _MM_SHUFFLE(1, 3, 2, 2)),
                           _mm_shuffle_ps(z, z, _MM_SHUFFLE(2, 1, 3, 3)))); //add 3 values together into new vector
                                                                     //-
            w = _mm_mul_ps(_mm_sub_ps(temp2, temp1), mat.m_rows[2]); //multiply 3 rows together
            w = _mm_add_ps(_mm_shuffle_ps(w, w, _MM_SHUFFLE(3, 2, 1, 1)),
                _mm_add_ps(_mm_shuffle_ps(w, w, _MM_SHUFFLE(1, 3, 2, 2)),
                           _mm_shuffle_ps(w, w, _MM_SHUFFLE(2, 1, 3, 3)))); //add 3 values together into new vector

            result.m_rows[0] = _mm_movelh_ps(_mm_unpacklo_ps(x, y), _mm_unpacklo_ps(z, w));

            //yx,yy
            temp1 = _mm_mul_ps(_mm_shuffle_ps(mat.m_rows[2], mat.m_rows[2], _MM_SHUFFLE(0, 3, 1, 2)),  //row 2 shifted backwards (ignoring 2nd value)
                               _mm_shuffle_ps(mat.m_rows[3], mat.m_rows[3], _MM_SHUFFLE(2, 0, 1, 3))); //row 3 shifted forwards (ignoring 2nd value)
            temp2 = _mm_mul_ps(_mm_shuffle_ps(mat.m_rows[3], mat.m_rows[3], _MM_SHUFFLE(0, 3, 1, 2)),  //row 3 shifted backwards (ignoring 2nd value)
                               _mm_shuffle_ps(mat.m_rows[2], mat.m_rows[2], _MM_SHUFFLE(2, 0, 1, 3))); //row 2 shifted forwards (ignoring 2nd value)
            
            //-
            x = _mm_mul_ps(_mm_sub_ps(temp2, temp1), mat.m_rows[1]); //multiply 3 rows together
            x = _mm_add_ps(_mm_shuffle_ps(x, x, _MM_SHUFFLE(3, 2, 0, 0)),
                _mm_add_ps(_mm_shuffle_ps(x, x, _MM_SHUFFLE(0, 3, 2, 2)),
                           _mm_shuffle_ps(x, x, _MM_SHUFFLE(2, 0, 3, 3)))); //add 3 values together into new vector

            //+
            y = _mm_mul_ps(_mm_sub_ps(temp1, temp2), mat.m_rows[0]); //multiply 3 rows together
            y = _mm_add_ps(_mm_shuffle_ps(y, y, _MM_SHUFFLE(3, 2, 0, 0)),
                _mm_add_ps(_mm_shuffle_ps(y, y, _MM_SHUFFLE(0, 3, 2, 2)),
                           _mm_shuffle_ps(y, y, _MM_SHUFFLE(2, 0, 3, 3)))); //add 3 values together into new vector

            //yz,yw
            temp1 = _mm_mul_ps(_mm_shuffle_ps(mat.m_rows[0], mat.m_rows[0], _MM_SHUFFLE(0, 3, 1, 2)),  //row 0 shifted backwards (ignoring 2nd value)
                               _mm_shuffle_ps(mat.m_rows[1], mat.m_rows[1], _MM_SHUFFLE(2, 0, 1, 3))); //row 1 shifted forwards (ignoring 2nd value)
            temp2 = _mm_mul_ps(_mm_shuffle_ps(mat.m_rows[1], mat.m_rows[1], _MM_SHUFFLE(0, 3, 1, 2)),  //row 1 shifted backwards (ignoring 2nd value)
                               _mm_shuffle_ps(mat.m_rows[0], mat.m_rows[0], _MM_SHUFFLE(2, 0, 1, 3))); //row 0 shifted forwards (ignoring 2nd value)

            //-
            z = _mm_mul_ps(_mm_sub_ps(temp2, temp1), mat.m_rows[3]); //multiply 3 rows together
            z = _mm_add_ps(_mm_shuffle_ps(z, z, _MM_SHUFFLE(3, 2, 0, 0)),
                _mm_add_ps(_mm_shuffle_ps(z, z, _MM_SHUFFLE(0, 3, 2, 2)),
                           _mm_shuffle_ps(z, z, _MM_SHUFFLE(2, 0, 3, 3)))); //add 3 values together into new vector
                                                                     //+
            w = _mm_mul_ps(_mm_sub_ps(temp1, temp2), mat.m_rows[2]); //multiply 3 rows together
            w = _mm_add_ps(_mm_shuffle_ps(w, w, _MM_SHUFFLE(3, 2, 0, 0)),
                _mm_add_ps(_mm_shuffle_ps(w, w, _MM_SHUFFLE(0, 3, 2, 2)),
                           _mm_shuffle_ps(w, w, _MM_SHUFFLE(2, 0, 3, 3)))); //add 3 values together into new vector

            result.m_rows[1] = _mm_movelh_ps(_mm_unpacklo_ps(x, y), _mm_unpacklo_ps(z, w));

            //zx,zy 
            temp1 = _mm_mul_ps(_mm_shuffle_ps(mat.m_rows[2], mat.m_rows[2], _MM_SHUFFLE(0, 2, 3, 1)),  //row 2 shifted backwards (ignoring 3rd value)
                               _mm_shuffle_ps(mat.m_rows[3], mat.m_rows[3], _MM_SHUFFLE(1, 2, 0, 3))); //row 3 shifted forwards (ignoring 3rd value)
            temp2 = _mm_mul_ps(_mm_shuffle_ps(mat.m_rows[3], mat.m_rows[3], _MM_SHUFFLE(0, 2, 3, 1)),  //row 3 shifted backwards (ignoring 3rd value)
                               _mm_shuffle_ps(mat.m_rows[2], mat.m_rows[2], _MM_SHUFFLE(1, 2, 0, 3))); //row 2 shifted forwards (ignoring 3rd value)

            //+
            x = _mm_mul_ps(_mm_sub_ps(temp1, temp2), mat.m_rows[1]); //multiply 3 rows together
            x = _mm_add_ps(_mm_shuffle_ps(x, x, _MM_SHUFFLE(3, 1, 0, 0)),
                _mm_add_ps(_mm_shuffle_ps(x, x, _MM_SHUFFLE(0, 3, 1, 1)),
                           _mm_shuffle_ps(x, x, _MM_SHUFFLE(1, 0, 3, 3)))); //add 3 values together into new vector
                                                                     //-
            y = _mm_mul_ps(_mm_sub_ps(temp2, temp1), mat.m_rows[0]); //multiply 3 rows together
            y = _mm_add_ps(_mm_shuffle_ps(y, y, _MM_SHUFFLE(3, 1, 0, 0)),
                _mm_add_ps(_mm_shuffle_ps(y, y, _MM_SHUFFLE(0, 3, 1, 1)),
                           _mm_shuffle_ps(y, y, _MM_SHUFFLE(1, 0, 3, 3)))); //add 3 values together into new vector

            //zz,zw 
            temp1 = _mm_mul_ps(_mm_shuffle_ps(mat.m_rows[0], mat.m_rows[0], _MM_SHUFFLE(0, 2, 3, 1)),  //row 0 shifted backwards (ignoring 3rd value)
                               _mm_shuffle_ps(mat.m_rows[1], mat.m_rows[1], _MM_SHUFFLE(1, 2, 0, 3))); //row 1 shifted forwards (ignoring 3rd value)
            temp2 = _mm_mul_ps(_mm_shuffle_ps(mat.m_rows[1], mat.m_rows[1], _MM_SHUFFLE(0, 2, 3, 1)),  //row 1 shifted backwards (ignoring 3rd value)
                               _mm_shuffle_ps(mat.m_rows[0], mat.m_rows[0], _MM_SHUFFLE(1, 2, 0, 3))); //row 0 shifted forwards (ignoring 3rd value)

            //+
            z = _mm_mul_ps(_mm_sub_ps(temp1, temp2), mat.m_rows[3]); //multiply 3 rows together
            z = _mm_add_ps(_mm_shuffle_ps(z, z, _MM_SHUFFLE(3, 1, 0, 0)),
                _mm_add_ps(_mm_shuffle_ps(z, z, _MM_SHUFFLE(0, 3, 1, 1)),
                           _mm_shuffle_ps(z, z, _MM_SHUFFLE(1, 0, 3, 3)))); //add 3 values together into new vector

            //-
            w = _mm_mul_ps(_mm_sub_ps(temp2, temp1), mat.m_rows[2]); //multiply 3 rows together
            w = _mm_add_ps(_mm_shuffle_ps(w, w, _MM_SHUFFLE(3, 1, 0, 0)),
                _mm_add_ps(_mm_shuffle_ps(w, w, _MM_SHUFFLE(0, 3, 1, 1)),
                           _mm_shuffle_ps(w, w, _MM_SHUFFLE(1, 0, 3, 3)))); //add 3 values together into new vector

            result.m_rows[2] = _mm_movelh_ps(_mm_unpacklo_ps(x, y), _mm_unpacklo_ps(z, w));

            //wx,wy
            temp1 = _mm_mul_ps(_mm_shuffle_ps(mat.m_rows[2], mat.m_rows[2], _MM_SHUFFLE(3, 0, 2, 1)),  //row 2 shifted backwards (ignoring 4th value)
                               _mm_shuffle_ps(mat.m_rows[3], mat.m_rows[3], _MM_SHUFFLE(3, 1, 0, 2))); //row 3 shifted forwards (ignoring 4th value)
            temp2 = _mm_mul_ps(_mm_shuffle_ps(mat.m_rows[3], mat.m_rows[3], _MM_SHUFFLE(3, 0, 2, 1)),  //row 3 shifted backwards (ignoring 4th value)
                               _mm_shuffle_ps(mat.m_rows[2], mat.m_rows[2], _MM_SHUFFLE(3, 1, 0, 2))); //row 2 shifted forwards (ignoring 4th value)
                                                                                        //-
            x = _mm_mul_ps(_mm_sub_ps(temp2, temp1), mat.m_rows[1]); //multiply 3 rows together
            x = _mm_add_ps(_mm_shuffle_ps(x, x, _MM_SHUFFLE(0, 2, 1, 1)),
                _mm_add_ps(_mm_shuffle_ps(x, x, _MM_SHUFFLE(1, 0, 2, 2)),
                           _mm_shuffle_ps(x, x, _MM_SHUFFLE(2, 1, 0, 0)))); //add 3 values together into new vector

            //+
            y = _mm_mul_ps(_mm_sub_ps(temp1, temp2), mat.m_rows[0]); //multiply 3 rows together
            y = _mm_add_ps(_mm_shuffle_ps(y, y, _MM_SHUFFLE(0, 2, 1, 1)),
                _mm_add_ps(_mm_shuffle_ps(y, y, _MM_SHUFFLE(1, 0, 2, 2)),
                           _mm_shuffle_ps(y, y, _MM_SHUFFLE(2, 1, 0, 0)))); //add 3 values together into new vector

            //wz,ww
            temp1 = _mm_mul_ps(_mm_shuffle_ps(mat.m_rows[0], mat.m_rows[0], _MM_SHUFFLE(3, 0, 2, 1)),  //row 0 shifted backwards (ignoring 4th value)
                               _mm_shuffle_ps(mat.m_rows[1], mat.m_rows[1], _MM_SHUFFLE(3, 1, 0, 2))); //row 1 shifted forwards (ignoring 4th value)
            temp2 = _mm_mul_ps(_mm_shuffle_ps(mat.m_rows[1], mat.m_rows[1], _MM_SHUFFLE(3, 0, 2, 1)),  //row 1 shifted backwards (ignoring 4th value)
                               _mm_shuffle_ps(mat.m_rows[0], mat.m_rows[0], _MM_SHUFFLE(3, 1, 0, 2))); //row 0 shifted forwards (ignoring 4th value)

            //-
            z = _mm_mul_ps(_mm_sub_ps(temp2, temp1), mat.m_rows[3]); //multiply 3 rows together
            z = _mm_add_ps(_mm_shuffle_ps(z, z, _MM_SHUFFLE(0, 2, 1, 1)),
                _mm_add_ps(_mm_shuffle_ps(z, z, _MM_SHUFFLE(1, 0, 2, 2)),
                           _mm_shuffle_ps(z, z, _MM_SHUFFLE(2, 1, 0, 0)))); //add 3 values together into new vector

            //+
            w = _mm_mul_ps(_mm_sub_ps(temp1, temp2), mat.m_rows[2]); //multiply 3 rows together
            w = _mm_add_ps(_mm_shuffle_ps(w, w, _MM_SHUFFLE(0, 2, 1, 1)),
                _mm_add_ps(_mm_shuffle_ps(w, w, _MM_SHUFFLE(1, 0, 2, 2)),
                           _mm_shuffle_ps(w, w, _MM_SHUFFLE(2, 1, 0, 0)))); //add 3 values together into new vector

            result.m_rows[3] = _mm_movelh_ps(_mm_unpacklo_ps(x, y), _mm_unpacklo_ps(z, w));

            //calculate determinant usinfg first element in each row

            det = _mm_movelh_ps(_mm_unpacklo_ps(result.m_rows[0], result.m_rows[1]), _mm_unpacklo_ps(result.m_rows[2], result.m_rows[3]));
            det = _mm_mul_ps(det, mat.m_rows[0]);
            det = _mm_add_ps(det, _mm_shuffle_ps(det, det, _MM_SHUFFLE(2, 3, 0, 1)));
            det = _mm_add_ps(det, _mm_shuffle_ps(det, det, _MM_SHUFFLE(0, 1, 2, 3)));

            det = _mm_rcp_ss(det);
            det = _mm_shuffle_ps(det, det, _MM_SHUFFLE(0, 0, 0, 0));

            result.m_rows[0] = _mm_mul_ps(result.m_rows[0], det);
            result.m_rows[1] = _mm_mul_ps(result.m_rows[1], det);
            result.m_rows[2] = _mm_mul_ps(result.m_rows[2], det);
            result.m_rows[3] = _mm_mul_ps(result.m_rows[3], det);

            return result;
        }

        //Creates a 4x4 identity matrix
        inline Matrix4::Matrix4()
        {
            __m128 v = _mm_set_ss(1);
            this->m_rows[0] = v;
            this->m_rows[1] = _mm_shuffle_ps(v, v, _MM_SHUFFLE(2, 2, 0, 2));
            this->m_rows[2] = _mm_shuffle_ps(v, v, _MM_SHUFFLE(2, 0, 2, 2));
            this->m_rows[3] = _mm_shuffle_ps(v, v, _MM_SHUFFLE(0, 2, 2, 2));
        }

        //Creates a 4x4 matrix from an array of 16 values
        inline Matrix4::Matrix4(float rawArray[])
        {
            this->m_rows[0] = _mm_load_ps(rawArray);
            this->m_rows[1] = _mm_load_ps(rawArray + 4);
            this->m_rows[2] = _mm_load_ps(rawArray + 8);
            this->m_rows[3] = _mm_load_ps(rawArray + 12);
        }

        //Creates a 4x4 matrix from 16 given values (it's recommended to send an array instead)
        inline Matrix4::Matrix4(float xx, float xy, float xz, float xw,
                                float yx, float yy, float yz, float yw,
                                float zx, float zy, float zz, float zw,
                                float wx, float wy, float wz, float ww)
        {
            __m128 xx0 = _mm_load_ss(&xx);
            __m128 xy0 = _mm_load_ss(&xy);
            __m128 xz0 = _mm_load_ss(&xz);
            __m128 xw0 = _mm_load_ss(&xw);
            __m128 yx0 = _mm_load_ss(&yx);
            __m128 yy0 = _mm_load_ss(&yy);
            __m128 yz0 = _mm_load_ss(&yz);
            __m128 yw0 = _mm_load_ss(&yw);
            __m128 zx0 = _mm_load_ss(&zx);
            __m128 zy0 = _mm_load_ss(&zy);
            __m128 zz0 = _mm_load_ss(&zz);
            __m128 zw0 = _mm_load_ss(&zw);
            __m128 wx0 = _mm_load_ss(&wx);
            __m128 wy0 = _mm_load_ss(&wy);
            __m128 wz0 = _mm_load_ss(&wz);
            __m128 ww0 = _mm_load_ss(&ww);

            this->m_rows[0] = _mm_movelh_ps(_mm_unpacklo_ps(xx0, xy0), _mm_unpacklo_ps(xz0, xw0));
            this->m_rows[1] = _mm_movelh_ps(_mm_unpacklo_ps(yx0, yy0), _mm_unpacklo_ps(yz0, yw0));
            this->m_rows[2] = _mm_movelh_ps(_mm_unpacklo_ps(zx0, zy0), _mm_unpacklo_ps(zz0, zw0));
            this->m_rows[3] = _mm_movelh_ps(_mm_unpacklo_ps(wx0, wy0), _mm_unpacklo_ps(wz0, ww0));
        }

        /** Creates a 4x4 matrix from 4 given Vector3s
        * The resulting matrix fills in a few values so that it will match this
        * layout:
        * a1, a2, a3, 0
        * b1, b2, b3, 0
        * c1, c2, c3, 0
        * d1, d2, d3, 1
        */
        inline Matrix4::Matrix4(const Vector3& a, const Vector3& b, const Vector3& c, const Vector3& d)
        {
            float one = 1;
            __m128 o = _mm_load_ss(&one);
            __m128 z = _mm_setzero_ps();

            __m128 xx = _mm_load_ss(&a[0]);
            __m128 xy = _mm_load_ss(&a[1]);
            __m128 xz = _mm_load_ss(&a[2]);
            __m128 yx = _mm_load_ss(&b[0]);
            __m128 yy = _mm_load_ss(&b[1]);
            __m128 yz = _mm_load_ss(&b[2]);
            __m128 zx = _mm_load_ss(&c[0]);
            __m128 zy = _mm_load_ss(&c[1]);
            __m128 zz = _mm_load_ss(&c[2]);
            __m128 wx = _mm_load_ss(&d[0]);
            __m128 wy = _mm_load_ss(&d[1]);
            __m128 wz = _mm_load_ss(&d[2]);

            this->m_rows[0] = _mm_movelh_ps(_mm_unpacklo_ps(xx, xy), _mm_unpacklo_ps(xz, z));
            this->m_rows[1] = _mm_movelh_ps(_mm_unpacklo_ps(yx, yy), _mm_unpacklo_ps(yz, z));
            this->m_rows[2] = _mm_movelh_ps(_mm_unpacklo_ps(zx, zy), _mm_unpacklo_ps(zz, z));
            this->m_rows[3] = _mm_movelh_ps(_mm_unpacklo_ps(wx, wy), _mm_unpacklo_ps(wz, o));
        }

        /** Creates a 4x4 matrix from 4 given Vector4s
        * The resulting matrix fills in a few values so that it will match this
        * layout:
        * a1, a2, a3, a4
        * b1, b2, b3, b4
        * c1, c2, c3, c4
        * d1, d2, d3, d4
        */
        inline Matrix4::Matrix4(const Vector4& a, const Vector4& b, const Vector4& c, const Vector4& d)
        {
            this->m_rows[0] = a.m_vector;
            this->m_rows[1] = b.m_vector;
            this->m_rows[2] = c.m_vector;
            this->m_rows[3] = d.m_vector;
        }

        /** Multiplies this Matrix4 by another given Matrix4 and returns the
        * resulting matrix
        * \param mat The other Matrix4 to multiply into this one
        * \return The product of this matrix * mat as a Matrix4
        */
        inline Matrix4 Matrix4::operator*(const Matrix4& m) const
        {
            Matrix4 result;

            //transpose the other matrix to get it as columns
            Matrix4 other = MMMatrixTranspose(m);

            //get the dot product of each row/column and put them into an array
            //rows
            for (int i = 0; i < 4; i++)
            {
                //columns
                __m128 a = _mm_mul_ps(m_rows[i], other.m_rows[0]);
                a = _mm_add_ps(a, _mm_shuffle_ps(a, a, _MM_SHUFFLE(0, 1, 2, 3)));
                a = _mm_add_ps(a, _mm_shuffle_ps(a, a, _MM_SHUFFLE(2, 3, 0, 1)));

                __m128 b = _mm_mul_ps(m_rows[i], other.m_rows[1]);
                b = _mm_add_ps(b, _mm_shuffle_ps(b, b, _MM_SHUFFLE(0, 1, 2, 3)));
                b = _mm_add_ps(b, _mm_shuffle_ps(b, b, _MM_SHUFFLE(2, 3, 0, 1)));

                __m128 c = _mm_mul_ps(m_rows[i], other.m_rows[2]);
                c = _mm_add_ps(c, _mm_shuffle_ps(c, c, _MM_SHUFFLE(0, 1, 2, 3)));
                c = _mm_add_ps(c, _mm_shuffle_ps(c, c, _MM_SHUFFLE(2, 3, 0, 1)));

                __m128 d = _mm_mul_ps(m_rows[i], other.m_rows[3]);
                d = _mm_add_ps(d, _mm_shuffle_ps(d, d, _MM_SHUFFLE(0, 1, 2, 3)));
                d = _mm_add_ps(d, _mm_shuffle_ps(d, d, _MM_SHUFFLE(2, 3, 0, 1)));

                //combine into one m128 and store in the new matrix
                result.m_rows[i] = _mm_movelh_ps(_mm_unpacklo_ps(a, b), _mm_unpacklo_ps(c, d));
            }

            return result; //newMat;
        }

        ///** Multiplies this Matrix4 by a given Vector3 and returns the
        //* resulting Vector3
        //* \param vec The Vector3 to multiply into this matrix
        //* \return The product of this matrix * vec as a Vector3
        //*/
        //inline Vector3 Matrix4::operator*(const Vector3& vec) const
        //{
        //    Vector3 result;

        //    __m128 x = _mm_mul_ps(m_rows[0], vec.m_vector);
        //    x = _mm_add_ps(x, _mm_shuffle_ps(x, x, _MM_SHUFFLE(0, 1, 2, 3)));
        //    x = _mm_add_ps(x, _mm_shuffle_ps(x, x, _MM_SHUFFLE(2, 3, 0, 1)));

        //    __m128 y = _mm_mul_ps(m_rows[1], vec.m_vector);
        //    y = _mm_add_ps(y, _mm_shuffle_ps(y, y, _MM_SHUFFLE(0, 1, 2, 3)));
        //    y = _mm_add_ps(y, _mm_shuffle_ps(y, y, _MM_SHUFFLE(2, 3, 0, 1)));

        //    __m128 z = _mm_mul_ps(m_rows[2], vec.m_vector);
        //    z = _mm_add_ps(z, _mm_shuffle_ps(z, z, _MM_SHUFFLE(0, 1, 2, 3)));
        //    z = _mm_add_ps(z, _mm_shuffle_ps(z, z, _MM_SHUFFLE(2, 3, 0, 1)));

        //    __m128 w = _mm_setzero_ps();

        //    result.m_vector = _mm_movelh_ps(_mm_unpacklo_ps(x, y), _mm_unpacklo_ps(z, w));

        //    return result;
        //}

        /** Multiplies this Matrix4 by a given Vector4 and returns the
        * resulting Vector4
        * \param vec The Vector4 to multiply into this matrix
        * \return The product of this matrix * vec as a Vector4
        */
        inline Vector4 Matrix4::operator*(const Vector4& vec) const
        {
            Vector4 result;

            __m128 x = _mm_mul_ps(m_rows[0], vec.m_vector);
            x = _mm_add_ps(x, _mm_shuffle_ps(x, x, _MM_SHUFFLE(0, 1, 2, 3)));
            x = _mm_add_ps(x, _mm_shuffle_ps(x, x, _MM_SHUFFLE(2, 3, 0, 1)));

            __m128 y = _mm_mul_ps(m_rows[1], vec.m_vector);
            y = _mm_add_ps(y, _mm_shuffle_ps(y, y, _MM_SHUFFLE(0, 1, 2, 3)));
            y = _mm_add_ps(y, _mm_shuffle_ps(y, y, _MM_SHUFFLE(2, 3, 0, 1)));

            __m128 z = _mm_mul_ps(m_rows[2], vec.m_vector);
            z = _mm_add_ps(z, _mm_shuffle_ps(z, z, _MM_SHUFFLE(0, 1, 2, 3)));
            z = _mm_add_ps(z, _mm_shuffle_ps(z, z, _MM_SHUFFLE(2, 3, 0, 1)));

            __m128 w = _mm_mul_ps(m_rows[3], vec.m_vector);
            w = _mm_add_ps(w, _mm_shuffle_ps(w, w, _MM_SHUFFLE(0, 1, 2, 3)));
            w = _mm_add_ps(w, _mm_shuffle_ps(w, w, _MM_SHUFFLE(2, 3, 0, 1)));

            result.m_vector = _mm_movelh_ps(_mm_unpacklo_ps(x, y), _mm_unpacklo_ps(z, w));

            return result;
        }


        inline float* Matrix4::operator[] (int row)
        {
            return data + sizeof(float) * row;
        }

        /** An outstream operator for a Matrix4 to interace with an ostream
        * \param output The ostream to output to
        * \param h The Matrix4 to interface with the ostream
        */
        inline std::ostream& operator<<(std::ostream& output, Matrix4& m)
        {
            output << m.xx << " " << m.xy << " " << m.xz << " " << m.xw << std::endl
                   << m.yx << " " << m.yy << " " << m.yz << " " << m.yw << std::endl
                   << m.zx << " " << m.zy << " " << m.zz << " " << m.zw << std::endl
                   << m.wx << " " << m.wy << " " << m.wz << " " << m.ww;

            return output;
        }

        /** An insertion operator for a Matrix4 to interace with an ostream
        * \param output The ostream to output to
        * \param h The Matrix4 to interface with the ostream
        */
        inline std::istream& operator>>(std::istream& input, Matrix4& m)
        {
            input >> m.xx >> m.xy >> m.xz >> m.xw
                  >> m.yx >> m.yy >> m.yz >> m.yw
                  >> m.zx >> m.zy >> m.zz >> m.zw
                  >> m.wx >> m.wy >> m.wz >> m.ww;

            return input;
        }

    }
}
