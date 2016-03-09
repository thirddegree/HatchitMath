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

using namespace Hatchit;
using namespace Math;

TEST(Vector2, DefaultConstructorFillsZeros) {
  Vector2 vector;
  EXPECT_FLOAT_EQ(vector.x, 0);
  EXPECT_FLOAT_EQ(vector.y, 0);
}

TEST(Vector2, SingleParameterConstructor) {
	Vector2 vector(5);
	EXPECT_FLOAT_EQ(vector.x, 5);
	EXPECT_FLOAT_EQ(vector.y, 5);
}

TEST(Vector2, TwoParameterConstructor) {
  Vector2 vector(5, 3);
  EXPECT_FLOAT_EQ(vector.x, 5);
  EXPECT_FLOAT_EQ(vector.y, 3);
}

TEST(Vector2, CopyConstructor)
{
  Vector2 vector1(6, 7);
  Vector2 vector2(vector1);

  EXPECT_FLOAT_EQ(vector2.x, vector1.x);
  EXPECT_FLOAT_EQ(vector2.y, vector1.y);
}

TEST(Vector2, SettingElementValues)
{
	Vector2 vector(3, 4);
	vector.x = 5;
	vector.y = 6;

	EXPECT_FLOAT_EQ(vector.x, 5);
	EXPECT_FLOAT_EQ(vector.y, 6);
}


TEST(Vector2, FloatAdditionOperator)
{
	Vector2 vector1(1, 2);

	Vector2 result = vector1 + 3;

	EXPECT_FLOAT_EQ(result.x, 4);
	EXPECT_FLOAT_EQ(result.y, 5);
}

TEST(Vector2, FloatAdditionAssignmentOperator)
{
	Vector2 vector1(1, 2);

	vector1 += 3;

	EXPECT_FLOAT_EQ(vector1.x, 4);
	EXPECT_FLOAT_EQ(vector1.y, 5);
}

TEST(Vector2, FloatSubtractionOperator)
{
	Vector2 vector1(1, 2);

	Vector2 result = vector1 - 3;

	EXPECT_FLOAT_EQ(result.x, -2);
	EXPECT_FLOAT_EQ(result.y, -1);
}

TEST(Vector2, FloatSubtractionAssignmentOperator)
{
	Vector2 vector1(1, 2);

	vector1 -= 3;

	EXPECT_FLOAT_EQ(vector1.x, -2);
	EXPECT_FLOAT_EQ(vector1.y, -1);
}

TEST(Vector2, FloatMultiplicationOperator)
{
	Vector2 vector1(1, 2);

	Vector2 result = vector1 * 3;

	EXPECT_FLOAT_EQ(result.x, 3);
	EXPECT_FLOAT_EQ(result.y, 6);
}

TEST(Vector2, FloatMultiplicationAssignmentOperator)
{
	Vector2 vector1(1, 2);

	vector1 *= 3;

	EXPECT_FLOAT_EQ(vector1.x, 3);
	EXPECT_FLOAT_EQ(vector1.y, 6);
}

TEST(Vector2, FloatDivisionOperator)
{
	Vector2 vector1(4, 8);

	Vector2 result = vector1 / 2;

	EXPECT_FLOAT_EQ(result.x, 2);
	EXPECT_FLOAT_EQ(result.y, 4);
}

TEST(Vector2, FloatDivisionAssignmentOperator)
{
	Vector2 vector1(4, 8);

	vector1 /= 2;

	EXPECT_FLOAT_EQ(vector1.x, 2);
	EXPECT_FLOAT_EQ(vector1.y, 4);
}





TEST(Vector2, VectorAdditionOperator)
{
	Vector2 vector1(1, 2);
	Vector2 vector2(3, 4);

	Vector2 result = vector1 + vector2;

	EXPECT_FLOAT_EQ(result.x, 4);
	EXPECT_FLOAT_EQ(result.y, 6);
}

TEST(Vector2, VectorAdditionAssignmentOperator)
{
	Vector2 vector1(1, 2);
	Vector2 vector2(3, 4);

	vector1 += vector2;

	EXPECT_FLOAT_EQ(vector1.x, 4);
	EXPECT_FLOAT_EQ(vector1.y, 6);
}

TEST(Vector2, VectorSubtractionOperator)
{
	Vector2 vector1(1, 2);
	Vector2 vector2(3, 4);

	Vector2 result = vector1 - vector2;

	EXPECT_FLOAT_EQ(result.x, -2);
	EXPECT_FLOAT_EQ(result.y, -2);
}

