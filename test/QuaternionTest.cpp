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
#include "ht_math.h"
#include <random>

using namespace Hatchit;
using namespace Math;

float GenerateRandomFloat(float min, float max)
{
	static std::random_device randomDevice;
	static std::mt19937 generator(randomDevice());
	std::uniform_real_distribution<float> distributor(min, max);
	return distributor(generator);
}

TEST(Quaternion, DefaultConstructorCreatesIdentityQuaternion)
{
  Quaternion quat;

  EXPECT_FLOAT_EQ(quat.w, 1);
  EXPECT_FLOAT_EQ(quat.x, 0);
  EXPECT_FLOAT_EQ(quat.y, 0);
  EXPECT_FLOAT_EQ(quat.z, 0);
}

TEST(Quaternion, ParamaterizedFloatConstructorCreatesAppropriateQuaternion)
{
  Quaternion quat(3,2,1,4);

  EXPECT_FLOAT_EQ(quat.w, 4);
  EXPECT_FLOAT_EQ(quat.x, 3);
  EXPECT_FLOAT_EQ(quat.y, 2);
  EXPECT_FLOAT_EQ(quat.z, 1);
}

TEST(Quaternion, AxisAngleConstructorCreatesAppropriateQuaternion)
{
	//Based off: http://www.euclideanspace.com/maths/geometry/rotations/conversions/angleToQuaternion/

	float angle = HalfPi; //90 degrees
	Vector3 axis = Vector3(1.f, 0.f, 0.f);

	Quaternion quat(axis, angle);

	EXPECT_FLOAT_EQ(quat.w, 0.7071f);
	EXPECT_FLOAT_EQ(quat.x, 0.7071f);
	EXPECT_FLOAT_EQ(quat.y, 0.0f);
	EXPECT_FLOAT_EQ(quat.z, 0.0f);
}

TEST(Quaterion, EulerAnglesConstructorCreatesAppropriateQuaternion)
{
  //90 deg x, 0 deg y, 90 deg z
  //Vector3 euler(M_PI/2,0,M_PI/2);
  Quaternion quat(HalfPi, 0, HalfPi);

  EXPECT_FLOAT_EQ(quat.w, .5f);
  EXPECT_FLOAT_EQ(quat.x, .5f);
  EXPECT_FLOAT_EQ(quat.y, .5f);
  EXPECT_FLOAT_EQ(quat.z, .5f);
}

TEST(Quaternion, ExistingM128ConstructorCreatesAppropriateQuaternion)
{
	__m128 data = MMVectorSet(1.f, 2.f, 3.f, 4.f);
	
	Quaternion quat(data);

	EXPECT_FLOAT_EQ(quat.w, 4.f);
	EXPECT_FLOAT_EQ(quat.x, 1.f);
	EXPECT_FLOAT_EQ(quat.y, 2.f);
	EXPECT_FLOAT_EQ(quat.z, 3.f);
}

TEST(Quaternion, EqualityOperatorReturnsTrueOnEqualQuats)
{
	Quaternion quatA(0.f, 1.f, 0.f, 0.f);
	Quaternion quatB(0.f, 1.f, 0.f, 0.f);

	ASSERT_EQ(quatA == quatB, true);
}

TEST(Quaternion, EqualityOperatorReturnsFalseOnNonEqualQuats)
{
	Quaternion quatA(0.f, 1.f, 0.f, 0.f);
	Quaternion quatB(1.f, 0.f, 0.f, 0.f);

	ASSERT_EQ(quatA == quatB, false);
}

TEST(Quaternion, NonEqualityOperatorReturnsTrueOnNonEqualQuats)
{
	Quaternion quatA(0.f, 1.f, 0.f, 0.f);
	Quaternion quatB(1.f, 0.f, 0.f, 0.f);

	ASSERT_EQ(quatA != quatB, true);
}

TEST(Quaternion, NonEqualityOperatorReturnsFalseOnEqualQuats)
{
	Quaternion quatA(0.f, 1.f, 0.f, 0.f);
	Quaternion quatB(0.f, 1.f, 0.f, 0.f);

	ASSERT_EQ(quatA != quatB, false);
}

