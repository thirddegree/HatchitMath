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

TEST(Vector4, ParamaterizedConstructor) {
  Vector4 vector(5,4,3,2);
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

TEST(Vector4, CopyConstructor)
{
  Vector4 vector1(6,7,8,9);
  Vector4 vector2(vector1);

  EXPECT_FLOAT_EQ(vector2.x, vector1.x);
  EXPECT_FLOAT_EQ(vector2.y, vector1.y);
  EXPECT_FLOAT_EQ(vector2.z, vector1.z);
  EXPECT_FLOAT_EQ(vector2.w, vector1.w);
}

TEST(Vector4, Magnitude)
{
  //Magnitude of this vector should be ~9.27362 according to wolfram alpha
  Vector4 vector(3,4,5,6);

  float mag = MMVector4Magnitude(vector);
  
  ASSERT_NEAR(mag, 9.27362184f, 0.00001f);
}

TEST(Vector4, SettingElementValues)
{
  Vector4 vector(3,4,5,6);
  vector.x = 6;
  vector.y = 7;
  vector.z = 8;
  vector.w = 9;

  EXPECT_FLOAT_EQ(vector.x, 6);
  EXPECT_FLOAT_EQ(vector.y, 7);
  EXPECT_FLOAT_EQ(vector.z, 8);
  EXPECT_FLOAT_EQ(vector.w, 9);
}

TEST(Vector4, ArrayNotationOperator)
{
  Vector4 vector(3,4,5,6);

  EXPECT_FLOAT_EQ(vector[0], 3);
  EXPECT_FLOAT_EQ(vector[1], 4);
  EXPECT_FLOAT_EQ(vector[2], 5);
  EXPECT_FLOAT_EQ(vector[3], 6);
}

TEST(Vector4, Vector3ConversionOperator)
{
  Vector4 vector(1,2,3,4);
  Vector3 result = (Vector3)vector;

  EXPECT_FLOAT_EQ(result[0], vector[0]);
  EXPECT_FLOAT_EQ(result[1], vector[1]);
  EXPECT_FLOAT_EQ(result[2], vector[2]);
}
