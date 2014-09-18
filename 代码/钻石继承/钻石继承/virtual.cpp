//diamond.cpp
#include<iostream>
using namespace std;
class A{
public:
	A (int x) :  m_x(x) {}
	int m_x;     
};
class B :virtual public A {
public:
	B (int x) : A(x) {}
	void set(int x) {
		this->m_x = x;
	}
};
class C :virtual public A {
public:
	C (int x) : A(x) {}
	int get(void) {
		return this->m_x;
	}
};
class D :public B,public C {
public:
	D (int x) : B(x),C(x),A(x){}
	
};
class E:public D
{
public:
	E (int x) : D(x),A(x){};

};
int main(void) {
	D d(10);
	E e(12);
	d.set(20);
	e.set(31);
	cout << d.get() << endl;
	cout << e.get() << endl;
	return 0;
}