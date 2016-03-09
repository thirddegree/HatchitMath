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

using namespace Hatchit;
using namespace Math;

TEST(Matrix4, DefaultConstructor)
{
  //Should be an identity matrix
  Matrix4 matrix;

  for(int i = 0; i < 4; i++)
  {
    for(int j = 0; j < 4; j++)
    {
      if(i == j)
        EXPECT_FLOAT_EQ(matrix[i][j], 1);
      else
        EXPECT_FLOAT_EQ(matrix[i][j], 0);
    }
  }
}

TEST(Matrix4, ArrayConstructor)
{
  float array[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};

  Matrix4 matrix(array);

  int index = 0;
  for(int i = 0; i < 4; i++)
  {
    for(int j = 0; j < 4; j++)
    {
        EXPECT_FLOAT_EQ(matrix[i][j], array[index]);
        index++;
    }
  }
}

TEST(Matrix4, FloatConstructor)
{
  Matrix4 matrix(1,2,3,4,
                 5,6,7,8,
                 9,10,11,12,
                 13,14,15,16);

  int value = 0;
  for(int i = 0; i < 4; i++)
  {
    for(int j = 0; j < 4; j++)
    {
        value++;
        EXPECT_FLOAT_EQ(matrix[i][j], value);
    }
  }
}

TEST(Matrix4, Vector3Constructor)
{
  Vector3 row1(1,2,3);
  Vector3 row2(4,5,6);
  Vector3 row3(7,8,9);
  Vector3 row4(10,11,12);

  //Just to easily test in the nested loop
  Vector3 rows[] = {row1, row2, row3, row4};

  /** The resulting matrix fills in a few values so that it will match this
   * layout:
   * 1, 2, 3, 0
   * 4, 5, 6, 0
   * 7, 8, 9, 0
   * 10, 11, 12, 1
   */
  Matrix4 matrix(row1, row2, row3, row4);
  
  for(int i = 0; i < 4; i++)
  {
    Vector3 row = rows[i];
    for(int j = 0; j < 4; j++)
    {
      //Special cases when testing the last column
      if(j == 3 && i == 3)
        EXPECT_FLOAT_EQ(matrix[i][j], 1);
      else if(j == 3)
        EXPECT_FLOAT_EQ(matrix[i][j], 0);
      else
        EXPECT_FLOAT_EQ(matrix[i][j], row[j]);
    }
  }
}

TEST(Matrix4, Vector4Constructor)
{
  Vector4 row1(1,2,3,4);
  Vector4 row2(5,6,7,8);
  Vector4 row3(9,10,11,12);
  Vector4 row4(13,14,15,16);

  //Just to easily test in the nested loop
  Vector4 rows[] = {row1, row2, row3, row4};

  Matrix4 matrix(row1, row2, row3,row4);
  
  for(int i = 0; i < 4; i++)
  {
    Vector4 row = rows[i];
    for(int j = 0; j < 4; j++)
        EXPECT_FLOAT_EQ(matrix[i][j], row[j]);
  }
}

TEST(Matrix4, Transposition)
{
  Matrix4 matrix(1,2,3,4,
                 4,3,2,1,
                 3,2,4,1,
                 3,1,4,2);
  Matrix4 transpose = MMMatrixTranspose(matrix);

  //Result taken from wolfram alpha
  //http://www.wolframalpha.com/input/?i=matrix+transpose&a=*C.matrix+transpose-_*Calculator.dflt-&f2={{1%2C2%2C3%2C4}%2C{4%2C3%2C2%2C1}%2C{3%2C2%2C4%2C1}%2C{3%2C1%2C4%2C2}}&f=MatrixOperations.theMatrix_{{1%2C2%2C3%2C4}%2C{4%2C3%2C2%2C1}%2C{3%2C2%2C4%2C1}%2C{3%2C1%2C4%2C2}}
  EXPECT_FLOAT_EQ(transpose[0][0], 1);
  EXPECT_FLOAT_EQ(transpose[0][1], 4);
  EXPECT_FLOAT_EQ(transpose[0][2], 3);
  EXPECT_FLOAT_EQ(transpose[0][3], 3);

  EXPECT_FLOAT_EQ(transpose[1][0], 2);
  EXPECT_FLOAT_EQ(transpose[1][1], 3);
  EXPECT_FLOAT_EQ(transpose[1][2], 2);
  EXPECT_FLOAT_EQ(transpose[1][3], 1);

  EXPECT_FLOAT_EQ(transpose[2][0], 3);
  EXPECT_FLOAT_EQ(transpose[2][1], 2);
  EXPECT_FLOAT_EQ(transpose[2][2], 4);
  EXPECT_FLOAT_EQ(transpose[2][3], 4);

  EXPECT_FLOAT_EQ(transpose[3][0], 4);
  EXPECT_FLOAT_EQ(transpose[3][1], 1);
  EXPECT_FLOAT_EQ(transpose[3][2], 1);
  EXPECT_FLOAT_EQ(transpose[3][3], 2);
}

