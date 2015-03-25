#include<iostream>
using namespace std;

struct test{
	//void (*tfun)();
	void fun()
{
	cout<<"func"<<endl;
}
};
int main()
{
	struct test mys;
	//mys.tfun=fun;
	//mys.tfun)();
	mys.fun();
	return 0;
}
