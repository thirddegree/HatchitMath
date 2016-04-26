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

#pragma once
#include <ht_math.h>

namespace Hatchit {

    namespace Math {

        /**
        * \fn constexpr inline float Absf(float x)
        * \brief Returns the absolute falue of x
        *   
        *   Returns the absolute value of x
        *   
        * \return The absolute value of x
        */
        constexpr inline float _MM_CALLCONV Absf(float x)
        {
            return (x < 0) ? x * -1 : x;
        }

        /**
        * \fn constexpr inline double Abs(double x)
        * \brief Returns the absolute value of x
        *   
        *   Returns the absolute value of x
        *
        * \return The absolute value of x
        */
        constexpr inline double _MM_CALLCONV Abs(double x)
        {
            return (x < 0) ? x * -1 : x;
        }

        /**
        * \fn constexpr inline float Minf(float x, float y)
        * \brief Returns the minimum value between x & y
        *
        *   Returns the minimum value between x & y
        *
        * \return The minimum value between x & y
        */
        constexpr inline float _MM_CALLCONV Minf(float x, float y)
        {
            return (x < y) ? x : y;
        }

        /**
        * \fn constexpr inline double Min(double x, double y)
        * \brief Returns the minimum value between x & y
        *   
        *   Returns the minimum value between x & y
        *
        * \return The minimum value between x & y
        */
        constexpr inline double _MM_CALLCONV Min(double x, double y)
        {
            return (x < y) ? x : y;
        }

        /**
        * \fn constexpr inline float Maxf(float x, float y)
        * \brief Returns the maximum value between x & y
        *
        *   Returns the maximum value between x & y
        *
        * \return The maximum value between x & y
        */
        constexpr inline float _MM_CALLCONV Maxf(float x, float y)
        {
            return (x > y) ? x : y;
        }

        /**
        * \fn constexpr inline double Max(double x, double y)
        * \brief Returns the maxmimum value between x & y
        *
        *   Returns the maxmimum value between x & y
        *
        * \return The maximum value between x & y
        */
        constexpr inline double _MM_CALLCONV Max(double x, double y)
        {
            return (x > y) ? x : y;
        }
        
        /**
        * \fn constexpr inline float Clampf(float num, float min, float max)
        * \brief Clamps the value num between min & max and returns value of the clamp
        *
        *   Returns min if num < min, max if num > max, or num itself if num is within specified the bounds
        *
        * \return The value of num clamped between min and max
        */
        constexpr inline float _MM_CALLCONV Clampf(float num, float min, float max)
        {
            return (num < min) ? min : (num > max) ? max : num;
        }

        /**
        * \fn constexpr inline double Clamp(double num, double min, double max)
        * \brief Clamps the value num between min & max and returns value of the clamp
        *
        *   Returns min if num < min, max if num > max, or num itself if num is within the specified bounds
        *
        * \return The value of num clamped between min and max
        */
        constexpr inline double _MM_CALLCONV Clamp(double num, double min, double max)
        {
            return (num < min) ? min : (num > max) ? max : num;
        }

        /**
        * \fn constexpr inline int32_t Floorf(float num)
        * \brief Calculates the closest whole number int32_t less than num
        *
        *   Calculates the closest whole number int32_t less than num
        *
        * \return The closest whole number int32_t less than num
        */
        constexpr inline int32_t _MM_CALLCONV Floorf(float num)
        {
            return (num == static_cast<int32_t>(num)) ? static_cast<int32_t>(num) : (num > 0) ? static_cast<int32_t>(num) : static_cast<int32_t>(num) - 1;
        }

        /**
        * \fn constexpr inline int64_t Floor(double num)
        * \brief Calculates the closest whole number int64_t less than num
        *
        *   Calculates the closest whole number int64_t less than num
        *
        * \return The closest whole number int64_t less than num
        */
        constexpr inline int64_t _MM_CALLCONV Floor(double num)
        {
            return (num == static_cast<int64_t>(num)) ? static_cast<int64_t>(num) : (num > 0) ? static_cast<int64_t>(num) : static_cast<int64_t>(num) - 1;
        }

        /**
        * \fn constexpr inline int32_t Ceilingf(float num)
        * \brief Calculates the closest whole number int32_t greater than num
        *
        *   Calculates the closest whole number int32_t greater than num
        *
        * \return The closest whole number int32_t greater than num
        */
        constexpr inline int32_t _MM_CALLCONV Ceilingf(float num)
        {
            return (num == static_cast<int32_t>(num)) ? static_cast<int32_t>(num) : (num > 0) ? static_cast<int32_t>(num) + 1 : static_cast<int32_t>(num);
        }