TEST(Quaternion, AdditionAddsQuaternionsAppropriately)
{
	float valueArray[8];
	for (size_t i = 0; i < 8; ++i)
	{
		valueArray[i] = GenerateRandomFloat(0.f, 1.f);
	}
	float expectedArray[4];
	for (size_t i = 0; i < 4; ++i)
	{
		expectedArray[i] = valueArray[i] + valueArray[i + 4];
	}
	Quaternion quatA(valueArray[0], valueArray[1], valueArray[2], valueArray[3]);
	Quaternion quatB(valueArray[4], valueArray[5], valueArray[6], valueArray[7]);

	Quaternion actualQuat = quatA + quatB;

	EXPECT_FLOAT_EQ(actualQuat.w, expectedArray[3]);
	EXPECT_FLOAT_EQ(actualQuat.x, expectedArray[0]);
	EXPECT_FLOAT_EQ(actualQuat.y, expectedArray[1]);
	EXPECT_FLOAT_EQ(actualQuat.z, expectedArray[2]);
}

TEST(Quaternion, SubtractionSubtractsQuaternionsAppropriately)
{
	float valueArray[8];
	for (size_t i = 0; i < 8; ++i)
	{
		valueArray[i] = GenerateRandomFloat(0.f, 1.f);
	}
	float expectedArray[4];
	for (size_t i = 0; i < 4; ++i)
	{
		expectedArray[i] = valueArray[i] - valueArray[i + 4];
	}
	Quaternion quatA(valueArray[0], valueArray[1], valueArray[2], valueArray[3]);
	Quaternion quatB(valueArray[4], valueArray[5], valueArray[6], valueArray[7]);

	Quaternion actualQuat = quatA - quatB;

	EXPECT_FLOAT_EQ(actualQuat.w, expectedArray[3]);
	EXPECT_FLOAT_EQ(actualQuat.x, expectedArray[0]);
	EXPECT_FLOAT_EQ(actualQuat.y, expectedArray[1]);
	EXPECT_FLOAT_EQ(actualQuat.z, expectedArray[2]);
}

TEST(Quaternion, MultiplicationReturnsAppropriateQuaternion)
{
	float valueArray[8];
	for (size_t i = 0; i < 8; ++i)
	{
		valueArray[i] = GenerateRandomFloat(0.f, 1.f);
	}
	float expectedArray[4];
	expectedArray[3] = valueArray[3] * valueArray[7] - valueArray[0] * valueArray[4] - valueArray[1] * valueArray[5] - valueArray[2] * valueArray[6];
	expectedArray[0] = valueArray[3] * valueArray[4] + valueArray[0] * valueArray[7] + valueArray[1] * valueArray[6] - valueArray[2] * valueArray[5];
	expectedArray[1] = valueArray[3] * valueArray[5] - valueArray[0] * valueArray[6] + valueArray[1] * valueArray[7] + valueArray[2] * valueArray[4];
	expectedArray[2] = valueArray[3] * valueArray[6] + valueArray[0] * valueArray[5] - valueArray[1] * valueArray[4] + valueArray[2] * valueArray[7];

	Quaternion quatA(valueArray[0], valueArray[1], valueArray[2], valueArray[3]);
	Quaternion quatB(valueArray[4], valueArray[5], valueArray[6], valueArray[7]);

	Quaternion actualQuat = quatA * quatB;

	EXPECT_FLOAT_EQ(actualQuat.w, expectedArray[3]);
	EXPECT_FLOAT_EQ(actualQuat.x, expectedArray[0]);
	EXPECT_FLOAT_EQ(actualQuat.y, expectedArray[1]);
	EXPECT_FLOAT_EQ(actualQuat.z, expectedArray[2]);
}

TEST(Quaternion, AddEqualsModifiesQuaternionAppropriately)
{
	float valueArray[8];
	for (size_t i = 0; i < 8; ++i)
	{
		valueArray[i] = GenerateRandomFloat(0.f, 1.f);
	}
	float expectedArray[4];
	for (size_t i = 0; i < 4; ++i)
	{
		expectedArray[i] = valueArray[i] + valueArray[i + 4];
	}
	Quaternion quatA = Quaternion(valueArray[0], valueArray[1], valueArray[2], valueArray[3]);
	Quaternion quatB = Quaternion(valueArray[4], valueArray[5], valueArray[6], valueArray[7]);

	quatA += quatB;

	EXPECT_FLOAT_EQ(quatA.w, expectedArray[3]);
	EXPECT_FLOAT_EQ(quatA.x, expectedArray[0]);
	EXPECT_FLOAT_EQ(quatA.y, expectedArray[1]);
	EXPECT_FLOAT_EQ(quatA.z, expectedArray[2]);
}

