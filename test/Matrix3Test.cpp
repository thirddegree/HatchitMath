#include <gtest/gtest.h>
#include "ht_matrix3.h"
#include <iostream>

using namespace Hatchit;
using namespace Math;

TEST(Matrix3, GetAsArray)
{
    Matrix3 matrix3(1,2,3,4,5,6,7,8,9);
    float* array = matrix3.getAsArray();

    for(int i = 0; i < 9; i++)
      ASSERT_EQ(array[i], i+1);
}

TEST(Matrix3, Inversion)
{
  Matrix3 testMat(1,2,3,3,2,1,2,1,3);
  Matrix3 inversion = testMat.getInverse();

  float* result = (inversion * testMat).getAsArray();
  float* identity = Matrix3().getAsArray();

  // A matrix multiplied by its inverse should be an identity matrix
  for(int i = 0; i < 9; i++)
  {
    // Using ASSERT_NEAR because floating point values aren't exact
    ASSERT_NEAR(result[i], identity[i], 0.0000001f);
  }
}