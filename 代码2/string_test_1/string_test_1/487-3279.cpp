#include<iostream>
#include<string>
#include<windows.h>
using namespace std;

int main()
{
	char sChar[6];
	strncpy(sChar,"abc234",3);

	cout<<sChar<<"|"<<endl;
	std::string s1(sChar);
	cout<<s1<<"|"<<endl;
	return 0;
}
