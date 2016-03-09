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
    ASSERT_NEAR(vector.x, 0, FLT_EPSILON);
	ASSERT_NEAR(vector.y, 0, FLT_EPSILON);
	ASSERT_NEAR(vector.z, 0, FLT_EPSILON);
	ASSERT_NEAR(vector.w, 0, FLT_EPSILON);
}

TEST(Vector4, SingleParameterConstructor) {
	Vector4 vector(5);
	EXPECT_FLOAT_EQ(vector.x, 5);
	EXPECT_FLOAT_EQ(vector.y, 5);
	EXPECT_FLOAT_EQ(vector.z, 5);
	EXPECT_FLOAT_EQ(vector.w, 5);
}

TEST(Vector4, ParamaterizedConstructor) {
  Vector4 vector(5,4,3,2);
  EXPECT_FLOAT_EQ(vector.x, 5);
  EXPECT_FLOAT_EQ(vector.y, 4);
  EXPECT_FLOAT_EQ(vector.z, 3);
  EXPECT_FLOAT_EQ(vector.w, 2);
}

TEST(Vector4, Vector2Constructor) {
	Vector4 vector(Vector2(5, 4), 3, 2);
	EXPECT_FLOAT_EQ(vector.x, 5);
	EXPECT_FLOAT_EQ(vector.y, 4);
	EXPECT_FLOAT_EQ(vector.z, 3);
	EXPECT_FLOAT_EQ(vector.w, 2);
}

TEST(Vector4, Vector3Constructor) {
	Vector4 vector(Vector3(5,4,3), 2);
	EXPECT_FLOAT_EQ(vector.x, 5);
	EXPECT_FLOAT_EQ(vector.y, 4);
	EXPECT_FLOAT_EQ(vector.z, 3);
	EXPECT_FLOAT_EQ(vector.w, 2);
}
TEST(Vector4, CopyConstructor) {
	Vector4 vector(Vector4(5, 4, 3, 2));
	EXPECT_FLOAT_EQ(vector.x, 5);
	EXPECT_FLOAT_EQ(vector.y, 4);
	EXPECT_FLOAT_EQ(vector.z, 3);
	EXPECT_FLOAT_EQ(vector.w, 2);
}

TEST(Vector4, AngleAxisConstructor)
{
  Vector3 axis(1,2,3);
  float angle = 5.0f;

  Vector4 angleAxis(axis, angle);

  EXPECT_FLOAT_EQ(angleAxis.x, 1);
  EXPECT_FLOAT_EQ(angleAxis.y, 2);
  EXPECT_FLOAT_EQ(angleAxis.z, 3);
  EXPECT_FLOAT_EQ(angleAxis.w, 5);
}

TEST(Vector4, SettingElementValues)
{
	Vector4 vector(3, 4, 5, 6);
	vector.x = 6;
	vector.y = 7;
	vector.z = 8;
	vector.w = 9;

	EXPECT_FLOAT_EQ(vector.x, 6);
	EXPECT_FLOAT_EQ(vector.y, 7);
	EXPECT_FLOAT_EQ(vector.z, 8);
	EXPECT_FLOAT_EQ(vector.w, 9);
}


TEST(Vector4, FloatAdditionOperator)
{
	Vector4 vector1(1, 2, 3, 4);

	Vector4 result = vector1 + 3;

	EXPECT_FLOAT_EQ(result.x, 4);
	EXPECT_FLOAT_EQ(result.y, 5);
	EXPECT_FLOAT_EQ(result.z, 6);
	EXPECT_FLOAT_EQ(result.w, 7);
}

TEST(Vector4, FloatAdditionAssignmentOperator)
{
	Vector4 vector1(1, 2, 3, 4);

	vector1 += 3;

	EXPECT_FLOAT_EQ(vector1.x, 4);
	EXPECT_FLOAT_EQ(vector1.y, 5);
	EXPECT_FLOAT_EQ(vector1.z, 6);
	EXPECT_FLOAT_EQ(vector1.w, 7);
}

TEST(Vector4, FloatSubtractionOperator)
{
	Vector4 vector1(1, 2, 3, 4);

	Vector4 result = vector1 - 3;

	EXPECT_FLOAT_EQ(result.x, -2);
	EXPECT_FLOAT_EQ(result.y, -1);
	EXPECT_FLOAT_EQ(result.z, 0);
	EXPECT_FLOAT_EQ(result.w, 1);
}

TEST(Vector4, FloatSubtractionAssignmentOperator)
{
	Vector4 vector1(1, 2, 3, 4);

	vector1 -= 3;

	EXPECT_FLOAT_EQ(vector1.x, -2);
	EXPECT_FLOAT_EQ(vector1.y, -1);
	EXPECT_FLOAT_EQ(vector1.z, 0);
	EXPECT_FLOAT_EQ(vector1.w, 1);
}

