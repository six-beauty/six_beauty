#include <iostream>
using namespace std;

class IX
{
public:
	int a;
	virtual void*  _cdecl Query(int d)=NULL;
	void fa()
	{
		a=10;
		cout<<"IX:"<<a<<endl;
	}
};

class IY
{
public:
	int a;
	virtual void*  _cdecl Query(int d)=NULL;
	void fb()
	{
		a=20;
		cout<<"IY:"<<a<<endl;
	}
};

class A:public IX,public IY
{
public:
	int a;
	void*  _cdecl Query(int a);
};

void* _cdecl A::Query(int a)
{
	switch(a)
	{
	case 10:
		cout<<"成功转为IX!"<<endl;
		printf("%p\n",this);
		return static_cast<IX*>(this);
		break;
	case 20:
		cout<<"成功转为IY!"<<endl;
		printf("%p\n",this);
		return static_cast<IY*>(this);
		break;
	default:
		break;
	}
	return NULL; 
}

int main()
{
	A* pa=new A;
	IX* pIx=NULL;
	pIx=(IX*)pa->Query(10);
	IY* pIy=NULL;
	pIy=(IY*)pa->Query(20);
	pIx->fa();
	pIy->fb();
	IY* ppIy=NULL;
	ppIy=(IY*)pIx->Query(20);
	ppIy->fb();
	IX* ppIx=NULL;
	ppIx=(IX*)pIy->Query(10);
	ppIx->fa();
	printf("%p\n",pIx);
	printf("%p\n",pIy);
	printf("%p\n",ppIx);
	printf("%p\n",ppIy);

	IX* pppIx=NULL;
	void* pv=static_cast<void*>(pIy);
	pppIx=static_cast<IX*>(pv);
	pppIx->fa();
	printf("%p\n",pppIx);

	IY* pppIy=NULL;
	pv=static_cast<void*>(pIx);
	pppIy=static_cast<IY*>(pv);
	pppIy->fb();
	printf("%p\n",pppIy);

	delete pa;
	return 0;
}