TEST(Matrix4, Inversion)
{
  Matrix4 matrix(1,2,3,4,
                 4,3,2,1,
                 3,2,4,1,
                 3,1,4,2);
  Matrix4 inversion = MMMatrixInverse(matrix);

  float* result = (inversion * matrix).data;
  float* identity = Matrix4().data;

  // A matrix multiplied by its inverse should be an identity matrix
  for(int i = 0; i < 16; i++)
  {
    // Using ASSERT_NEAR because floating point values aren't exact
    ASSERT_NEAR(result[i], identity[i], 0.0002f);
  }
}

TEST(Matrix4, Matrix4MultiplicationOperator)
{
  Matrix4 mat1(1,2,3,4,
               4,3,2,1,
               3,2,4,1,
               3,1,4,2);
  Matrix4 mat2(4,5,6,7,
               7,6,5,4,
               6,5,7,4,
               6,4,7,5);

  Matrix4 result = mat1 * mat2;

  EXPECT_FLOAT_EQ(result[0][0], 60);
  EXPECT_FLOAT_EQ(result[0][1], 48);
  EXPECT_FLOAT_EQ(result[0][2], 65);
  EXPECT_FLOAT_EQ(result[0][3], 47);

  EXPECT_FLOAT_EQ(result[1][0], 55);
  EXPECT_FLOAT_EQ(result[1][1], 52);
  EXPECT_FLOAT_EQ(result[1][2], 60);
  EXPECT_FLOAT_EQ(result[1][3], 53);

  EXPECT_FLOAT_EQ(result[2][0], 56);
  EXPECT_FLOAT_EQ(result[2][1], 51);
  EXPECT_FLOAT_EQ(result[2][2], 63);
  EXPECT_FLOAT_EQ(result[2][3], 50);

  EXPECT_FLOAT_EQ(result[3][0], 55);
  EXPECT_FLOAT_EQ(result[3][1], 49);
  EXPECT_FLOAT_EQ(result[3][2], 65);
  EXPECT_FLOAT_EQ(result[3][3], 51);
}

TEST(Matrix4, Vector4MultiplicationOperator)
{
  Matrix4 matrix(1,2,3,4,
                 4,3,2,1,
                 3,2,4,1,
                 3,1,4,2);
  Vector4 vector(1,2,3,4);

  Vector4 result = matrix * vector;

  EXPECT_FLOAT_EQ(result[0], 30);
  EXPECT_FLOAT_EQ(result[1], 20);
  EXPECT_FLOAT_EQ(result[2], 23);
  EXPECT_FLOAT_EQ(result[3], 25);
}

