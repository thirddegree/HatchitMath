#include <cmath>

/////////////////////////////////////////////////////////////
// Matrix4 Implementation
/////////////////////////////////////////////////////////////

/*
*	Statics
*/

/** Generates an orthographic projection from the given values
* \param left The lefthand bound
* \param right The righthand bound
* \param top The topmost bound
* \param _near The near plane
* \param _far The far plane
* \return The resulting orthographic projection in a Matrix4
*/
inline MMMATRIX _MM_CALLCONV MMMatrixOrthoProj(float left, float right, float bottom, float top, float znear, float zfar)
{
	float a = 2 / (right - left);
	float b = 2 / (top - bottom);
	float c = -2 / (zfar - znear);
	float d = -1 * ((right + left) / (right - left));
	float e = -1 * ((top + bottom) / (top - bottom));
	float f = -1 * ((zfar + znear) / (zfar - znear));

	return MMMATRIX(a, 0, 0, 0,
		0, b, 0, 0,
		0, 0, c, 0,
		d, e, f, 1);
}

/** Generates a perspective projection from the given values
* \param fov The field of view
* \param aspect The aspect ratio
* \param near The _near plane
* \param far The _far plane
* \return The resulting perspective projection in a Matrix4
*/
inline Hatchit::Math::Matrix4 _MM_CALLCONV MMMatrixPerspProj(float fov, float aspect, float znear, float zfar)
{
	//thanks to https://stackoverflow.com/questions/18404890/how-to-build-perspective-projection-matrix-no-api
	float depth = zfar - znear;
	float m_vector = -(zfar + znear) / depth;
	float qn = -2 * (zfar * znear) / depth;

	float h = 1 / tanf(0.5f * fov);
	float w = h / aspect;

	return MMMATRIX(w, 0, 0, 0,
		0, h, 0, 0,
		0, 0, m_vector, -1,
		0, 0, qn, 0);
}

/** Generates a view matrix from the given values
* \param lookAt The point for the camera to look at
* \param center The point that the camera is located
* \param up The vector representing which way is up for this camera
* \return The resulting view matrix in a Matrix4
*/
inline Hatchit::Math::Matrix4 _MM_CALLCONV MMMatrixLookAt(Hatchit::Math::Vector3 lookAt, Hatchit::Math::Vector3 center, Hatchit::Math::Vector3 up)
{
	//Calculate axes
	MMVECTOR3 zAxis = Hatchit::Math::MMVector3Normalize((lookAt - center));
    MMVECTOR3 xAxis = Hatchit::Math::MMVector3Normalize(Hatchit::Math::MMVector3Cross(up, zAxis));
    MMVECTOR3 yAxis = Hatchit::Math::MMVector3Cross(zAxis, xAxis);

	//Create view matrix;
	return MMMATRIX(xAxis.x, yAxis.x, zAxis.x, 0,
		           xAxis.y, yAxis.y, zAxis.y, 0,
		           xAxis.z, yAxis.z, zAxis.z, 0,
		MMVector3Dot(xAxis * -1, lookAt),
        MMVector3Dot(yAxis * -1, lookAt),
        MMVector3Dot(zAxis * -1, lookAt),
		1);
}

