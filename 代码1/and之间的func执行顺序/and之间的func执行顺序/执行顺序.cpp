#include<iostream>
using namespace std;
bool func1()
{
	cout<<"func1"<<endl;
	return true;
}
bool func2()
{
	cout<<"func2"<<endl;
	return true;
}
bool func3()
{
	cout<<"func3"<<endl;
	return true;
}
bool func4()
{
	return func1()&&func2()&&func3();
}

int main()
{
	func4();
	return 0;
}