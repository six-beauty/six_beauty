//CppDllUse

#include<stdio.h>
#include"CppDll.h"

#pragma comment(lib,"CppDll.lib")

int main()
{
	int sum=CPPdll_add(5,6);
	int sub=CPPdll_sub(5,6);
	int mul=CPPdll_mul(5,6);
	printf("sum=%d,sub=%d,mul=%d\n",sum,sub,mul);


	return 0;
}