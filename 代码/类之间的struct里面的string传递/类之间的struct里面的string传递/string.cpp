#include<iostream>
#include<string>
using namespace std;
struct tagStr
{
	string name;
	string msg;
};

class A
{
public:
	A(){};
	void printStruct(tagStr a)
	{
		cout<<a.name<<endl;
		cout<<a.msg<<endl;
	}
};

int main()
{
	tagStr b={"hello","world"};
	A a;
	a.printStruct(b);


	return 0;
}