/** Returns the transpose of a matrix as a Matrix4
* \param mat matrix to transpose
* \return A Matrix4 that is the transpoe of this matrix
*/
inline Hatchit::Math::Matrix4 _MM_CALLCONV MMMatrixTranspose(const MMMATRIX& mat)
{
	/*matrix shuffling to transpose is done in 3 steps
	* |01,02,03,04|    |01,02,05,06|    |01,05,02,06|    |01,05,09,13|
	* |05,06,07,08| -> |03,04,07,08| -> |03,07,04,08| -> |02,06,10,14|
	* |09,10,11,12|    |09,10,13,14|    |09,13,10,14|    |03,07,11,15|
	* |13,14,15,16|    |11,12,15,16|    |11,15,12,16|    |04,08,12,16|
	*/
    MMMATRIX transpose;
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
inline Hatchit::Math::Matrix4 _MM_CALLCONV MMMatrixInverse(const MMMATRIX& mat)
{

	MMMATRIX result;
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

	//calculate determinant using first element in each row

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


/*
*	Constructors
*/

inline Hatchit::Math::Matrix4::Matrix4()
{
	float zero = 0;
	float one = 1;
	__m128 o = _mm_load_ss(&one);
	__m128 z = _mm_load_ss(&zero);
	this->m_rows[0] = o;
	this->m_rows[1] = _mm_movelh_ps(_mm_unpacklo_ps(z, o), _mm_unpacklo_ps(z, z));
	this->m_rows[2] = _mm_movelh_ps(_mm_unpacklo_ps(z, z), _mm_unpacklo_ps(o, z));
	this->m_rows[3] = _mm_movelh_ps(_mm_unpacklo_ps(z, z), _mm_unpacklo_ps(z, o));
}

inline Hatchit::Math::Matrix4::Matrix4(float rawArray[])
{
	__m128 xx = _mm_load_ss(&rawArray[0]);
	__m128 xy = _mm_load_ss(&rawArray[1]);
	__m128 xz = _mm_load_ss(&rawArray[2]);
	__m128 xw = _mm_load_ss(&rawArray[3]);
	__m128 yx = _mm_load_ss(&rawArray[4]);
	__m128 yy = _mm_load_ss(&rawArray[5]);
	__m128 yz = _mm_load_ss(&rawArray[6]);
	__m128 yw = _mm_load_ss(&rawArray[7]);
	__m128 zx = _mm_load_ss(&rawArray[8]);
	__m128 zy = _mm_load_ss(&rawArray[9]);
	__m128 zz = _mm_load_ss(&rawArray[10]);
	__m128 zw = _mm_load_ss(&rawArray[11]);
	__m128 wx = _mm_load_ss(&rawArray[12]);
	__m128 wy = _mm_load_ss(&rawArray[13]);
	__m128 wz = _mm_load_ss(&rawArray[14]);
	__m128 ww = _mm_load_ss(&rawArray[15]);

	this->m_rows[0] = _mm_movelh_ps(_mm_unpacklo_ps(xx, xy), _mm_unpacklo_ps(xz, xw));
	this->m_rows[1] = _mm_movelh_ps(_mm_unpacklo_ps(yx, yy), _mm_unpacklo_ps(yz, yw));
	this->m_rows[2] = _mm_movelh_ps(_mm_unpacklo_ps(zx, zy), _mm_unpacklo_ps(zz, zw));
	this->m_rows[3] = _mm_movelh_ps(_mm_unpacklo_ps(wx, wy), _mm_unpacklo_ps(wz, ww));
}

inline Hatchit::Math::Matrix4::Matrix4(float xx, float xy, float xz, float xw,
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

Hatchit::Math::Matrix4::Matrix4(Vector3 a,
	Vector3 b,
	Vector3 c,
	Vector3 d)
{
	float zero = 0;
	float one = 1;
	__m128 o = _mm_load_ss(&one);
	__m128 z = _mm_load_ss(&zero);

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

	this->m_rows[0] = _mm_movelh_ps(_mm_unpacklo_ps(xx, xy), _mm_unpacklo_ps(xz, o));
	this->m_rows[1] = _mm_movelh_ps(_mm_unpacklo_ps(yx, yy), _mm_unpacklo_ps(yz, o));
	this->m_rows[2] = _mm_movelh_ps(_mm_unpacklo_ps(zx, zy), _mm_unpacklo_ps(zz, o));
	this->m_rows[3] = _mm_movelh_ps(_mm_unpacklo_ps(wx, wy), _mm_unpacklo_ps(wz, z));
}

Hatchit::Math::Matrix4::Matrix4(Vector4 a,
	Vector4 b,
	Vector4 c,
	Vector4 d)
{
	__m128 xx = _mm_load_ss(&a[0]);
	__m128 xy = _mm_load_ss(&a[1]);
	__m128 xz = _mm_load_ss(&a[2]);
	__m128 xw = _mm_load_ss(&a[3]);
	__m128 yx = _mm_load_ss(&b[0]);
	__m128 yy = _mm_load_ss(&b[1]);
	__m128 yz = _mm_load_ss(&b[2]);
	__m128 yw = _mm_load_ss(&b[3]);
	__m128 zx = _mm_load_ss(&c[0]);
	__m128 zy = _mm_load_ss(&c[1]);
	__m128 zz = _mm_load_ss(&c[2]);
	__m128 zw = _mm_load_ss(&c[3]);
	__m128 wx = _mm_load_ss(&d[0]);
	__m128 wy = _mm_load_ss(&d[1]);
	__m128 wz = _mm_load_ss(&d[2]);
	__m128 ww = _mm_load_ss(&d[3]);

	this->m_rows[0] = _mm_movelh_ps(_mm_unpacklo_ps(xx, xy), _mm_unpacklo_ps(xz, xw));
	this->m_rows[1] = _mm_movelh_ps(_mm_unpacklo_ps(yx, yy), _mm_unpacklo_ps(yz, yw));
	this->m_rows[2] = _mm_movelh_ps(_mm_unpacklo_ps(zx, zy), _mm_unpacklo_ps(zz, zw));
	this->m_rows[3] = _mm_movelh_ps(_mm_unpacklo_ps(wx, wy), _mm_unpacklo_ps(wz, ww));
}

/*
Accessors and Mutators
*/

inline const float* const Hatchit::Math::Matrix4::getAsArray() const
{
	static _MM_ALIGN16 float mat_array[16];

	_mm_store_ps(mat_array, m_rows[0]);
	_mm_store_ps(mat_array + 4, m_rows[1]);
	_mm_store_ps(mat_array + 8, m_rows[2]);
	_mm_store_ps(mat_array + 12, m_rows[3]);

	return mat_array;
}

/*
Operators
*/


inline Matrix4 Hatchit::Math::Matrix4::operator*(const Matrix4 m)
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

inline Vector3 Hatchit::Math::Matrix4::operator*(Vector3 vec)
{
	Vector3 result;

	__m128 x = _mm_mul_ps(m_rows[0], vec.m_vector);
	x = _mm_add_ps(x, _mm_shuffle_ps(x, x, _MM_SHUFFLE(0, 1, 2, 3)));
	x = _mm_add_ps(x, _mm_shuffle_ps(x, x, _MM_SHUFFLE(2, 3, 0, 1)));

	__m128 y = _mm_mul_ps(m_rows[1], vec.m_vector);
	y = _mm_add_ps(y, _mm_shuffle_ps(y, y, _MM_SHUFFLE(0, 1, 2, 3)));
	y = _mm_add_ps(y, _mm_shuffle_ps(y, y, _MM_SHUFFLE(2, 3, 0, 1)));

	__m128 z = _mm_mul_ps(m_rows[2], vec.m_vector);
	z = _mm_add_ps(z, _mm_shuffle_ps(z, z, _MM_SHUFFLE(0, 1, 2, 3)));
	z = _mm_add_ps(z, _mm_shuffle_ps(z, z, _MM_SHUFFLE(2, 3, 0, 1)));

	__m128 w = _mm_load_ss(0);

	result.m_vector = _mm_movelh_ps(_mm_unpacklo_ps(x, y), _mm_unpacklo_ps(z, w));

	return result;
}

inline Vector4 Hatchit::Math::Matrix4::operator*(Vector4 vec)
{
	Vector3 result;

	__m128 x = _mm_mul_ps(m_rows[0], vec.m_vector);
	x = _mm_add_ps(x, _mm_shuffle_ps(x, x, _MM_SHUFFLE(0, 1, 2, 3)));
	x = _mm_add_ps(x, _mm_shuffle_ps(x, x, _MM_SHUFFLE(2, 3, 0, 1)));

	__m128 y = _mm_mul_ps(m_rows[1], vec.m_vector);
	y = _mm_add_ps(y, _mm_shuffle_ps(y, y, _MM_SHUFFLE(0, 1, 2, 3)));
	y = _mm_add_ps(y, _mm_shuffle_ps(y, y, _MM_SHUFFLE(2, 3, 0, 1)));

	__m128 z = _mm_mul_ps(m_rows[2], vec.m_vector);
	z = _mm_add_ps(z, _mm_shuffle_ps(z, z, _MM_SHUFFLE(0, 1, 2, 3)));
	z = _mm_add_ps(z, _mm_shuffle_ps(z, z, _MM_SHUFFLE(2, 3, 0, 1)));

	__m128 w = _mm_mul_ps(m_rows[2], vec.m_vector);
	w = _mm_add_ps(w, _mm_shuffle_ps(w, w, _MM_SHUFFLE(0, 1, 2, 3)));
	w = _mm_add_ps(w, _mm_shuffle_ps(w, w, _MM_SHUFFLE(2, 3, 0, 1)));

	result.m_vector = _mm_movelh_ps(_mm_unpacklo_ps(x, y), _mm_unpacklo_ps(z, w));

	return result;
}

//Extraction
inline std::ostream& operator<<(std::ostream& output, Hatchit::Math::Matrix4& m)
{
	output << m.xx << " " << m.xy << " " << m.xz << " " << m.xw << std::endl
		<< m.yx << " " << m.yy << " " << m.yz << " " << m.yw << std::endl
		<< m.zx << " " << m.zy << " " << m.zz << " " << m.zw << std::endl
		<< m.wx << " " << m.zw << " " << m.wz << " " << m.ww;
	return output;
}

//Insertion
inline std::istream& operator>>(std::istream& input, Hatchit::Math::Matrix4& m)
{
	float	xx, xy, xz, xw,
		yx, yy, yz, yw,
		zx, zy, zz, zw,
		wx, wy, wz, ww;

	input >> xx >> xy >> xz >> xw
		>> yx >> yy >> yz >> yw
		>> zx >> zy >> zz >> zw
		>> wx >> wy >> wz >> ww;

	m = Matrix4(xx, xy, xz, xw,
		yx, yy, yz, yw,
		zx, zy, zz, zw,
		wx, wy, wz, ww);

	return input;
}

/** Generates an orthographic projection from the given values
* \param left The lefthand bound
* \param right The righthand bound
* \param bottom the bottommost bound
* \param top The topmost bound
* \param znear The near plane
* \param zfar The far plane
* \return The resulting orthographic projection in a Matrix4
*/
//inline Matrix4 MMMatrixOrthoProj(float left, float right, float bottom, float top, float znear, float zfar)
//{
//	float a = 2 / (right - left);
//	float b = 2 / (top - bottom);
//	float c = -2 / (zfar - znear);
//	float d = -1 * ((right + left) / (right - left));
//	float e = -1 * ((top + bottom) / (top - bottom));
//	float f = -1 * ((zfar + znear) / (zfar - znear));
//
//	return Matrix4(a, 0, 0, 0,
//		0, b, 0, 0,
//		0, 0, c, 0,
//		d, e, f, 1);
//}

/** Generates a perspective projection from the given values
* \param fov The field of view
* \param aspect The aspect ratio
* \param znear The near plane
* \param zfar The far plane
* \return The resulting perspective projection in a Matrix4
*/
//inline Matrix4 MMMatrixPerspProj(float fov, float aspect, float znear, float zfar)
//{
//	//thanks to https://stackoverflow.com/questions/18404890/how-to-build-perspective-projection-matrix-no-api
//	float depth = zfar - znear;
//	float q = -(zfar + znear) / depth;
//	float qn = -2 * (zfar * znear) / depth;
//
//	float h = 1 / tanf(0.5f * fov);
//	float w = h / aspect;
//
//	return Matrix4(w, 0, 0, 0,
//		0, h, 0, 0,
//		0, 0, q, -1,
//		0, 0, qn, 0);
//}

/** Generates a view matrix from the given values
* \param lookAt The point for the camera to look at
* \param center The point that the camera is located
* \param up The vector representing which way is up for this camera
* \return The resulting view matrix in a Matrix4
*/
//inline Matrix4 MMMatrixLookAt(__m128 lookAt, __m128 center, __m128 up)
//{
//	//Calculate axes
//	Vector3 zAxis = Vector3::Normalize((lookAt - center));
//	Vector3 xAxis = Vector3::Normalize(Vector3::Cross(up, zAxis));
//	Vector3 yAxis = Vector3::Cross(zAxis, xAxis);
//
//	//Create view matrix;
//	return Matrix4(xAxis.getX(), yAxis.getX(), zAxis.getX(), 0,
//		xAxis.getY(), yAxis.getY(), zAxis.getY(), 0,
//		xAxis.getZ(), yAxis.getZ(), zAxis.getZ(), 0,
//		Vector3::Dot(xAxis * -1, lookAt),
//		Vector3::Dot(yAxis * -1, lookAt),
//		Vector3::Dot(zAxis * -1, lookAt),
//		1);
//}
