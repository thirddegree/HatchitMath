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

/////////////////////////////////////////////////////////////
// Define portable platform macros
/////////////////////////////////////////////////////////////

#ifdef _WIN32
    //Windows platform
    #define HT_SYS_WINDOWS
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
    #ifndef NOMINMAX
    #define NOMINMAX
    #endif
#elif defined(__linux__)
    //Linux platform
    #define HT_SYS_LINUX
#elif defined(__APPLE__)
    //Apple platform
    #define HT_SYS_MACOS
#else
    #error System is not suported by Hatchit
#endif

/////////////////////////////////////////////////////////////
// Define portable API import/export macros
/////////////////////////////////////////////////////////////

#if !defined(HT_STATIC)
    #ifdef HT_SYS_WINDOWS
        //define dllexport and dllimport macros
        #if defined (HT_NONCLIENT_BUILD)
            #ifndef HT_API
            #define HT_API __declspec(dllexport)
            #endif
        #else
            #ifndef HT_API
            #define HT_API __declspec(dllimport)
            #endif
        #endif

        //Visual C++ compiler warning C4251 disable
        #ifdef _MSC_VER
        #pragma warning(disable : 4251)
        #endif

    #else //Linux and MAC OSX
        #if __GNUC__ >= 4
            //GCC 4 has unique keywords for showing/hiding symbols
            //the same keyword is used for both import and export
            #define HT_API __attribute__((__visibility__("default")))
            
            //Define MSVC compatible __forceinline keyword
            //for use with GCC compiler.
            #ifndef __forceinline
            #define __forceinline __attribute__((always_inline))
            #endif

        #else
            #define HT_API
        #endif
    #endif
#else
    //static build doesn't need import/export macros
    #define HT_API
#endif

#ifndef _MSC_VER
#define NOEXCEPT noexcept
#elif _MSC_VER >= 1900
#define NOEXCEPT noexcept
#else
#define NOEXCEPT 
#endif

//////////////////////////////
// BYTE typedef
//////////////////////////////
typedef unsigned char BYTE;