TEST(Vector4, FloatMultiplicationOperator)
{
	Vector4 vector1(1, 2, 3, 4);

	Vector4 result = vector1 * 3;

	EXPECT_FLOAT_EQ(result.x, 3);
	EXPECT_FLOAT_EQ(result.y, 6);
	EXPECT_FLOAT_EQ(result.z, 9);
	EXPECT_FLOAT_EQ(result.w, 12);
}

TEST(Vector4, FloatMultiplicationAssignmentOperator)
{
	Vector4 vector1(1, 2, 3, 4);

	vector1 *= 3;

	EXPECT_FLOAT_EQ(vector1.x, 3);
	EXPECT_FLOAT_EQ(vector1.y, 6);
	EXPECT_FLOAT_EQ(vector1.z, 9);
	EXPECT_FLOAT_EQ(vector1.w, 12);
}

TEST(Vector4, FloatDivisionOperator)
{
	Vector4 vector1(2, 4, 6, 8);

	Vector4 result = vector1 / 2;

	EXPECT_FLOAT_EQ(result.x, 1);
	EXPECT_FLOAT_EQ(result.y, 2);
	EXPECT_FLOAT_EQ(result.z, 3);
	EXPECT_FLOAT_EQ(result.w, 4);
}

TEST(Vector4, FloatDivisionAssignmentOperator)
{
	Vector4 vector1(2, 4, 6, 8);

	vector1 /= 2;

	EXPECT_FLOAT_EQ(vector1.x, 1);
	EXPECT_FLOAT_EQ(vector1.y, 2);
	EXPECT_FLOAT_EQ(vector1.z, 3);
	EXPECT_FLOAT_EQ(vector1.w, 4);
}



TEST(Vector4, VectorAdditionOperator)
{
	Vector4 vector1(1, 2, 3, 4);
	Vector4 vector2(3, 4, 5, 6);

	Vector4 result = vector1 + vector2;

	EXPECT_FLOAT_EQ(result.x, 4);
	EXPECT_FLOAT_EQ(result.y, 6);
	EXPECT_FLOAT_EQ(result.z, 8);
	EXPECT_FLOAT_EQ(result.w, 10);
}

TEST(Vector4, VectorAdditionAssignmentOperator)
{
	Vector4 vector1(1, 2, 3, 4);
	Vector4 vector2(3, 4, 5, 6);

	vector1 += vector2;

	EXPECT_FLOAT_EQ(vector1.x, 4);
	EXPECT_FLOAT_EQ(vector1.y, 6);
	EXPECT_FLOAT_EQ(vector1.z, 8);
	EXPECT_FLOAT_EQ(vector1.w, 10);
}

TEST(Vector4, VectorSubtractionOperator)
{
	Vector4 vector1(1, 2, 3, 4);
	Vector4 vector2(3, 4, 5, 6);

	Vector4 result = vector1 - vector2;

	EXPECT_FLOAT_EQ(result.x, -2);
	EXPECT_FLOAT_EQ(result.y, -2);
	EXPECT_FLOAT_EQ(result.z, -2);
	EXPECT_FLOAT_EQ(result.w, -2);
}

TEST(Vector4, VectorSubtractionAssignmentOperator)
{
	Vector4 vector1(1, 2, 3, 4);
	Vector4 vector2(3, 4, 5, 6);

	vector1 -= vector2;

	EXPECT_FLOAT_EQ(vector1.x, -2);
	EXPECT_FLOAT_EQ(vector1.y, -2);
	EXPECT_FLOAT_EQ(vector1.z, -2);
	EXPECT_FLOAT_EQ(vector1.w, -2);
}

TEST(Vector4, VectorMultiplicationOperator)
{
	Vector4 vector1(1, 2, 3, 4);
	Vector4 vector2(3, 4, 5, 6);

	Vector4 result = vector1 * vector2;

	EXPECT_FLOAT_EQ(result.x, 3);
	EXPECT_FLOAT_EQ(result.y, 8);
	EXPECT_FLOAT_EQ(result.z, 15);
	EXPECT_FLOAT_EQ(result.w, 24);
}

TEST(Vector4, VectorMultiplicationAssignmentOperator)
{
	Vector4 vector1(1, 2, 3, 4);
	Vector4 vector2(3, 4, 5, 6);

	ASSERT_TRUE(false);//vector1 *= vector2;

	EXPECT_FLOAT_EQ(vector1.x, 3);
	EXPECT_FLOAT_EQ(vector1.y, 8);
	EXPECT_FLOAT_EQ(vector1.z, 15);
	EXPECT_FLOAT_EQ(vector1.w, 24);
}

