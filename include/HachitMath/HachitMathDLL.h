#ifndef HACHIT_MATH_DLL_H
#define HACHIT_MATH_DLL_H

#ifdef _WIN32

#ifdef HACHIT_MATH_EXPORTS
#define HACHIT_MATH_API __declspec(dllexport)
#else
#define HACHIT_MATH_API __declspec(dllimport)
#endif

#else
#define HACHIT_MATH_API
#endif

#endif