TEST(Matrix4Static, OrthographicProjection)
{
  float left = -50;
  float right = 50;
  float bottom = -25;
  float top = 25;
  float _near = 0.1f;
  float _far = 100;

  Matrix4 ortho = MMMatrixOrthoProj(left, right, bottom, top, _near, _far);

  ASSERT_NEAR(ortho[0][0], 0.02f, 0.00001f);
  ASSERT_NEAR(ortho[0][1], 0.0f, 0.00001f);
  ASSERT_NEAR(ortho[0][2], 0.0f, 0.00001f);
  ASSERT_NEAR(ortho[0][3], 0.0f, 0.00001f);

  ASSERT_NEAR(ortho[1][0], 0.0f, 0.00001f);
  ASSERT_NEAR(ortho[1][1], 0.04f, 0.00001f);
  ASSERT_NEAR(ortho[1][2], 0.0f, 0.00001f);
  ASSERT_NEAR(ortho[1][3], 0.0f, 0.00001f);

  ASSERT_NEAR(ortho[2][0], 0.0f, 0.00001f);
  ASSERT_NEAR(ortho[2][1], 0.0f, 0.00001f);
  ASSERT_NEAR(ortho[2][2], -0.02002f, 0.00001f);
  ASSERT_NEAR(ortho[2][3], 0.0f, 0.00001f);

  ASSERT_NEAR(ortho[3][0], 0.0f, 0.00001f);
  ASSERT_NEAR(ortho[3][1], 0.0f, 0.00001f);
  ASSERT_NEAR(ortho[3][2], -1.002002f, 0.00001f);
  ASSERT_NEAR(ortho[3][3], 1.0f, 0.00001f);
}

TEST(Matrix4Static, GetPerspectiveProjection)
{
  float fov = HalfPi;
  float width = 16.0f;
  float height = 9.0f;
  float _near = 0.1f;
  float _far = 100.0f;

  Matrix4 persp = MMMatrixPerspProj(fov, width, height, _near, _far);

  EXPECT_FLOAT_EQ(persp[0][0], 0.5625f);
  EXPECT_FLOAT_EQ(persp[0][1], 0.0f);
  EXPECT_FLOAT_EQ(persp[0][2], 0.0f);
  EXPECT_FLOAT_EQ(persp[0][3], 0.0f);

  EXPECT_FLOAT_EQ(persp[1][0], 0.0f);
  EXPECT_FLOAT_EQ(persp[1][1], 1.0f);
  EXPECT_FLOAT_EQ(persp[1][2], 0.0f);
  EXPECT_FLOAT_EQ(persp[1][3], 0.0f);

  EXPECT_FLOAT_EQ(persp[2][0], 0.0f);
  EXPECT_FLOAT_EQ(persp[2][1], 0.0f);
  EXPECT_FLOAT_EQ(persp[2][2], -1.002002f);
  EXPECT_FLOAT_EQ(persp[2][3], -0.2002002f);

  EXPECT_FLOAT_EQ(persp[3][0], 0.0f);
  EXPECT_FLOAT_EQ(persp[3][1], 0.0f);
  EXPECT_FLOAT_EQ(persp[3][2], -1.0f);
  EXPECT_FLOAT_EQ(persp[3][3], 0.0f);
}

TEST(Matrix4Static, GetLookAtView)
{
  Vector3 eye(5.f, 10.f, 15.f);
  Vector3 target(15.f, 15.f, 15.f);
  Vector3 up(0.f, 1.f, 0.f);

  Matrix4 lookAt = MMMatrixLookAt(eye, target, up);

  EXPECT_FLOAT_EQ(lookAt[0][0], 0.f);
  EXPECT_FLOAT_EQ(lookAt[0][1], 0.f);
  EXPECT_FLOAT_EQ(lookAt[0][2], -1.f);
  EXPECT_FLOAT_EQ(lookAt[0][3], 15.f);

  EXPECT_FLOAT_EQ(lookAt[1][0], -0.447213590f);
  EXPECT_FLOAT_EQ(lookAt[1][1], 0.894427180f);
  EXPECT_FLOAT_EQ(lookAt[1][2], 0.f);
  EXPECT_FLOAT_EQ(lookAt[1][3], -6.70820427f);

  EXPECT_FLOAT_EQ(lookAt[2][0], -0.894427180f);
  EXPECT_FLOAT_EQ(lookAt[2][1], -0.447213590f);
  EXPECT_FLOAT_EQ(lookAt[2][2], 0.f);
  EXPECT_FLOAT_EQ(lookAt[2][3], 8.94427204f);

  EXPECT_FLOAT_EQ(lookAt[3][0], 0.f);
  EXPECT_FLOAT_EQ(lookAt[3][1], 0.f);
  EXPECT_FLOAT_EQ(lookAt[3][2], 0.f);
  EXPECT_FLOAT_EQ(lookAt[3][3], 1.0f);
}
