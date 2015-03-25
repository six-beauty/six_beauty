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
		m_x = x;
	}
};
class C :virtual public A {
public:
	C (int x) : A(x) {}
	int get(void) {
		return m_x;
	}
};
class D :public B,public C {
public:
	D (int x) : B(12),C(13),A(14),m_x(x)
	{
		cout<<"¹¹Ôì£º"<<m_x<<endl;
		cout<<B::m_x<<endl;
	}
	int m_x;
	void print()
	{
		cout<<"print:"<<m_x<<endl;
	}
};
int main(void) {
	D d(10);
	d.set(20);
	cout << d.get() << endl;
	d.print();
	return 0;
}