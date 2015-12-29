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
