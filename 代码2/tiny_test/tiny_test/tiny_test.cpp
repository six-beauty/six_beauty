
#include "stdafx.h"
#include<string>
#include"xml/tinyxml.h"

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	TiXmlDocument doc;
	if(!doc.LoadFile("E:/ДњТы2/tiny_test/Debug./utf8test.xml"))
	{
		cout<<"xml read error!"<<endl;
		return -1;
	}
	TiXmlElement* root=doc.FirstChildElement("document");
	if(!root)
	{
		cout<<"root errror!"<<endl;
		return -1;
	}
	TiXmlElement *english=root->FirstChildElement("English");
	if(!english)
	{
		cout<<"english error!"<<endl;
		return -1;
	}
	string name=english->Attribute("name");
	cout<<name<<endl;
	string value=english->Attribute("value");
	cout<<value<<endl;
	return 0;
}
