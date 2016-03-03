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
  ASSERT_NEAR(vector.x, 0, FLT_EPSILON);
  ASSERT_NEAR(vector.y, 0, FLT_EPSILON);
  ASSERT_NEAR(vector.z, 0, FLT_EPSILON);
}

TEST(Vector3, ParamaterizedConstructor) {
  Vector3 vector(5, 3, 1);
  ASSERT_EQ(vector.x, 5);
  ASSERT_EQ(vector.y, 3);
  ASSERT_EQ(vector.z, 1);
}

TEST(Vector3, CopyConstructor)
{
  Vector3 vector1(6,7,8);
  Vector3 vector2(vector1);

  ASSERT_EQ(vector2.x, vector1.x);
  ASSERT_EQ(vector2.y, vector1.y);
  ASSERT_EQ(vector2.z, vector1.z);
}

TEST(Vector3, Magnitude)
{
  //Magnitude of this vector should be ~7.07107 according to wolfram alpha
  Vector3 vector(3,4,5);
  ASSERT_NEAR(MMVector3Magnitude(vector), 7.07107f, 0.00001f);
}

TEST(Vector3, SettingElementValues)
{
  Vector3 vector(3,4,5);
  vector.x = 6;
  vector.y = 7;
  vector.z = 8;

  ASSERT_EQ(vector.x, 6);
  ASSERT_EQ(vector.y, 7);
  ASSERT_EQ(vector.z, 8);
}

TEST(Vector3, ScalarMultiplicationOperator)
{
  Vector3 vector(1,2,3);
  Vector3 result = vector * 2;

  ASSERT_EQ(result.x, 2);
  ASSERT_EQ(result.y, 4);
  ASSERT_EQ(result.z, 6);
}

TEST(Vector3, ScalarDivisionOperator)
{
  Vector3 vector(2,4,6);
  Vector3 result = vector / 2;

  ASSERT_EQ(result.x, 1);
  ASSERT_EQ(result.y, 2);
  ASSERT_EQ(result.z, 3);
}

TEST(Vector3, ScalarSubtractionOperator)
{
  Vector3 vector(2,4,6);
  Vector3 result = vector - 2;

  ASSERT_EQ(result.x, 0);
  ASSERT_EQ(result.y, 2);
  ASSERT_EQ(result.z, 4);
}

TEST(Vector3, ScalarAdditionOperator)
{
  Vector3 vector(1,2,3);
  Vector3 result = vector + 2;

  ASSERT_EQ(result.x, 3);
  ASSERT_EQ(result.y, 4);
  ASSERT_EQ(result.z, 5);
}

TEST(Vector3, AppliedScalarMultiplicationOperator)
{
  Vector3 vector(1,2,3);
  vector *= 2;

  ASSERT_EQ(vector.x, 2);
  ASSERT_EQ(vector.y, 4);
  ASSERT_EQ(vector.z, 6);
}

TEST(Vector3, AppliedScalarDivisionOperator)
{
  Vector3 vector(2,4,6);
  vector /= 2;

  ASSERT_EQ(vector.x, 1);
  ASSERT_EQ(vector.y, 2);
  ASSERT_EQ(vector.z, 3);
}

TEST(Vector3, AppliedScalarSubtractionOperator)
{
  Vector3 vector(2,4,6);
  vector -= 2;

  ASSERT_EQ(vector.x, 0);
  ASSERT_EQ(vector.y, 2);
  ASSERT_EQ(vector.z, 4);
}

TEST(Vector3, AppliedScalarAdditionOperator)
{
  Vector3 vector(1,2,3);
  vector += 2;

  ASSERT_EQ(vector.x, 3);
  ASSERT_EQ(vector.y, 4);
  ASSERT_EQ(vector.z, 5);
}

TEST(Vector3, VectorGreaterThanComparisonOperator)
{
  Vector3 smaller(1,1,1);
  Vector3 larger(2,2,2);

  ASSERT_TRUE(larger > smaller);
}

