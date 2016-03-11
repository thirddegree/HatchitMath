/**
**    Hatchit Engine
**    Copyright(c) 2015 Third-Degree
**
**    GNU Lesser General Public License
**    This file may be used under the terms of the GNU Lesser
**    General Public License version 3 as published by the Free
**    Software Foundation and appearing in the file LICENSE.LGPLv3 included
**    in the packaging of this file. Please review the following information
**    to ensure the GNU Lesser General Public License requirements
**    will be met: https://www.gnu.org/licenses/lgpl.html
**
**/

#include <gtest/gtest.h>
#include "ht_math.h"
#include <cfloat>
#include <iostream>

using namespace Hatchit;
using namespace Math;

TEST(Vector4, DefaultConstructorFillsZeros)
{
    Vector4 vector;
    EXPECT_FLOAT_EQ(vector.x, 0.f);
	EXPECT_FLOAT_EQ(vector.y, 0.f);
	EXPECT_FLOAT_EQ(vector.z, 0.f);
	EXPECT_FLOAT_EQ(vector.w, 0.f);
}

TEST(Vector4, SingleParameterConstructor) {
	Vector4 vector(5.f);
	EXPECT_FLOAT_EQ(vector.x, 5.f);
	EXPECT_FLOAT_EQ(vector.y, 5.f);
	EXPECT_FLOAT_EQ(vector.z, 5.f);
	EXPECT_FLOAT_EQ(vector.w, 5.f);
}

TEST(Vector4, ParamaterizedConstructor) {
    Vector4 vector(5.f,4.f,3.f,2.f);
    EXPECT_FLOAT_EQ(vector.x, 5.f);
    EXPECT_FLOAT_EQ(vector.y, 4.f);
    EXPECT_FLOAT_EQ(vector.z, 3.f);
    EXPECT_FLOAT_EQ(vector.w, 2.f);
}

TEST(Vector4, Vector2Constructor) {
	Vector4 vector(Vector2(5.f, 4.f), 3.f, 2.f);
	EXPECT_FLOAT_EQ(vector.x, 5.f);
	EXPECT_FLOAT_EQ(vector.y, 4.f);
	EXPECT_FLOAT_EQ(vector.z, 3.f);
	EXPECT_FLOAT_EQ(vector.w, 2.f);
}

TEST(Vector4, Vector3Constructor) {
	Vector4 vector(Vector3(5.f, 4.f, 3.f), 2.f);
	EXPECT_FLOAT_EQ(vector.x, 5.f);
	EXPECT_FLOAT_EQ(vector.y, 4.f);
	EXPECT_FLOAT_EQ(vector.z, 3.f);
	EXPECT_FLOAT_EQ(vector.w, 2.f);
}
TEST(Vector4, CopyConstructor) {
	Vector4 vector(Vector4(5.f, 4.f, 3.f, 2.f));
	EXPECT_FLOAT_EQ(vector.x, 5.f);
	EXPECT_FLOAT_EQ(vector.y, 4.f);
	EXPECT_FLOAT_EQ(vector.z, 3.f);
	EXPECT_FLOAT_EQ(vector.w, 2.f);
}

TEST(Vector4, SettingElementValues)
{
	Vector4 vector(3.f, 4.f, 5.f, 6.f);
	vector.x = 6.f;
	vector.y = 7.f;
	vector.z = 8.f;
	vector.w = 9.f;

	EXPECT_FLOAT_EQ(vector.x, 6.f);
	EXPECT_FLOAT_EQ(vector.y, 7.f);
	EXPECT_FLOAT_EQ(vector.z, 8.f);
	EXPECT_FLOAT_EQ(vector.w, 9.f);
}


TEST(Vector4, FloatAdditionOperator)
{
	Vector4 vector1(1.f, 2.f, 3.f, 4.f);

	Vector4 result = vector1 + 3.f;

	EXPECT_FLOAT_EQ(result.x, 4.f);
	EXPECT_FLOAT_EQ(result.y, 5.f);
	EXPECT_FLOAT_EQ(result.z, 6.f);
	EXPECT_FLOAT_EQ(result.w, 7.f);
}

TEST(Vector4, FloatAdditionAssignmentOperator)
{
	Vector4 vector1(1.f, 2.f, 3.f, 4.f);

	vector1 += 3.f;

	EXPECT_FLOAT_EQ(vector1.x, 4.f);
	EXPECT_FLOAT_EQ(vector1.y, 5.f);
	EXPECT_FLOAT_EQ(vector1.z, 6.f);
	EXPECT_FLOAT_EQ(vector1.w, 7.f);
}

TEST(Vector4, FloatSubtractionOperator)
{
	Vector4 vector1(1.f, 2.f, 3.f, 4.f);

	Vector4 result = vector1 - 3.f;

	EXPECT_FLOAT_EQ(result.x, -2.f);
	EXPECT_FLOAT_EQ(result.y, -1.f);
	EXPECT_FLOAT_EQ(result.z, 0.f);
	EXPECT_FLOAT_EQ(result.w, 1.f);
}

