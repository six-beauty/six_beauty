//CppDll.h

//使用预编译开关切换类的导入导出定义
#ifdef DLLCLASS_EXPORTS

#define EXT_CLASS _declspec(dllexport)//DLL

#else

#define EXT_CLASS _declspec(dllimport)//使用者

//函数声明
EXT_CLASS int CPPdll_sub(int sub1,int sub2);
EXT_CLASS int CPPdll_add(int add1,int add2);
EXT_CLASS int CPPdll_mul(int mul1,int mul2);


#endif