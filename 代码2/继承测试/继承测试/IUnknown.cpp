#include <iostream>
using namespace std;

class IX
{
public:
	int a;
	virtual void  _cdecl Query(int d,void **ppv)=NULL;
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
	virtual void  _cdecl Query(int d,void **ppv)=NULL;
	void fb()
	{
		a=20;
		cout<<"IY"<<a<<endl;
	}
};

class A:public IX,public IY
{
public:
	int a;
	void  _cdecl Query(int a,void **ppv);
};

void _cdecl A::Query(int a,void **ppv)
{
	switch(a)
	{
	case 10:
		*ppv= static_cast<IX*>(this);
		cout<<"成功转为IX!"<<endl;
		break;
	case 20:
		*ppv= static_cast<IY*>(this);
		cout<<"成功转为IY!"<<endl;
		break;
	default:
		break;
	}
	return; 
}

int main()
{
	A* pa=new A;
	//IX* px=static_cast<IX*>(pa);
	//IY* py=static_cast<IY*>(pa);

	//printf("%p\n",pa);
	//printf("%p\n",px);
	//printf("%p\n",py);
	//px->fa();
	//py->fb();

	cout<<"======================"<<endl;
	//这种转换是不成功的
	//IY* ppy=static_cast<IY*>(px);
	//printf("%p\n",ppy);
	//ppy->fb();

	//IX* ppx=static_cast<IX*>(py);
	//printf("%p\n",ppx);
	//ppx->fa();

	IX* pIx=NULL;
	pa->Query(10,(void**)&pIx);
	IY* pIy=NULL;
	pa->Query(20,(void**)&pIy);
	pIx->fa();
	pIy->fb();
	IY* ppIy=NULL;
	pIx->Query(20,(void**)&ppIy);
	ppIy->fb();
	IX* ppIx=NULL;
	pIy->Query(10,(void**)&ppIx);
	ppIx->fa();
	printf("%p\n",pIx);
	printf("%p\n",pIy);
	printf("%p\n",ppIx);
	printf("%p\n",ppIy);

	delete pa;
	return 0;
}



