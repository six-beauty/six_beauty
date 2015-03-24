#include<iostream>
#include"modelu.h"
using namespace std;
int main()
{
	Util<int> util;
	int a=1,b=3;
	util.Swap(a,b);
	cout<<a<<","<<b<<endl;
	cout<<typeid(1.23).name()<<endl;
	return 0;
}


