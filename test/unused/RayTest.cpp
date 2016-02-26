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
#include "ht_ray.h"
#include <cfloat>

using namespace Hatchit;
using namespace Math;

TEST(Ray, DirectionConstructor)
{
  //Ray at 0,0,0 with direction 1,2,3
  Ray ray (Vector3(1,2,3));

  Vector3 origin = ray.getOrigin();
  Vector3 direction = ray.getDirection();

  //Origin should stay 0,0,0
  ASSERT_NEAR(origin[0], 0, FLT_EPSILON);
  ASSERT_NEAR(origin[1], 0, FLT_EPSILON);
  ASSERT_NEAR(origin[2], 0, FLT_EPSILON);

  //Direction should stay 1,2,3
  ASSERT_EQ(direction[0], 1);
  ASSERT_EQ(direction[1], 2);
  ASSERT_EQ(direction[2], 3);
}

TEST(Ray, OriginDirectionConstructor)
{
  //Ray at 5,6,7 with direction 1,2,3
  Ray ray (Vector3(5,6,7),Vector3(1,2,3));

  Vector3 origin = ray.getOrigin();
  Vector3 direction = ray.getDirection();

  //Origin should stay 5,6,7
  ASSERT_EQ(origin[0], 5);
  ASSERT_EQ(origin[1], 6);
  ASSERT_EQ(origin[2], 7);

  //Direction should stay 1,2,3
  ASSERT_EQ(direction[0], 1);
  ASSERT_EQ(direction[1], 2);
  ASSERT_EQ(direction[2], 3);
}

TEST(Ray, SettingOrigin)
{
  Ray ray(Vector3(1,2,3));

  //Change origin to 5,6,7
  ray.setOrigin(Vector3(5,6,7));

  Vector3 origin = ray.getOrigin();

  //Origin should now be 5,6,7
  ASSERT_EQ(origin[0], 5);
  ASSERT_EQ(origin[1], 6);
  ASSERT_EQ(origin[2], 7);
}

TEST(Ray, SettingDirection)
{
  Ray ray(Vector3(1,2,3));

  //Change direction to 5,6,7
  ray.setDirection(Vector3(5,6,7));

  Vector3 direction = ray.getDirection();

  //Origin should now be 5,6,7
  ASSERT_EQ(direction[0], 5);
  ASSERT_EQ(direction[1], 6);
  ASSERT_EQ(direction[2], 7);
}