TEST(Vector4, FloatSubtractionAssignmentOperator)
{
	Vector4 vector1(1.f, 2.f, 3.f, 4.f);

	vector1 -= 3.f;

	EXPECT_FLOAT_EQ(vector1.x, -2.f);
	EXPECT_FLOAT_EQ(vector1.y, -1.f);
	EXPECT_FLOAT_EQ(vector1.z, 0.f);
	EXPECT_FLOAT_EQ(vector1.w, 1.f);
}

TEST(Vector4, FloatMultiplicationOperator)
{
	Vector4 vector1(1.f, 2.f, 3.f, 4.f);

	Vector4 result = vector1 * 3.f;

	EXPECT_FLOAT_EQ(result.x, 3.f);
	EXPECT_FLOAT_EQ(result.y, 6.f);
	EXPECT_FLOAT_EQ(result.z, 9.f);
	EXPECT_FLOAT_EQ(result.w, 12.f);
}

TEST(Vector4, FloatMultiplicationAssignmentOperator)
{
	Vector4 vector1(1.f, 2.f, 3.f, 4.f);

	vector1 *= 3.f;

	EXPECT_FLOAT_EQ(vector1.x, 3.f);
	EXPECT_FLOAT_EQ(vector1.y, 6.f);
	EXPECT_FLOAT_EQ(vector1.z, 9.f);
	EXPECT_FLOAT_EQ(vector1.w, 12.f);
}

TEST(Vector4, FloatDivisionOperator)
{
	Vector4 vector1(2.f, 4.f, 6.f, 8.f);

	Vector4 result = vector1 / 2.f;

	EXPECT_FLOAT_EQ(result.x, 1.f);
	EXPECT_FLOAT_EQ(result.y, 2.f);
	EXPECT_FLOAT_EQ(result.z, 3.f);
	EXPECT_FLOAT_EQ(result.w, 4.f);
}

TEST(Vector4, FloatDivisionAssignmentOperator)
{
	Vector4 vector1(2.f, 4.f, 6.f, 8.f);

	vector1 /= 2.f;

	EXPECT_FLOAT_EQ(vector1.x, 1.f);
	EXPECT_FLOAT_EQ(vector1.y, 2.f);
	EXPECT_FLOAT_EQ(vector1.z, 3.f);
	EXPECT_FLOAT_EQ(vector1.w, 4.f);
}



TEST(Vector4, VectorAdditionOperator)
{
	Vector4 vector1(1.f, 2.f, 3.f, 4.f);
	Vector4 vector2(3.f, 4.f, 5.f, 6.f);

	Vector4 result = vector1 + vector2;

	EXPECT_FLOAT_EQ(result.x, 4.f);
	EXPECT_FLOAT_EQ(result.y, 6.f);
	EXPECT_FLOAT_EQ(result.z, 8.f);
	EXPECT_FLOAT_EQ(result.w, 10.f);
}

TEST(Vector4, VectorAdditionAssignmentOperator)
{
	Vector4 vector1(1.f, 2.f, 3.f, 4.f);
	Vector4 vector2(3.f, 4.f, 5.f, 6.f);

	vector1 += vector2;

	EXPECT_FLOAT_EQ(vector1.x, 4.f);
	EXPECT_FLOAT_EQ(vector1.y, 6.f);
	EXPECT_FLOAT_EQ(vector1.z, 8.f);
	EXPECT_FLOAT_EQ(vector1.w, 10.f);
}

TEST(Vector4, VectorSubtractionOperator)
{
	Vector4 vector1(1.f, 2.f, 3.f, 4.f);
	Vector4 vector2(3.f, 4.f, 5.f, 6.f);

	Vector4 result = vector1 - vector2;

	EXPECT_FLOAT_EQ(result.x, -2.f);
	EXPECT_FLOAT_EQ(result.y, -2.f);
	EXPECT_FLOAT_EQ(result.z, -2.f);
	EXPECT_FLOAT_EQ(result.w, -2.f);
}

TEST(Vector4, VectorSubtractionAssignmentOperator)
{
	Vector4 vector1(1.f, 2.f, 3.f, 4.f);
	Vector4 vector2(3.f, 4.f, 5.f, 6.f);

	vector1 -= vector2;

	EXPECT_FLOAT_EQ(vector1.x, -2.f);
	EXPECT_FLOAT_EQ(vector1.y, -2.f);
	EXPECT_FLOAT_EQ(vector1.z, -2.f);
	EXPECT_FLOAT_EQ(vector1.w, -2.f);
}

