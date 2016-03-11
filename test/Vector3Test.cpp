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

using namespace Hatchit;
using namespace Math;

TEST(Vector3, DefaultConstructorFillsZeros) {
  Vector3 vector;
  EXPECT_FLOAT_EQ(vector.x, 0.f);
  EXPECT_FLOAT_EQ(vector.y, 0.f);
  EXPECT_FLOAT_EQ(vector.z, 0.f);
}

TEST(Vector3, SingleValueConstructor) {
	Vector3 vector(3);
	EXPECT_FLOAT_EQ(vector.x, 3);
}

TEST(Vector3, Vector2AndFloatConstructor) {
	Vector3 vector(Vector2(3, 4), 5);
	EXPECT_FLOAT_EQ(vector.x, 3);
	EXPECT_FLOAT_EQ(vector.y, 4);
	EXPECT_FLOAT_EQ(vector.z, 5);
}

TEST(Vector3, ThreeParameterConstructor) {
  Vector3 vector(5, 3, 1);
  EXPECT_FLOAT_EQ(vector.x, 5);
  EXPECT_FLOAT_EQ(vector.y, 3);
  EXPECT_FLOAT_EQ(vector.z, 1);
}

TEST(Vector3, CopyConstructor)
{
  Vector3 vector1(6,7,8);
  Vector3 vector2(vector1);

  EXPECT_FLOAT_EQ(vector2.x, vector1.x);
  EXPECT_FLOAT_EQ(vector2.y, vector1.y);
  EXPECT_FLOAT_EQ(vector2.z, vector1.z);
}

TEST(Vector3, SettingElementValues)
{
  Vector3 vector(3,4,5);
  vector.x = 6;
  vector.y = 7;
  vector.z = 8;

  EXPECT_FLOAT_EQ(vector.x, 6);
  EXPECT_FLOAT_EQ(vector.y, 7);
  EXPECT_FLOAT_EQ(vector.z, 8);
}

TEST(Vector3, FloatAdditionOperator)
{
	Vector3 vector(1, 2, 3);
	Vector3 result = vector + 2;

	EXPECT_FLOAT_EQ(result.x, 3);
	EXPECT_FLOAT_EQ(result.y, 4);
	EXPECT_FLOAT_EQ(result.z, 5);
}

TEST(Vector3, FloatAdditionAssignmentOperator)
{
	Vector3 vector(1, 2, 3);
	vector += 2;

	EXPECT_FLOAT_EQ(vector.x, 3);
	EXPECT_FLOAT_EQ(vector.y, 4);
	EXPECT_FLOAT_EQ(vector.z, 5);
}

TEST(Vector3, FloatSubtractionOperator)
{
	Vector3 vector(2, 4, 6);
	Vector3 result = vector - 2;

	EXPECT_FLOAT_EQ(result.x, 0);
	EXPECT_FLOAT_EQ(result.y, 2);
	EXPECT_FLOAT_EQ(result.z, 4);
}

TEST(Vector3, FloatSubtractionAssignmentOperator)
{
	Vector3 vector(2, 4, 6);
	vector -= 2;

	EXPECT_FLOAT_EQ(vector.x, 0);
	EXPECT_FLOAT_EQ(vector.y, 2);
	EXPECT_FLOAT_EQ(vector.z, 4);
}

TEST(Vector3, FloatMultiplicationOperator)
{
  Vector3 vector(1,2,3);
  Vector3 result = vector * 2;

  EXPECT_FLOAT_EQ(result.x, 2);
  EXPECT_FLOAT_EQ(result.y, 4);
  EXPECT_FLOAT_EQ(result.z, 6);
}

TEST(Vector3, FloatMultiplicationAssignmentOperator)
{
	Vector3 vector(1, 2, 3);
	vector *= 2;

	EXPECT_FLOAT_EQ(vector.x, 2);
	EXPECT_FLOAT_EQ(vector.y, 4);
	EXPECT_FLOAT_EQ(vector.z, 6);
}

TEST(Vector3, FloatDivisionOperator)
{
  Vector3 vector(2,4,6);
  Vector3 result = vector / 2;

  EXPECT_FLOAT_EQ(result.x, 1);
  EXPECT_FLOAT_EQ(result.y, 2);
  EXPECT_FLOAT_EQ(result.z, 3);
}

TEST(Vector3, FloatDivisionAssignmentOperator)
{
	Vector3 vector(2, 4, 6);
	vector /= 2;

	EXPECT_FLOAT_EQ(vector.x, 1);
	EXPECT_FLOAT_EQ(vector.y, 2);
	EXPECT_FLOAT_EQ(vector.z, 3);
}


TEST(Vector3, VectorAdditionOperator)
{
	Vector3 vector1(1, 2, 3);
	Vector3 vector2(4, 5, 6);
	Vector3 result = vector1 + vector2;

	EXPECT_FLOAT_EQ(result.x, 5);
	EXPECT_FLOAT_EQ(result.y, 7);
	EXPECT_FLOAT_EQ(result.z, 9);
}

TEST(Vector3, VectorAdditionAssignmentOperator)
{
	Vector3 vector1(1, 2, 3);
	Vector3 vector2(4, 5, 6);
	vector1 += vector2;

	EXPECT_FLOAT_EQ(vector1.x, 5);
	EXPECT_FLOAT_EQ(vector1.y, 7);
	EXPECT_FLOAT_EQ(vector1.z, 9);
}

