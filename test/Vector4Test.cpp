#include <gtest/gtest.h>
#include "ht_vector2.h"
#include "ht_vector3.h"
#include "ht_vector4.h"

using namespace Hatchit;
using namespace Math;

TEST(Vector4, DefaultConstructorFillsZeros)
{
    Vector4 vector;

    ASSERT_EQ(vector.getX(), 0);
    ASSERT_EQ(vector.getY(), 0);
    ASSERT_EQ(vector.getZ(), 0);
    ASSERT_EQ(vector.getW(), 0);
}

TEST(Vector4, ParamaterizedConstructor) {
  Vector4 vector(5,4,3,2);
  ASSERT_EQ(vector.getX(), 5);
  ASSERT_EQ(vector.getY(), 4);
  ASSERT_EQ(vector.getZ(), 3);
  ASSERT_EQ(vector.getW(), 2);
}

TEST(Vector4, AngleAxisConstructor)
{
  Vector3 axis(1,2,3);
  float angle = 5.0f;

  Vector4 angleAxis(axis, angle);

  ASSERT_EQ(angleAxis.getX(), 1);
  ASSERT_EQ(angleAxis.getY(), 2);
  ASSERT_EQ(angleAxis.getZ(), 3);
  ASSERT_EQ(angleAxis.getW(), 5);
}

TEST(Vector4, CopyConstructor)
{
  Vector4 vector1(6,7,8,9);
  Vector4 vector2(vector1);

  ASSERT_EQ(vector2.getX(), vector1.getX());
  ASSERT_EQ(vector2.getY(), vector1.getY());
  ASSERT_EQ(vector2.getZ(), vector1.getZ());
  ASSERT_EQ(vector2.getW(), vector1.getW());
}

TEST(Vector4, Magnitude)
{
  //Magnitude of this vector should be ~9.27362 according to wolfram alpha
  Vector4 vector(3,4,5,6);
  ASSERT_NEAR(vector.getMagnitude(), 9.27362f, 0.00001f);
}

TEST(Vector4, GetAsArray)
{
    Vector4 vector(2,3,4,5);
    float* array = vector.getAsArray();

    ASSERT_EQ(array[0], 2);
    ASSERT_EQ(array[1], 3);
    ASSERT_EQ(array[2], 4);
    ASSERT_EQ(array[3], 5);
}

TEST(Vector4, SettingElementValues)
{
  Vector4 vector(3,4,5,6);
  vector.setX(6);
  vector.setY(7);
  vector.setZ(8);
  vector.setW(9);

  ASSERT_EQ(vector.getX(), 6);
  ASSERT_EQ(vector.getY(), 7);
  ASSERT_EQ(vector.getZ(), 8);
  ASSERT_EQ(vector.getW(), 9);
}

TEST(Vector4, ArrayNotationOperator)
{
  Vector4 vector(3,4,5,6);

  ASSERT_EQ(vector[0], 3);
  ASSERT_EQ(vector[1], 4);
  ASSERT_EQ(vector[2], 5);
  ASSERT_EQ(vector[3], 6);
}

TEST(Vector4, Vector3ConversionOperator)
{
  Vector4 vector(1,2,3,4);
  Vector3 result = (Vector3)vector;

  float invV4W = 1 / vector[3];
  ASSERT_EQ(result[0], vector[0] * invV4W);
  ASSERT_EQ(result[1], vector[1] * invV4W);
  ASSERT_EQ(result[2], vector[2] * invV4W);
}