        /**
        * \fn constexpr inline int64_t Ceiling(double num)
        * \brief Calculates the closest whole number int64_t greater than num
        *
        *   Calculates the closest whole number int64_t greater than num
        *
        * \return The closest whole number int64_t greater than num
        */
        constexpr inline int64_t _MM_CALLCONV Ceiling(double num)
        {
            return (num == static_cast<int64_t>(num)) ? static_cast<int64_t>(num) : (num > 0) ? static_cast<int64_t>(num) + 1 : static_cast<int64_t>(num);
        }

        /**
        * \fn constexpr inline int32_t Roundf(float num)
        * \brief Calculates the value of num rounded to the nearest whole number int32_t
        *
        *   Calculates the value of num rounded to the nearest whole number int32_t
        *
        * \return  Num rounded to the nearest whole number int32_t
        */
        constexpr inline int32_t _MM_CALLCONV Roundf(float num)
        {
            return (num - Floorf(num) >= 0.5f) ? Ceilingf(num) : Floorf(num);
        }

        /**
        * \fn constexpr inline int64_t Round(double num)
        * \brief Calculates the value of num rounded to the nearest whole number int32_t
        *
        *   Calculates the value of num rounded to the nearest whole number int32_t
        *
        * \return  Num rounded to the nearest whole number int32_t
        */
        constexpr inline int64_t _MM_CALLCONV Round(double num)
        {
            return (num - Floor(num) >= 0.5f) ? Ceiling(num) : Floor(num);
        }

        /**
        * \fn constexpr inline float PowfRecursive(float num, int pow, float base)
        * \brief Helper function for Powf(float num, int pow)
        *
        *   Recursively calculates the value of num to the pow power using base as a multiplier
        *
        * \return  The value of num to the pow power
        */
        constexpr inline float _MM_CALLCONV PowfRecursive(float num, int pow, float base)
        {
            return (pow > 0) ? 
                (pow >  1) ? PowfRecursive(num * base, pow - 1, base) : num : 
                (pow < -1) ? PowfRecursive(num * base, pow + 1, base) : 1 / num;
        }

        /**
        * \fn constexpr inline float Powf(float num, int pow)
        * \brief Calculates the value of num to the pow power
        *
        *   Calculates the value of num to the pow power
        *
        * \return  The value of num to the pow power
        */
        constexpr inline float _MM_CALLCONV Powf(float num, int pow)
        {
            return (pow == 0) ? 1.0f : PowfRecursive(num, pow, num);
        }

        /**
        * \fn constexpr inline double PowRecursive(double num, int pow, double base)
        * \brief Helper function for Pow(double num, int pow)
        *
        *   Recursively calculates the value of num to the pow power using base as a multiplier
        *
        * \return  The value of num to the pow power
        */
        constexpr inline double _MM_CALLCONV PowRecursive(double num, int pow, double base)
        {
            return (pow > 0) ?
                (pow >  1) ? PowRecursive(num * base, pow - 1, base) : num :
                (pow < -1) ? PowRecursive(num * base, pow + 1, base) : 1 / num;
        }

        /**
        * \fn constexpr inline double Pow(double num, int pow)
        * \brief Calculates the value of num to the pow power
        *
        *   Calculates the value of num to the pow power
        *
        * \return  The value of num to the pow power
        */
        constexpr inline double _MM_CALLCONV Pow(double num, int pow)
        {
            return (pow == 0) ? 1.0 : PowRecursive(num, pow, num);
        }

        /**
        * \fn constexpr inline float ExpPowf(int pow)
        * \brief Calculates the exponential e to the pow power
        *
        *   Calculates the exponential e to the pow power
        *
        * \return e to the pow power
        */
        constexpr inline float _MM_CALLCONV ExpPowf(int pow)
        {
            return Powf(2.7182818284f, pow);
        }

        /**
        * \fn constexpr inline double ExpPow(int pow)
        * \brief Calculates the exponential e to the pow power
        *
        *   Calculates the exponential e to the pow power
        *
        * \return e to the pow power
        */
        constexpr inline double _MM_CALLCONV ExpPow(int pow)
        {
            return Pow(2.7182818284, pow);
        }
    }
}