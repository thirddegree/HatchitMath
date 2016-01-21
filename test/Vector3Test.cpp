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
#include "ht_vector2.h"
#include "ht_vector3.h"
#include "ht_vector4.h"

using namespace Hatchit;
using namespace Math;

TEST(Vector3, DefaultConstructorFillsZeros) {
  Vector3 vector;
  ASSERT_EQ(vector.getX(), 0);
  ASSERT_EQ(vector.getY(), 0);
  ASSERT_EQ(vector.getZ(), 0);
}

TEST(Vector3, ParamaterizedConstructor) {
  Vector3 vector(5, 3, 1);
  ASSERT_EQ(vector.getX(), 5);
  ASSERT_EQ(vector.getY(), 3);
  ASSERT_EQ(vector.getZ(), 1);
}

TEST(Vector3, CopyConstructor)
{
  Vector3 vector1(6,7,8);
  Vector3 vector2(vector1);

  ASSERT_EQ(vector2.getX(), vector1.getX());
  ASSERT_EQ(vector2.getY(), vector1.getY());
  ASSERT_EQ(vector2.getZ(), vector1.getZ());
}

TEST(Vector3, Magnitude)
{
  //Magnitude of this vector should be ~7.07107 according to wolfram alpha
  Vector3 vector(3,4,5);
  ASSERT_NEAR(vector.getMagnitude(), 7.07107f, 0.00001f);
}

TEST(Vector3, GetAsArray)
{
    Vector3 vector(2,3,4);
    float* array = vector.getAsArray();

    ASSERT_EQ(array[0], 2);
    ASSERT_EQ(array[1], 3);
    ASSERT_EQ(array[2], 4);
}

TEST(Vector3, SettingElementValues)
{
  Vector3 vector(3,4,5);
  vector.setX(6);
  vector.setY(7);
  vector.setZ(8);

  ASSERT_EQ(vector.getX(), 6);
  ASSERT_EQ(vector.getY(), 7);
  ASSERT_EQ(vector.getZ(), 8);
}

TEST(Vector3, ScalarMultiplicationOperator)
{
  Vector3 vector(1,2,3);
  Vector3 result = vector * 2;

  ASSERT_EQ(result.getX(), 2);
  ASSERT_EQ(result.getY(), 4);
  ASSERT_EQ(result.getZ(), 6);
}

TEST(Vector3, ScalarDivisionOperator)
{
  Vector3 vector(2,4,6);
  Vector3 result = vector / 2;

  ASSERT_EQ(result.getX(), 1);
  ASSERT_EQ(result.getY(), 2);
  ASSERT_EQ(result.getZ(), 3);
}

TEST(Vector3, ScalarSubtractionOperator)
{
  Vector3 vector(2,4,6);
  Vector3 result = vector - 2;

  ASSERT_EQ(result.getX(), 0);
  ASSERT_EQ(result.getY(), 2);
  ASSERT_EQ(result.getZ(), 4);
}

TEST(Vector3, ScalarAdditionOperator)
{
  Vector3 vector(1,2,3);
  Vector3 result = vector + 2;

  ASSERT_EQ(result.getX(), 3);
  ASSERT_EQ(result.getY(), 4);
  ASSERT_EQ(result.getZ(), 5);
}

TEST(Vector3, AppliedScalarMultiplicationOperator)
{
  Vector3 vector(1,2,3);
  vector *= 2;

  ASSERT_EQ(vector.getX(), 2);
  ASSERT_EQ(vector.getY(), 4);
  ASSERT_EQ(vector.getZ(), 6);
}

TEST(Vector3, AppliedScalarDivisionOperator)
{
  Vector3 vector(2,4,6);
  vector /= 2;

  ASSERT_EQ(vector.getX(), 1);
  ASSERT_EQ(vector.getY(), 2);
  ASSERT_EQ(vector.getZ(), 3);
}

TEST(Vector3, AppliedScalarSubtractionOperator)
{
  Vector3 vector(2,4,6);
  vector -= 2;

  ASSERT_EQ(vector.getX(), 0);
  ASSERT_EQ(vector.getY(), 2);
  ASSERT_EQ(vector.getZ(), 4);
}

TEST(Vector3, AppliedScalarAdditionOperator)
{
  Vector3 vector(1,2,3);
  vector += 2;

  ASSERT_EQ(vector.getX(), 3);
  ASSERT_EQ(vector.getY(), 4);
  ASSERT_EQ(vector.getZ(), 5);
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

    ASSERT_EQ(vector1 * vector2, 32);
}

TEST(Vector3, VectorAdditionOperator)
{
    Vector3 vector1(1,2,3);
    Vector3 vector2(4,5,6);

    Vector3 result = vector1 + vector2;

    ASSERT_EQ(result.getX(), 5);
    ASSERT_EQ(result.getY(), 7);
    ASSERT_EQ(result.getZ(), 9);
}

TEST(Vector3, VectorSubtractionOperator)
{
    Vector3 vector1(4,5,6);
    Vector3 vector2(1,2,3);

    Vector3 result = vector1 - vector2;

    ASSERT_EQ(result.getX(), 3);
    ASSERT_EQ(result.getY(), 3);
    ASSERT_EQ(result.getZ(), 3);
}

TEST(Vector3, AppliedVectorAdditionOperator)
{
    Vector3 vector1(1,2,3);
    Vector3 vector2(4,5,6);

    vector1 += vector2;

    ASSERT_EQ(vector1.getX(), 5);
    ASSERT_EQ(vector1.getY(), 7);
    ASSERT_EQ(vector1.getZ(), 9);
}

TEST(Vector3, AppliedVectorSubtractionOperator)
{
    Vector3 vector1(4,5,6);
    Vector3 vector2(1,2,3);

    vector1 -= vector2;

    ASSERT_EQ(vector1.getX(), 3);
    ASSERT_EQ(vector1.getY(), 3);
    ASSERT_EQ(vector1.getZ(), 3);
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

TEST(Vector3, Vector2ConversionOperator)
{
  Vector3 vector(1,2,3);
  Vector2 result = (Vector2)vector;

  ASSERT_EQ(result[0], 1);
  ASSERT_EQ(result[1], 2);
}

TEST(Vector3Static, DotProduct)
{
    Vector3 vector1(1,2,3);
    Vector3 vector2(4,5,6);

    ASSERT_EQ(Vector3::Dot(vector1, vector2), 32);
}

TEST(Vector3Static, CrossProduct)
{
  Vector3 vector1(1,2,3);
  Vector3 vector2(4,5,6);

  Vector3 cross = Vector3::Cross(vector1, vector2);

  ASSERT_EQ(cross.getX(), -3);
  ASSERT_EQ(cross.getY(), 6);
  ASSERT_EQ(cross.getZ(), -3);
}

TEST(Vector3Static, Normalize)
{
    Vector3 vector(3,4,5);

    Vector3 normal = Vector3::Normalize(vector);

    float inv = 1.0f / 7.07107f;

    ASSERT_NEAR(normal.getX(), 3.0f * inv, 0.00001f);
    ASSERT_NEAR(normal.getY(), 4.0f * inv, 0.00001f);
    ASSERT_NEAR(normal.getZ(), 5.0f * inv, 0.00001f);
}