TEST(Quaternion, SubtractEqualsModifiesQuaternionAppropriately)
{
	float valueArray[8];
	for (size_t i = 0; i < 8; ++i)
	{
		valueArray[i] = GenerateRandomFloat(0.f, 1.f);
	}
	float expectedArray[4];
	for (size_t i = 0; i < 4; ++i)
	{
		expectedArray[i] = valueArray[i] - valueArray[i + 4];
	}
	Quaternion quatA(valueArray[0], valueArray[1], valueArray[2], valueArray[3]);
	Quaternion quatB(valueArray[4], valueArray[5], valueArray[6], valueArray[7]);

	quatA -= quatB;

	EXPECT_FLOAT_EQ(quatA.w, expectedArray[3]);
	EXPECT_FLOAT_EQ(quatA.x, expectedArray[0]);
	EXPECT_FLOAT_EQ(quatA.y, expectedArray[1]);
	EXPECT_FLOAT_EQ(quatA.z, expectedArray[2]);
}

TEST(Quaternion, MultiplyEqualsModifiesQuaternionAppropriately)
{
	float valueArray[8];
	for (size_t i = 0; i < 8; ++i)
	{
		valueArray[i] = GenerateRandomFloat(0.f, 1.f);
	}
	float expectedArray[4];
	expectedArray[3] = valueArray[3] * valueArray[7] - valueArray[0] * valueArray[4] - valueArray[1] * valueArray[5] - valueArray[2] * valueArray[6];
	expectedArray[0] = valueArray[3] * valueArray[4] + valueArray[0] * valueArray[7] + valueArray[1] * valueArray[6] - valueArray[2] * valueArray[5];
	expectedArray[1] = valueArray[3] * valueArray[5] - valueArray[0] * valueArray[6] + valueArray[1] * valueArray[7] + valueArray[2] * valueArray[4];
	expectedArray[2] = valueArray[3] * valueArray[6] + valueArray[0] * valueArray[5] - valueArray[1] * valueArray[4] + valueArray[2] * valueArray[7];

	Quaternion quatA = Quaternion(valueArray[0], valueArray[1], valueArray[2], valueArray[3]);
	Quaternion quatB = Quaternion(valueArray[4], valueArray[5], valueArray[6], valueArray[7]);

	quatA *= quatB;

	EXPECT_FLOAT_EQ(quatA.w, expectedArray[3]);
	EXPECT_FLOAT_EQ(quatA.x, expectedArray[0]);
	EXPECT_FLOAT_EQ(quatA.y, expectedArray[1]);
	EXPECT_FLOAT_EQ(quatA.z, expectedArray[2]);
}

TEST(Quaternion, ConversionOperatorReturnsInternalM128InExpectedOrder)
{
	float valueArray[4];
	for (size_t i = 0; i < 4; ++i)
	{
		valueArray[i] = GenerateRandomFloat(0.f, 1.f);
	}
	Quaternion quatA = Quaternion(valueArray[0], valueArray[1], valueArray[2], valueArray[3]);

	__m128 result = static_cast<__m128>(quatA);

	float actualArray[4];
	_mm_store_ps(actualArray, result);
	for (size_t i = 0; i < 4; ++i)
	{
		EXPECT_FLOAT_EQ(actualArray[i], valueArray[i]);
	}
}

TEST(Quaternion, DotProductReturnsExpectedValue)
{
	float valueArray[8];
	for (size_t i = 0; i < 8; ++i)
	{
		valueArray[i] = GenerateRandomFloat(0.f, 1.f);
	}
	float expectedResult = valueArray[0] * valueArray[4] + valueArray[1] * valueArray[5] + valueArray[2] * valueArray[6] + valueArray[3] * valueArray[7];

	Quaternion quatA = Quaternion(valueArray[0], valueArray[1], valueArray[2], valueArray[3]);
	Quaternion quatB = Quaternion(valueArray[4], valueArray[5], valueArray[6], valueArray[7]);

	float actualResult = MMQuaternionDot(quatA, quatB);

	EXPECT_FLOAT_EQ(actualResult, expectedResult);
}

