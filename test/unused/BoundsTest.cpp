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
#include "ht_bounds.h"

using namespace Hatchit;
using namespace Math;

TEST(Bounds, DefaultConstructor)
{
  Bounds bounds;

  Vector3 center = bounds.getCenter();
  float xWidth = bounds.getXWidth();
  float yWidth = bounds.getYWidth();
  float zWidth = bounds.getZWidth();

  //Center should be 0,0,0
  ASSERT_EQ(center[0], 0);
  ASSERT_EQ(center[1], 0);
  ASSERT_EQ(center[2], 0);

  //All widths should be 1.0f
  ASSERT_EQ(xWidth, 1.0f);
  ASSERT_EQ(yWidth, 1.0f);
  ASSERT_EQ(zWidth, 1.0f);
}

TEST(Bounds, SymmetricWidthConstructor)
{
  Vector3 center(1,2,3);
  float width = 2.0f;

  Bounds bounds(center, width);

  Vector3 testCenter = bounds.getCenter();
  float xWidth = bounds.getXWidth();
  float yWidth = bounds.getYWidth();
  float zWidth = bounds.getZWidth();

  //testCenter should be the same as center
  ASSERT_EQ(testCenter[0], center[0]);
  ASSERT_EQ(testCenter[1], center[1]);
  ASSERT_EQ(testCenter[2], center[2]);

  //All widths should be the same as the given width
  ASSERT_EQ(xWidth, width);
  ASSERT_EQ(yWidth, width);
  ASSERT_EQ(zWidth, width);
}

TEST(Bounds, AsymmetricWidthConstructor)
{
  Vector3 center(1,2,3);
  float xW = 1.0f;
  float yW = 2.0f;
  float zW = 3.0f;

  Bounds bounds(center, xW, yW, zW);

  Vector3 testCenter = bounds.getCenter();
  float xWidth = bounds.getXWidth();
  float yWidth = bounds.getYWidth();
  float zWidth = bounds.getZWidth();

  //testCenter should be the same as center
  ASSERT_EQ(testCenter[0], center[0]);
  ASSERT_EQ(testCenter[1], center[1]);
  ASSERT_EQ(testCenter[2], center[2]);

  //All widths should be the same as the given widths
  ASSERT_EQ(xWidth, xW);
  ASSERT_EQ(yWidth, yW);
  ASSERT_EQ(zWidth, zW);
}

TEST(Bounds, MinimumBound)
{
  Vector3 center(1,2,3);

  float xWidth = 2.0f;
  float yWidth = 3.0f;
  float zWidth = 5.0f;

  Bounds bounds(center, xWidth, yWidth, zWidth);

  Vector3 minBoundCalc = Vector3(center.getX() - xWidth / 2,
                                 center.getY() - yWidth / 2,
                                 center.getZ() - zWidth / 2);

  Vector3 minBound = bounds.getMinBound();

  ASSERT_EQ(minBoundCalc[0], minBound[0]);
  ASSERT_EQ(minBoundCalc[1], minBound[1]);
  ASSERT_EQ(minBoundCalc[2], minBound[2]);
}

TEST(Bounds, MaximumBound)
{
  Vector3 center(1,2,3);

  float xWidth = 2.0f;
  float yWidth = 3.0f;
  float zWidth = 5.0f;

  Bounds bounds(center, xWidth, yWidth, zWidth);

  Vector3 maxBoundCalc = Vector3(center.getX() + xWidth / 2,
                                 center.getY() + yWidth / 2,
                                 center.getZ() + zWidth / 2);

  Vector3 maxBound = bounds.getMaxBound();

  ASSERT_EQ(maxBoundCalc[0], maxBound[0]);
  ASSERT_EQ(maxBoundCalc[1], maxBound[1]);
  ASSERT_EQ(maxBoundCalc[2], maxBound[2]);
}

TEST(Bounds, GetPositive)
{
  Vector3 normal = Vector3::Normalize(Vector3(1,2,3));

  //Bounds at 4,5,6 with all widths of 3.0f
  Bounds bounds(Vector3(4,5,6), 3.0f);

  Vector3 minBound = bounds.getMinBound();
  Vector3 maxBound = bounds.getMaxBound();

  Vector3 positiveCalc(minBound);

  if (normal.getX() >= 0)
      positiveCalc.setX(maxBound.getX());
  if (normal.getY() >= 0)
      positiveCalc.setY(maxBound.getY());
  if (normal.getZ() >= 0)
      positiveCalc.setZ(maxBound.getZ());

  Vector3 positive = bounds.getPositive(normal);

  ASSERT_EQ(positiveCalc[0], positive[0]);
  ASSERT_EQ(positiveCalc[1], positive[1]);
  ASSERT_EQ(positiveCalc[2], positive[2]);
}

TEST(Bounds, GetNegative)
{
  Vector3 normal = Vector3::Normalize(Vector3(1,2,3));

  //Bounds at 4,5,6 with all widths of 3.0f
  Bounds bounds(Vector3(4,5,6), 3.0f);

  Vector3 minBound = bounds.getMinBound();
  Vector3 maxBound = bounds.getMaxBound();

  Vector3 negativeCalc(maxBound);

  if (normal.getX() >= 0)
      negativeCalc.setX(minBound.getX());
  if (normal.getY() >= 0)
      negativeCalc.setY(minBound.getY());
  if (normal.getZ() >= 0)
      negativeCalc.setZ(minBound.getZ());

  Vector3 negative = bounds.getNegative(normal);

  ASSERT_EQ(negativeCalc[0], negative[0]);
  ASSERT_EQ(negativeCalc[1], negative[1]);
  ASSERT_EQ(negativeCalc[2], negative[2]);
}

TEST(Bounds, ShouldCollide)
{
  Bounds boundsOne(Vector3(0,0,0), 2.0f);
  Bounds boundsTwo(Vector3(0,0,1.0f), 1.0f);

  ASSERT_TRUE(boundsOne.isCollidingWithBounds(boundsTwo));
}


TEST(Bounds, ShouldNotCollide)
{
  Bounds boundsOne(Vector3(0,0,0), 2.0f);
  Bounds boundsTwo(Vector3(3,3,3), 1.0f);

  ASSERT_FALSE(boundsOne.isCollidingWithBounds(boundsTwo));
}
