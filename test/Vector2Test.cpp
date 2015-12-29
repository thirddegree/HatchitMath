#include <string>

#include <gtest/gtest.h>
#include "ht_vector2.h"

using namespace Hatchit;
using namespace Math;

TEST(Vector2, DefaultConstructorFillsZeros) {
  Vector2 vector;
  ASSERT_EQ(vector.getX(), 0);
  ASSERT_EQ(vector.getY(), 0);
}

TEST(Vector2, ParamaterizedConstructor) {
  Vector2 vector(5, 3);
  ASSERT_EQ(vector.getX(), 5);
  ASSERT_EQ(vector.getY(), 3);
}

TEST(Vector2, CopyConstructor)
{
  Vector2 vector1(6,7);
  Vector2 vector2(vector1);

  ASSERT_EQ(vector2.getX(), vector1.getX());
  ASSERT_EQ(vector2.getY(), vector1.getY());
}

TEST(Vector2, Magnitude)
{
  //Magnitude of this vector should be 5; the good ol 3,4,5 triangle rule
  Vector2 vector(3,4);
  ASSERT_EQ(vector.getMagnitude(), 5);
}

TEST(Vector2, SettingElementValues)
{
  Vector2 vector(3,4);
  vector.setX(5);
  vector.setY(6);

  ASSERT_EQ(vector.getX(), 5);
  ASSERT_EQ(vector.getY(), 6);
}

TEST(Vector2, DotOperator)
{
    Vector2 vector1(1,2);
    Vector2 vector2(3,4);

    ASSERT_EQ(vector1 * vector2, 11);
}

TEST(Vector2, ScalarMultiplicationOperator)
{
  Vector2 vector(1,2);
  Vector2 result = vector * 2;

  ASSERT_EQ(result.getX(), 2);
  ASSERT_EQ(result.getY(), 4);
}

TEST(Vector2, VectorAdditionOperator)
{
    Vector2 vector1(1,2);
    Vector2 vector2(3,4);

    Vector2 result = vector1 + vector2;

    ASSERT_EQ(result.getX(), 4);
    ASSERT_EQ(result.getY(), 6);
}

TEST(Vector2, ArrayNotationOperator)
{
  Vector2 vector(3,4);

  ASSERT_EQ(vector[0], 3);
  ASSERT_EQ(vector[1], 4);
}

TEST(Vector2Static, DotProduct)
{
    Vector2 vector1(1,2);
    Vector2 vector2(3,4);

    ASSERT_EQ(Vector2::Dot(vector1, vector2), 11);
}

TEST(Vector2Static, Normalize)
{
    Vector2 vector(3,4);

    Vector2 normal = Vector2::Normalize(vector);

    float inv = 1.0f / 5.0f;

    ASSERT_EQ(normal.getX(), 3.0f * inv);
    ASSERT_EQ(normal.getY(), 4.0f * inv);
}
