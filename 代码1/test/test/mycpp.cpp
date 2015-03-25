#include <iostream>
using namespace std;

class ClassA 
{ 
public: 
	ClassA(int x) {a=x;};
	virtual void FunctionA(){
		printf("pIA:%p\n",this);}; 
		int a;
}; 
class ClassB 
{ 
public: 
	 virtual void FunctionB(){
		cout<<"BBB"<<endl;}; 
}; 
class ClassC : public ClassA,public ClassB 
{ 
public: 
	void FunctionC(){
		printf("pA:%p\n",this);}; 
	virtual	 void FunctionB(){
			cout<<"CCC"<<endl;}; 
			ClassC(int x):ClassA(1){a=x;};
			int a;
}; 

typedef void (ClassB::*pHandler)();
typedef void (ClassC::*pCHandler)();

int main()
{
	ClassC aObject(3); 
	ClassA* pA=&aObject; 
	ClassB* pB=&aObject; 
	ClassC* pC=&aObject; 

	cout<<pA->a<<endl;
	cout<<pC->a<<endl;

	pA->FunctionA();
	pB->FunctionB();

	pHandler phd = &ClassB::FunctionB;
	printf("FunctionB:%p\n",phd);

	pCHandler pChd = &ClassC::FunctionB;
	printf("FunctionB:%p\n",pChd);

	 pChd = &ClassC::FunctionC;
	printf("FunctionC:%p\n",pChd);
	return 0;
}