TEST(Quaternion, NormalizeReturnsNormalizedQuaternion)
{
	float valueArray[4];
	for (size_t i = 0; i < 4; ++i)
	{
		valueArray[i] = GenerateRandomFloat(0.f, 1.f);
	}
	valueArray[1] = 0.5f; //To assure quaternion passed in does not have magnitude of 0
	//Calculate expected result
	float expectedArray[4];
	float magnitude = sqrtf(valueArray[0] * valueArray[0] + valueArray[1] * valueArray[1] + valueArray[2] * valueArray[2] + valueArray[3] * valueArray[3]);
	for (size_t i = 0; i < 4; ++i)
	{
		expectedArray[i] = valueArray[i] / magnitude;
	}

	Quaternion quat = Quaternion(valueArray[0], valueArray[1], valueArray[2], valueArray[3]);

	Quaternion actualQuat = MMQuaternionNormalize(quat);

	EXPECT_FLOAT_EQ(actualQuat.w, expectedArray[3]);
	EXPECT_FLOAT_EQ(actualQuat.x, expectedArray[0]);
	EXPECT_FLOAT_EQ(actualQuat.y, expectedArray[1]);
	EXPECT_FLOAT_EQ(actualQuat.z, expectedArray[2]);
}

#if !defined(NDEBUG)
TEST(Quaternion, NormalizingZeroQuaternionAsserts)
{
	Quaternion quat(0.f, 0.f, 0.f, 0.f);

	ASSERT_DEATH(Quaternion actualQuat = MMQuaternionNormalize(quat));
}
#else
TEST(Quaternion, NormalizingAZeroQuaternionDoesntCrash)
{
	Quaternion quat(0.f, 0.f, 0.f, 0.f);

	Quaternion actualQuat = MMQuaternionNormalize(quat);

	//Woot woot, we pass
}
#endif

TEST(Quaternion, MagnitudeReturnsAppropriateValue)
{
	float valueArray[4];
	for (size_t i = 0; i < 4; ++i)
	{
		valueArray[i] = GenerateRandomFloat(0.f, 1.f);
	}
	Quaternion quat = Quaternion(valueArray[0], valueArray[1], valueArray[2], valueArray[3]);

	float expectedResult = sqrtf(valueArray[0] * valueArray[0] + valueArray[1] * valueArray[1] + valueArray[2] * valueArray[2] + valueArray[3] * valueArray[3]);

	float actualResult = MMQuaternionMagnitude(quat);

	EXPECT_FLOAT_EQ(actualResult, expectedResult);
}

TEST(Quaternion, SquareMagnitudeReturnsAppropriateValue)
{
	float valueArray[4];
	for (size_t i = 0; i < 4; ++i)
	{
		valueArray[i] = GenerateRandomFloat(0.f, 1.f);
	}
	Quaternion quat = Quaternion(valueArray[0], valueArray[1], valueArray[2], valueArray[3]);

	float expectedResult = valueArray[0] * valueArray[0] + valueArray[1] * valueArray[1] + valueArray[2] * valueArray[2] + valueArray[3] * valueArray[3];

	float actualResult = MMQuaternionMagnitudeSqr(quat);

	EXPECT_FLOAT_EQ(actualResult, expectedResult);
}

TEST(Quaternion, ConjugateReturnsAppropriateQuaternion)
{
	float valueArray[4];
	for (size_t i = 0; i < 4; ++i)
	{
		valueArray[i] = GenerateRandomFloat(0.f, 1.f);
	}
	float expectedArray[4];
	expectedArray[3] = valueArray[3];
	for (size_t i = 0; i < 3; ++i)
	{
		expectedArray[i] = -valueArray[3];
	}
	Quaternion quat = Quaternion(valueArray[0], valueArray[1], valueArray[2], valueArray[3]);

	Quaternion actualQuat = MMQuaternionConjugate(quat);

	EXPECT_FLOAT_EQ(actualQuat.w, expectedArray[3]);
	EXPECT_FLOAT_EQ(actualQuat.x, expectedArray[0]);
	EXPECT_FLOAT_EQ(actualQuat.y, expectedArray[1]);
	EXPECT_FLOAT_EQ(actualQuat.z, expectedArray[2]);
}