TEST(Vector4, VectorMultiplicationOperator)
{
	Vector4 vector1(1.f, 2.f, 3.f, 4.f);
	Vector4 vector2(3.f, 4.f, 5.f, 6.f);

	Vector4 result = vector1 * vector2;

	EXPECT_FLOAT_EQ(result.x, 3.f);
	EXPECT_FLOAT_EQ(result.y, 8.f);
	EXPECT_FLOAT_EQ(result.z, 15.f);
	EXPECT_FLOAT_EQ(result.w, 24.f);
}

TEST(Vector4, VectorMultiplicationAssignmentOperator)
{
	Vector4 vector1(1.f, 2.f, 3.f, 4.f);
	Vector4 vector2(3.f, 4.f, 5.f, 6.f);

	vector1 *= vector2;

	EXPECT_FLOAT_EQ(vector1.x, 3.f);
	EXPECT_FLOAT_EQ(vector1.y, 8.f);
	EXPECT_FLOAT_EQ(vector1.z, 15.f);
	EXPECT_FLOAT_EQ(vector1.w, 24.f);
}

TEST(Vector4, VectorDivisionOperator)
{
	Vector4 vector1(4.f, 6.f, 8.f, 10.f);
	Vector4 vector2(2.f, 3.f, 4.f, 5.f);

	Vector4 result = vector1 / vector2;

	EXPECT_FLOAT_EQ(result.x, 2.f);
	EXPECT_FLOAT_EQ(result.y, 2.f);
	EXPECT_FLOAT_EQ(result.z, 2.f);
	EXPECT_FLOAT_EQ(result.w, 2.f);
}

TEST(Vector4, VectorDivisionAssignmentOperator)
{
	Vector4 vector1(4.f, 6.f, 8.f, 10.f);
	Vector4 vector2(2.f, 3.f, 4.f, 5.f);

	vector1 /= vector2;

	EXPECT_FLOAT_EQ(vector1.x, 2.f);
	EXPECT_FLOAT_EQ(vector1.y, 2.f);
	EXPECT_FLOAT_EQ(vector1.z, 2.f);
	EXPECT_FLOAT_EQ(vector1.w, 2.f);
}

TEST(Vector4, VectorEqualityOperator)
{
	Vector4 vector1(3.f, 4.f, 5.f, 6.f);
	Vector4 vector2(3.f, 4.f, 5.f, 6.f);
	Vector4 vector3(6.f, 5.f, 4.f, 3.f);

	ASSERT_TRUE(vector1 == vector2);
	ASSERT_FALSE(vector1 == vector3);
}

TEST(Vector4, VectorInequalityOperator)
{
	Vector4 vector1(3.f, 4.f, 5.f, 6.f);
	Vector4 vector2(6.f, 5.f, 4.f, 3.f);
	Vector4 vector3(3.f, 4.f, 5.f, 6.f);

	ASSERT_TRUE(vector1 != vector2);
	ASSERT_FALSE(vector1 != vector3);
}


TEST(Vector4, ArrayNotationOperator)
{
  Vector4 vector(3.f, 4.f, 5.f, 6.f);

  EXPECT_FLOAT_EQ(vector[0], 3.f);
  EXPECT_FLOAT_EQ(vector[1], 4.f);
  EXPECT_FLOAT_EQ(vector[2], 5.f);
  EXPECT_FLOAT_EQ(vector[3], 6.f);
}


TEST(Vector4Static, DotProduct)
{
	Vector4 vector1(1.f, 2.f, 3.f, 4.f);
	Vector4 vector2(3.f, 4.f, 5.f, 6.f);

	EXPECT_FLOAT_EQ(Vector4::Dot(vector1, vector2), 50.f);
}

TEST(Vector4, MagnitudeSqr)
{
	Vector4 vector(3.f, 4.f, 5.f, 6.f);
	EXPECT_FLOAT_EQ(vector.MagnitudeSquared(), 86.f);
}

TEST(Vector4, Magnitude)
{
	Vector4 vector(3.f, 3.f, 3.f, 3.f);
	EXPECT_FLOAT_EQ(vector.Magnitude(), 6.f);
}

TEST(Vector4Static, Normalize)
{
    Vector4 vector(3, 4, 5, 6);

    Vector4 actualVector = vector.Normalized();

    EXPECT_FLOAT_EQ(actualVector.x, 0.32349831961f);
    EXPECT_FLOAT_EQ(actualVector.y, 0.43133109281f);
    EXPECT_FLOAT_EQ(actualVector.z, 0.53916286602f);
    EXPECT_FLOAT_EQ(actualVector.w, 0.64699663922f);
}


TEST(Vector4, Vector3ConversionOperator)
{
  Vector4 vector(1,2,3,4);
  Vector3 result = (Vector3)vector;

  EXPECT_FLOAT_EQ(result[0], vector[0]);
  EXPECT_FLOAT_EQ(result[1], vector[1]);
  EXPECT_FLOAT_EQ(result[2], vector[2]);
}