TEST(Vector2, VectorSubtractionAssignmentOperator)
{
	Vector2 vector1(1, 2);
	Vector2 vector2(3, 4);

	vector1 -= vector2;

	EXPECT_FLOAT_EQ(vector1.x, -2);
	EXPECT_FLOAT_EQ(vector1.y, -2);
}

TEST(Vector2, VectorMultiplicationOperator)
{
	Vector2 vector1(1, 2);
	Vector2 vector2(3, 4);

	Vector2 result = vector1 * vector2;

	EXPECT_FLOAT_EQ(result.x, 3);
	EXPECT_FLOAT_EQ(result.y, 8);
}

TEST(Vector2, VectorMultiplicationAssignmentOperator)
{
	Vector2 vector1(1, 2);
	Vector2 vector2(3, 4);

	vector1 *= vector2;

	EXPECT_FLOAT_EQ(vector1.x, 3);
	EXPECT_FLOAT_EQ(vector1.y, 8);
}

TEST(Vector2, VectorDivisionOperator)
{
	Vector2 vector1(4, 9);
	Vector2 vector2(2, 3);

	Vector2 result = vector1 / vector2;

	EXPECT_FLOAT_EQ(result.x, 2);
	EXPECT_FLOAT_EQ(result.y, 3);
}

TEST(Vector2, VectorDivisionAssignmentOperator)
{
	Vector2 vector1(4, 9);
	Vector2 vector2(2, 3);

	vector1 /= vector2;

	EXPECT_FLOAT_EQ(vector1.x, 2);
	EXPECT_FLOAT_EQ(vector1.y, 3);
}



TEST(Vector2, FloatCompareOperators)
{
	Vector2 vector(3, 4);
	ASSERT_TRUE(vector > 4.5);
	ASSERT_TRUE(vector < 5.5);
	ASSERT_TRUE(4.5 < vector);
	ASSERT_TRUE(5.5 > vector);
	ASSERT_FALSE(vector < 4.5);
	ASSERT_FALSE(vector > 5.5);
	ASSERT_FALSE(4.5 > vector);
	ASSERT_FALSE(5.5 < vector);
}

TEST(Vector2, VectorCompareOperator)
{
	Vector2 vector1(3, 4);
	Vector2 vector2(4, 4);

	ASSERT_TRUE(vector1 < vector2);
	ASSERT_TRUE(vector2 > vector1);
	ASSERT_FALSE(vector1 > vector2);
	ASSERT_FALSE(vector2 < vector1);
}

TEST(Vector2, VectorEqualityOperator)
{
	Vector2 vector1(3, 4);
	Vector2 vector2(3, 4);
	Vector2 vector3(4, 3);

	ASSERT_TRUE(vector1 == vector2);
	ASSERT_FALSE(vector1 == vector3);
}

TEST(Vector2, VectorInequalityOperator)
{
	Vector2 vector1(3, 4);
	Vector2 vector2(4, 3);
	Vector2 vector3(3, 4);

	ASSERT_TRUE(vector1 != vector2);
	ASSERT_FALSE(vector1 != vector3);
}

TEST(Vector2, ArrayNotationOperator)
{
	Vector2 vector1(3, 4);

	EXPECT_FLOAT_EQ(vector1[0], 3);
	EXPECT_FLOAT_EQ(vector1[1], 4);
}

TEST(Vector2Static, DotProduct)
{
    Vector2 vector1(1, 2);
    Vector2 vector2(3, 4);

    EXPECT_FLOAT_EQ(Vector2::Dot(vector1, vector2), 11);
}

TEST(Vector2, MagnitudeSqr)
{
	//Magnitude of this vector should be 5; the good ol 3,4,5 triangle rule
	Vector2 vector(3, 4);
	ASSERT_NEAR(vector.MagnitudeSquared(), 25, 0.00001f);
}

TEST(Vector2, Magnitude)
{
	//Magnitude of this vector should be 5; the good ol 3,4,5 triangle rule
	Vector2 vector(3, 4);
	ASSERT_NEAR(vector.Magnitude(), 5, 0.00001f);
}

TEST(Vector2Static, Normalize)
{
    Vector2 vector(3, 4);

    vector.Normalize();

    float inv = 1.0f / 5.0f;

    ASSERT_NEAR(vector.x, 3.0f * inv, 0.00001f);
    ASSERT_NEAR(vector.y, 4.0f * inv, 0.00001f);
}
