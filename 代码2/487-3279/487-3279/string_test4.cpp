#include<iostream>
#include<string>
#include<map>
#include <algorithm>
using namespace std;

inline bool char2Int(char cx,int &out)
{
	//cx  Ù”⁄[A,P]
	int excaptAx=cx-'A';
	if((0 <=excaptAx) && ( excaptAx<=('P'-'A')) )	
	{
		out=2+ (excaptAx /3);
		return true;
	}

	//cx Ù”⁄(Q,Z)
	int excapeQx=cx-'Q';
	if( (0 < excapeQx) && (excapeQx < ('Z'-'Q')) )
	{
		out=7+ ( excapeQx /3 );
		return true;
	}

	return false;
}
string changeStr(string str)
{
	string outStr;
	int out;
	outStr.resize(str.length()+1);
	for(int count=0;count<(int)str.length();count++)
	{
		if(char2Int(str[count],out))
		{
			char c=(char)('0'+out);
			outStr.insert(count,1,c);
		}else
		{
			int excapeQz=str[count]-'0';
			if( (0 <= excapeQz) && (excapeQz <= ('9'-'0')) )
				outStr.insert(count,1,str[count]);
		}
	}
	outStr.insert(3,1,'-');
	return outStr.c_str();
}



inline void stringWipe(string & srcStr)
{
	for(string::iterator itr=srcStr.begin();itr!=srcStr.end();)
		if(*itr=='-')
			itr=srcStr.erase(itr);
		else
			itr++;
	return ;
}


int main()
{
	/*int n;
	cin>>n;
	map<string,int> mapStr;
	for(int i=0;i<n;i++)
	{
		string inStr;
		cin>>inStr;
		stringWipe(inStr);
		string out=changeStr(inStr);
		if(out.length() <8)	continue;

		map<string,int>::iterator itr=mapStr.find(out);
		if(itr==mapStr.end())
		{
			mapStr.insert(make_pair<string,int>(out,1));
		}else
		{
			mapStr[out]=itr->second+1;
		} 
	} 
	int nLine=0;
	for(map<string,int>::iterator itr=mapStr.begin();itr!=mapStr.end();itr++)
	{
		if(itr->second > 1)
		{
			nLine++;
			cout<<itr->first<<" "<<itr->second<<endl;
		}
	}
	if(!nLine)
		cout<<"No duplicates."<<endl;
	return 0;*/

	int a[20]={2,4,1,23,5,76,0,43,24,65},i;
	for(i=0;i<20;i++)
		cout<<a[i]<<endl;
	cout<<"=====flag======"<<endl;
	sort(a,a+10);
	for(i=0;i<10;i++)
		cout<<a[i]<<endl;
	return 0;
}


