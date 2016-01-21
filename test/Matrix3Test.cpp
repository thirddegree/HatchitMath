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
#include "ht_matrix3.h"
#include "ht_matrix4.h"

using namespace Hatchit;
using namespace Math;

TEST(Matrix3, DefaultConstructor)
{
  //Should be an identity matrix
  Matrix3 matrix;

  for(int i = 0; i < 3; i++)
  {
    for(int j = 0; j < 3; j++)
    {
      if(i == j)
        ASSERT_EQ(matrix[i][j], 1);
      else
        ASSERT_EQ(matrix[i][j], 0);
    }
  }
}

TEST(Matrix3, ArrayConstructor)
{
  float array[] = {1,2,3,4,5,6,7,8,9};

  Matrix3 matrix(array);

  int index = 0;
  for(int i = 0; i < 3; i++)
  {
    for(int j = 0; j < 3; j++)
    {
        ASSERT_EQ(matrix[i][j], array[index]);
        index++;
    }
  }
}

TEST(Matrix3, FloatConstructor)
{
  Matrix3 matrix(1,2,3,4,5,6,7,8,9);

  int value = 0;
  for(int i = 0; i < 3; i++)
  {
    for(int j = 0; j < 3; j++)
    {
        value++;
        ASSERT_EQ(matrix[i][j], value);
    }
  }
}

TEST(Matrix3, Vector3Constructor)
{
  Vector3 row1(1,2,3);
  Vector3 row2(4,5,6);
  Vector3 row3(7,8,9);

  //Just to easily test in the nested loop
  Vector3 rows[] = {row1, row2, row3};

  Matrix3 matrix(row1, row2, row3);

  for(int i = 0; i < 3; i++)
  {
    Vector3 row = rows[i];
    for(int j = 0; j < 3; j++)
        ASSERT_EQ(matrix[i][j], row[j]);
  }

}

TEST(Matrix3, Transposition)
{
  Matrix3 matrix(1,2,3,3,2,1,2,1,3);
  Matrix3 transpose = matrix.getTranspose();

  //Result taken from wolfram alpha
  ASSERT_EQ(transpose[0][0], 1);
  ASSERT_EQ(transpose[0][1], 3);
  ASSERT_EQ(transpose[0][2], 2);

  ASSERT_EQ(transpose[1][0], 2);
  ASSERT_EQ(transpose[1][1], 2);
  ASSERT_EQ(transpose[1][2], 1);

  ASSERT_EQ(transpose[2][0], 3);
  ASSERT_EQ(transpose[2][1], 1);
  ASSERT_EQ(transpose[2][2], 3);
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

TEST(Matrix3, GetAsArray)
{
    Matrix3 matrix3(1,2,3,4,5,6,7,8,9);
    float* array = matrix3.getAsArray();

    for(int i = 0; i < 9; i++)
      ASSERT_EQ(array[i], i+1);
}

TEST(Matrix3, Matrix3MultiplicationOperator)
{
  //This is an example problem from wolfram alpha
  Matrix3 mat1(1,2,3,3,2,1,2,1,3);
  Matrix3 mat2(4,5,6,6,5,4,4,6,5);

  Matrix3 result = mat1 * mat2;

  ASSERT_EQ(result[0][0], 28);
  ASSERT_EQ(result[0][1], 33);
  ASSERT_EQ(result[0][2], 29);

  ASSERT_EQ(result[1][0], 28);
  ASSERT_EQ(result[1][1], 31);
  ASSERT_EQ(result[1][2], 31);

  ASSERT_EQ(result[2][0], 26);
  ASSERT_EQ(result[2][1], 33);
  ASSERT_EQ(result[2][2], 31);
}

TEST(Matrix3, Vector3MultiplicationOperator)
{
  Matrix3 matrix(1,2,3,3,2,1,2,1,3);
  Vector3 vector(1,2,3);

  //Another good ol test from Wolfram alpha
  Vector3 result = matrix * vector;

  ASSERT_EQ(result[0], 14);
  ASSERT_EQ(result[1], 10);
  ASSERT_EQ(result[2], 13);
}

TEST(Matrix3, Matrix4ConversionOperator)
{
  Matrix3 matrix(0,1,2,3,4,5,6,7,8);
  Matrix4 result = (Matrix4)matrix;

  int value = 0;
  for(int i = 0; i < 4; i++)
  {
    for(int j = 0; j < 4; j++)
    {
      if(i == 3 && j == 3)
      {
        ASSERT_EQ(result[i][j], 1);
      }
      else if(i == 3 || j == 3)
      {
        ASSERT_EQ(result[i][j], 0);
      }
      else
      {
        ASSERT_EQ(result[i][j], value);
        value++;
      }
    }
  }
}
