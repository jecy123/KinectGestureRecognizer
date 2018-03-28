#ifndef __DLL_API_H__
#define __DLL_API_H__

#ifdef DLL_IMPLEMENT
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

#endif