TEST(Vector4, VectorDivisionOperator)
{
	Vector4 vector1(4, 6, 8, 10);
	Vector4 vector2(2, 3, 4, 5);

	Vector4 result;// = vector1 / vector2;
	ASSERT_TRUE(false);

	EXPECT_FLOAT_EQ(result.x, 2);
	EXPECT_FLOAT_EQ(result.y, 2);
	EXPECT_FLOAT_EQ(result.z, 2);
	EXPECT_FLOAT_EQ(result.w, 2);
}

TEST(Vector4, VectorDivisionAssignmentOperator)
{
	Vector4 vector1(4, 6, 8, 10);
	Vector4 vector2(2, 3, 4, 5);

	ASSERT_TRUE(false);//vector1 /= vector2;

	EXPECT_FLOAT_EQ(vector1.x, 2);
	EXPECT_FLOAT_EQ(vector1.y, 2);
	EXPECT_FLOAT_EQ(vector1.z, 2);
	EXPECT_FLOAT_EQ(vector1.w, 2);
}


TEST(Vector4, FloatCompareOperators)
{
	Vector4 vector(5, 5, 5, 5);
	ASSERT_TRUE(vector > 9.5);
	ASSERT_TRUE(vector < 11.5);
	ASSERT_TRUE(false);//ASSERT_TRUE(9.5 < vector);
	ASSERT_TRUE(false);//ASSERT_TRUE(11.5 > vector);
	ASSERT_FALSE(vector < 9.5);
	ASSERT_FALSE(vector > 11.5);
	ASSERT_TRUE(false);//ASSERT_FALSE(9.5 > vector);
	ASSERT_TRUE(false);//ASSERT_FALSE(11.5 < vector);
}

TEST(Vector4, VectorCompareOperator)
{
	Vector4 vector1(3, 4, 5, 6);
	Vector4 vector2(4, 4, 5, 6);

	ASSERT_TRUE(vector1 < vector2);
	ASSERT_TRUE(vector2 > vector1);
	ASSERT_FALSE(vector1 > vector2);
	ASSERT_FALSE(vector2 < vector1);
}

TEST(Vector4, VectorEqualityOperator)
{
	Vector4 vector1(3, 4, 5, 6);
	Vector4 vector2(3, 4, 5, 6);
	Vector4 vector3(6, 5, 4, 3);

	ASSERT_TRUE(vector1 == vector2);
	ASSERT_FALSE(vector1 == vector3);
}

TEST(Vector4, VectorInequalityOperator)
{
	Vector4 vector1(3, 4, 5, 6);
	Vector4 vector2(6, 5, 4, 3);
	Vector4 vector3(3, 4, 5, 6);

	ASSERT_TRUE(vector1 != vector2);
	ASSERT_FALSE(vector1 != vector3);
}


TEST(Vector4, ArrayNotationOperator)
{
  Vector4 vector(3, 4, 5, 6);

  EXPECT_FLOAT_EQ(vector[0], 3);
  EXPECT_FLOAT_EQ(vector[1], 4);
  EXPECT_FLOAT_EQ(vector[2], 5);
  EXPECT_FLOAT_EQ(vector[3], 6);
}


TEST(Vector4Static, DotProduct)
{
	Vector4 vector1(1, 2, 3, 4);
	Vector4 vector2(3, 4);

	ASSERT_TRUE(false);//EXPECT_FLOAT_EQ(Vector4::Dot(vector1, vector2), 11);
}

TEST(Vector4, MagnitudeSqr)
{
	Vector4 vector(3, 4, 5, 6);
	ASSERT_TRUE(false);//ASSERT_NEAR(vector.MagnitudeSquared(), 86, 0.00001f);
}

TEST(Vector4, Magnitude)
{
	Vector4 vector(3, 3, 3, 3);
	ASSERT_TRUE(false);//ASSERT_NEAR(vector.Magnitude(), 6, 0.00001f);
}

TEST(Vector4Static, Normalize)
{
	Vector4 vector(3, 4);

	ASSERT_TRUE(false);//vector.Normalize();

	float inv = 1.0f / 5.0f;

	ASSERT_NEAR(vector.x, 3.0f * inv, 0.00001f);
	ASSERT_NEAR(vector.y, 4.0f * inv, 0.00001f);
}


TEST(Vector4, Vector3ConversionOperator)
{
  Vector4 vector(1,2,3,4);
  Vector3 result = (Vector3)vector;

  EXPECT_FLOAT_EQ(result[0], vector[0]);
  EXPECT_FLOAT_EQ(result[1], vector[1]);
  EXPECT_FLOAT_EQ(result[2], vector[2]);
}