TEST(Vector3, VectorSubtractionOperator)
{
	Vector3 vector1(1, 2, 3);
	Vector3 vector2(4, 5, 6);
	Vector3 result = vector1 - vector2;

	EXPECT_FLOAT_EQ(result.x, -3);
	EXPECT_FLOAT_EQ(result.y, -3);
	EXPECT_FLOAT_EQ(result.z, -3);
}

TEST(Vector3, VectorSubtractionAssignmentOperator)
{
	Vector3 vector1(1, 2, 3);
	Vector3 vector2(4, 5, 6);
	vector1 -= vector2;

	EXPECT_FLOAT_EQ(vector1.x, -3);
	EXPECT_FLOAT_EQ(vector1.y, -3);
	EXPECT_FLOAT_EQ(vector1.z, -3);
}

TEST(Vector3, VectorMultiplicationOperator)
{
	Vector3 vector1(1, 2, 3);
	Vector3 vector2(4, 5, 6);
	Vector3 result = vector1 * vector2;

	EXPECT_FLOAT_EQ(result.x, 4);
	EXPECT_FLOAT_EQ(result.y, 10);
	EXPECT_FLOAT_EQ(result.z, 18);
}

TEST(Vector3, VectorMultiplicationAssignmentOperator)
{
	Vector3 vector1(1, 2, 3);
	Vector3 vector2(4, 5, 6);
	vector1 *= vector2;
	
	EXPECT_FLOAT_EQ(vector1.x, 4);
	EXPECT_FLOAT_EQ(vector1.y, 10);
	EXPECT_FLOAT_EQ(vector1.z, 18);
}

TEST(Vector3, VectorDivisionOperator)
{
	Vector3 vector1(4, 9, 16);
	Vector3 vector2(2, 3, 4);
	Vector3 result = vector1 / vector2;

	EXPECT_FLOAT_EQ(result.x, 2);
	EXPECT_FLOAT_EQ(result.y, 3);
	EXPECT_FLOAT_EQ(result.z, 4);
}

TEST(Vector3, VectorDivisionAssignmentOperator)
{
	Vector3 vector1(4, 9, 16);
	Vector3 vector2(2, 3, 4);
	vector1 /= vector2;

	EXPECT_FLOAT_EQ(vector1.x, 2);
	EXPECT_FLOAT_EQ(vector1.y, 3);
	EXPECT_FLOAT_EQ(vector1.z, 4);
}

TEST(Vector3, VectorEqualityOperator)
{
	Vector3 vector1(3, 4, 5);
	Vector3 vector2(3, 4, 5);
	Vector3 vector3(5, 4, 3);

	ASSERT_TRUE(vector1 == vector2);
	ASSERT_FALSE(vector1 == vector3);
}

TEST(Vector3, VectorInequalityOperator)
{
	Vector3 vector1(3, 4, 5);
	Vector3 vector2(4, 4, 5);
	Vector3 vector3(3, 4, 5);

	ASSERT_TRUE(vector1 != vector2);
	ASSERT_FALSE(vector1 != vector3);
}

TEST(Vector3, ArrayNotationOperator)
{
	Vector3 vector(3, 4, 5);

	EXPECT_FLOAT_EQ(vector[0], 3);
	EXPECT_FLOAT_EQ(vector[1], 4);
	EXPECT_FLOAT_EQ(vector[2], 5);
}

TEST(Vector3, DotOperator)
{
    Vector3 vector1(1,2,3);
    Vector3 vector2(4,5,6);

    EXPECT_FLOAT_EQ(MMVector3Dot(vector1,vector2), 32);
}

TEST(Vector3Static, DotProduct)
{
    Vector3 vector1(1,2,3);
    Vector3 vector2(4,5,6);

    EXPECT_FLOAT_EQ(Vector3::Dot(vector1, vector2), 32);
}

TEST(Vector3Static, CrossProduct)
{
  Vector3 vector1(1,2,3);
  Vector3 vector2(4,5,6);

  Vector3 cross = Vector3::Cross(vector1, vector2);

  EXPECT_FLOAT_EQ(cross.x, -3);
  EXPECT_FLOAT_EQ(cross.y, 6);
  EXPECT_FLOAT_EQ(cross.z, -3);
}

TEST(Vector3, MagnitudeSqr)
{
	//Magnitude of this vector should be ~7.07107 according to wolfram alpha
	Vector3 vector(3, 4, 5);
	EXPECT_FLOAT_EQ(vector.MagnitudeSquared(), 50);
}

TEST(Vector3, Magnitude)
{
	//Magnitude of this vector should be ~7.07107 according to wolfram alpha
	Vector3 vector(3, 4, 5);
	ASSERT_NEAR(vector.Magnitude(), 7.07107f, 0.00001f);
}

TEST(Vector3Static, Normalize)
{
    Vector3 vector(3,4,5);

    vector.Normalized();

    float inv = 1.0f / 7.07107f;

    ASSERT_NEAR(vector.x, 3.0f * inv, 0.00001f);
    ASSERT_NEAR(vector.y, 4.0f * inv, 0.00001f);
    ASSERT_NEAR(vector.z, 5.0f * inv, 0.00001f);
}
