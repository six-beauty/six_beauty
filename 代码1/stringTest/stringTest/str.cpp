#include<iostream>
#include<string>
using namespace std;

int main()
{
	string s1="C://main//tseta//hello.c";

	string s2="abc";
	s2.assign(s1.c_str(),s1.length());
	cout<<s2<<"|"<<endl;

	return 0;
}