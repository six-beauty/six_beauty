#include<iostream>
using namespace std;

class IX
{
public:
	virtual void fun()
	{
		printf("IX:%p\n",this);
	}
};

class IY
{
public:
	virtual void fun()
	{
		printf("IY:%p\n",this);
	}
};

class A:public IX,public IY
{
	void fun()
	{
		printf("A:%p\n",this);
	}
};

void f(IY *px)
{
	cout<<typeid(px).name()<<endl;
	printf("f:%p\n",px);
}


int main()
{
	A *pa=new A;

	IX *px=static_cast<IX*>(pa);
	px->fun();

	IY *py=static_cast<IY*>(pa);
	py->fun();

	cout<<typeid(pa).name()<<endl;
	cout<<typeid(px).name()<<endl;
	cout<<typeid(py).name()<<endl;
	printf("A:%p\n",pa);
	f(pa);
	delete pa;
	return 0;
}
