#include <iostream>
using namespace std;

void fun(int arry[],int len)
{
	for (int i=0;i<len;i++)
		count<<arry[i]<<endl;
}

int main()
{
	int arry[]={1,2,3,4,5};
	fun(arry,sizeof(arry)/sizeof(int));

	return 0;
}

