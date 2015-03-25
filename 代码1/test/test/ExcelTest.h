#pragma once


#ifdef DLLCLASS_EXPORTS

#define EXT_CLASS _declspec(dllexport)//DLL

#else

#define EXT_CLASS _declspec(dllimport)//สนำรี฿

#endif

EXT_CLASS char *w2c(char *pcstr,const wchar_t *pwstr, size_t len);

EXT_CLASS void myDllFunc(char *destStr);