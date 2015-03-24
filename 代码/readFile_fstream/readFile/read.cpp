#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
using namespace std;
int main()
{
	string FileName="F:\\mailfile\\55e736d12f2eb938e9ea5eb1d5628535e4dd6fe9.jpg";
	ifstream ReadFile;
	ReadFile.open(FileName.c_str(),ios::binary|ios::in);

	ReadFile.seekg(0,ios::end);
	ios::pos_type ss=ReadFile.tellg();
	cout<<"FileSize:"<<ss<<'\n';

	ReadFile.seekg(0,ios::beg);
	if(!ReadFile) return 1;
	std::ostringstream tmp; 
	 tmp << ReadFile.rdbuf(); 
	std::string str = tmp.str();
	cout<< str<<endl;
	ReadFile.close();
}