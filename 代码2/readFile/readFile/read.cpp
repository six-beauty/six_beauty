#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
using namespace std;
int main()
{
	string FileName="E:\\pyCal.py";
	try
	{
		ifstream ReadFile;
		ReadFile.open(FileName.c_str(),ios::binary|ios::in);
		if(!ReadFile)
		{
			cout<<"no exit!"<<endl;
			return 0;
		}

		ReadFile.seekg(0,ios::end);
		ios::pos_type ss=ReadFile.tellg();
		cout<<"FileSize:"<<ss<<'\n';
		throw string("¹ÊÒâµÄ");

		ReadFile.seekg(0,ios::beg);
		if(!ReadFile) return 1;
		std::ostringstream tmp; 
		tmp << ReadFile.rdbuf(); 
		std::string str = tmp.str();
		cout<< str<<endl;
		ReadFile.close();
	}
	catch(...)
	{
		cout<<"Exception happened"<<endl;
	}
}