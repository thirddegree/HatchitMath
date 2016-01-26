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

#define _USE_MATH_DEFINES

#include <gtest/gtest.h>
#include "ht_quaternion.h"

using namespace Hatchit;
using namespace Math;

TEST(Quaternion, DefaultConstructor)
{
  Quaternion quat;

  ASSERT_EQ(quat.getX(), 0);
  ASSERT_EQ(quat.getY(), 0);
  ASSERT_EQ(quat.getZ(), 0);
  ASSERT_EQ(quat.getW(), 1);
}

TEST(Quaternion, ParamaterizedFloatConstructor)
{
  Quaternion quat(4,3,2,1);

  ASSERT_EQ(quat.getX(), 4);
  ASSERT_EQ(quat.getY(), 3);
  ASSERT_EQ(quat.getZ(), 2);
  ASSERT_EQ(quat.getW(), 1);
}

TEST(Quaterion, EulerAnglesConstructor)
{
  //90 deg x, 0 deg y, 90 deg z
  Vector3 euler(M_PI/2,0,M_PI/2);
  Quaternion quat(euler);

  ASSERT_NEAR(quat.getX(), .5f, 0.00001f);
  ASSERT_NEAR(quat.getY(), .5f, 0.00001f);
  ASSERT_NEAR(quat.getZ(), .5f, 0.00001f);
  ASSERT_NEAR(quat.getW(), .5f, 0.00001f);
}

TEST(Quaternion, AxisAngleConstructor)
{
  //Based off: http://www.euclideanspace.com/maths/geometry/rotations/conversions/angleToQuaternion/

  float angle = M_PI/2; //90 degrees
  Vector4 angleAxis(1, 0, 0, angle);

  Quaternion quat(angleAxis);

  ASSERT_NEAR(quat.getX(), 0.7071f, 0.00001f);
  ASSERT_NEAR(quat.getY(), 0.0f, 0.00001f);
  ASSERT_NEAR(quat.getZ(), 0.0f, 0.00001f);
  ASSERT_NEAR(quat.getW(), 0.7071f, 0.00001f);
}

TEST(Quaternion, Inversion)
{
  Quaternion quat(4,3,2,1);
  Quaternion inverse = quat.getInverse();

  ASSERT_EQ(inverse.getX(), -4);
  ASSERT_EQ(inverse.getY(), -3);
  ASSERT_EQ(inverse.getZ(), -2);
  ASSERT_EQ(inverse.getW(), 1);
}

TEST(Quaterion, GetAxisAngle)
{
  float angle = M_PI/2; //90 degrees
  Vector4 angleAxis(1, 0, 0, angle);

  Quaternion quat(angleAxis);

  Vector4 resultAA = quat.getAxisAngle();

  ASSERT_EQ(angleAxis[0], resultAA[0]);
  ASSERT_EQ(angleAxis[1], resultAA[1]);
  ASSERT_EQ(angleAxis[2], resultAA[2]);
  ASSERT_EQ(angleAxis[3], resultAA[3]);
}

TEST(Quaternion, GetRotationMatrix)
{
  //Thanks to: http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToMatrix/
  Quaternion quat(0.7071f, 0, 0, 0.7071f);

  Matrix3 mat = quat.getRotationMatrix();

  ASSERT_NEAR(mat[0][0], 1, 0.0001f);
  ASSERT_NEAR(mat[0][1], 0, 0.0001f);
  ASSERT_NEAR(mat[0][2], 0, 0.0001f);

  ASSERT_NEAR(mat[1][0], 0, 0.0001f);
  ASSERT_NEAR(mat[1][1], 0, 0.0001f);
  ASSERT_NEAR(mat[1][2], 1, 0.0001f);

  ASSERT_NEAR(mat[2][0], 0, 0.0001f);
  ASSERT_NEAR(mat[2][1], -1, 0.0001f);
  ASSERT_NEAR(mat[2][2], 0, 0.0001f);
}

//TODO: Finish
TEST(Quaternion, MultiplicationOperator)
{
  Quaternion quat1(3, 4, 3, -sinf(M_PI));
  Quaternion quat2(3.9f, -1, -3, 4);

  Quaternion product = quat1 * quat2;

  //std::cout << product << std::endl;

  //ASSERT_NEAR(product[0], 3, 0.00001f);

}
