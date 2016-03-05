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

using namespace Hatchit;
using namespace Math;

TEST(Vector2, DefaultConstructorFillsZeros) {
  Vector2 vector;
  ASSERT_EQ(vector.x, 0);
  ASSERT_EQ(vector.y, 0);
}

TEST(Vector2, ParamaterizedConstructor) {
  Vector2 vector(5, 3);
  ASSERT_EQ(vector.x, 5);
  ASSERT_EQ(vector.y, 3);
}

TEST(Vector2, CopyConstructor)
{
  Vector2 vector1(6, 7);
  Vector2 vector2(vector1);

  ASSERT_EQ(vector2.x, vector1.x);
  ASSERT_EQ(vector2.y, vector1.y);
}

TEST(Vector2, Magnitude)
{
  //Magnitude of this vector should be 5; the good ol 3,4,5 triangle rule
  Vector2 vector(3,4);
  ASSERT_EQ(vector.getMagnitude(), 5);
}

TEST(Vector2, SettingElementValues)
{
  Vector2 vector(3, 4);
  vector.x = 5;
  vector.y = 6;

  ASSERT_EQ(vector.x, 5);
  ASSERT_EQ(vector.y, 6);
}

TEST(Vector2, DotProduct)
{
    Vector2 vector1(1, 2);
    Vector2 vector2(3, 4);

    ASSERT_EQ(MMVector2Dotvector1, vector2), 11);
}

TEST(Vector2, ScalarMultiplicationOperator)
{
  Vector2 vector(1, 2);
  Vector2 result = vector * 2;

  ASSERT_EQ(result.x, 2);
  ASSERT_EQ(result.y, 4);
}

TEST(Vector2, VectorAdditionOperator)
{
    Vector2 vector1(1, 2);
    Vector2 vector2(3, 4);

    Vector2 result = vector1 + vector2;

    ASSERT_EQ(result.x, 4);
    ASSERT_EQ(result.y, 6);
}

TEST(Vector2, ArrayNotationOperator)
{
  Vector2 vector(3, 4);

  ASSERT_EQ(vector[0], 3);
  ASSERT_EQ(vector[1], 4);
}

TEST(Vector2Static, Normalize)
{
    Vector2 vector(3, 4);

    Vector2 normal = MMVector2Normalize(vector);

    float inv = 1.0f / 5.0f;

    ASSERT_EQ(normal.x, 3.0f * inv);
    ASSERT_EQ(normal.y, 4.0f * inv);
}