TEST(Vector3, VectorLesserThanComparisonOperator)
{
  Vector3 smaller(1,1,1);
  Vector3 larger(2,2,2);

  ASSERT_TRUE(smaller < larger);
}

TEST(Vector3, VectorEqualityOperator)
{
  Vector3 vector(1,2,3);
  Vector3 sameVector(1,2,3);

  ASSERT_TRUE(vector == sameVector);
}

TEST(Vector3, VectorInequalityOperator)
{
  Vector3 vector(1,2,3);
  Vector3 diffVector(4,5,6);

  ASSERT_TRUE(vector != diffVector);
}

TEST(Vector3, DotOperator)
{
    Vector3 vector1(1,2,3);
    Vector3 vector2(4,5,6);

    ASSERT_EQ(MMVector3Dot(vector1,vector2), 32);
}

TEST(Vector3, VectorAdditionOperator)
{
    Vector3 vector1(1,2,3);
    Vector3 vector2(4,5,6);

    Vector3 result = vector1 + vector2;

    ASSERT_EQ(result.x, 5);
    ASSERT_EQ(result.y, 7);
    ASSERT_EQ(result.z, 9);
}

TEST(Vector3, VectorSubtractionOperator)
{
    Vector3 vector1(4,5,6);
    Vector3 vector2(1,2,3);

    Vector3 result = vector1 - vector2;

    ASSERT_EQ(result.x, 3);
    ASSERT_EQ(result.y, 3);
    ASSERT_EQ(result.z, 3);
}

TEST(Vector3, AppliedVectorAdditionOperator)
{
    Vector3 vector1(1,2,3);
    Vector3 vector2(4,5,6);

    vector1 += vector2;

    ASSERT_EQ(vector1.x, 5);
    ASSERT_EQ(vector1.y, 7);
    ASSERT_EQ(vector1.z, 9);
}

TEST(Vector3, AppliedVectorSubtractionOperator)
{
    Vector3 vector1(4,5,6);
    Vector3 vector2(1,2,3);

    vector1 -= vector2;

    ASSERT_EQ(vector1.x, 3);
    ASSERT_EQ(vector1.y, 3);
    ASSERT_EQ(vector1.z, 3);
}

TEST(Vector3, ArrayNotationOperator)
{
  Vector3 vector(3,4,5);

  ASSERT_EQ(vector[0], 3);
  ASSERT_EQ(vector[1], 4);
  ASSERT_EQ(vector[2], 5);
}

TEST(Vector3, Vector4ConversionOperator)
{
  Vector3 vector(1,2,3);
  Vector4 result = (Vector4)vector;

  ASSERT_EQ(result[0], 1);
  ASSERT_EQ(result[1], 2);
  ASSERT_EQ(result[2], 3);
  ASSERT_EQ(result[3], 1);
}

/*TEST(Vector3, Vector2ConversionOperator)
{
  Vector3 vector(1,2,3);
  Vector2 result = (Vector2)vector;

  ASSERT_EQ(result[0], 1);
  ASSERT_EQ(result[1], 2);
}*/

TEST(Vector3Static, DotProduct)
{
    Vector3 vector1(1,2,3);
    Vector3 vector2(4,5,6);

    ASSERT_EQ(MMVector3Dot(vector1, vector2), 32);
}

TEST(Vector3Static, CrossProduct)
{
  Vector3 vector1(1,2,3);
  Vector3 vector2(4,5,6);

  Vector3 cross = MMVector3Cross(vector1, vector2);

  ASSERT_EQ(cross.x, -3);
  ASSERT_EQ(cross.y, 6);
  ASSERT_EQ(cross.z, -3);
}

TEST(Vector3Static, Normalize)
{
    Vector3 vector(3,4,5);

    Vector3 normal = MMVector3Normalize(vector);

    float inv = 1.0f / 7.07107f;

    ASSERT_NEAR(normal.x, 3.0f * inv, 0.0001f);
    ASSERT_NEAR(normal.y, 4.0f * inv, 0.0001f);
    ASSERT_NEAR(normal.z, 5.0f * inv, 0.0001f);
}
