#include<iostream>
#include<algorithm>
using namespace std;

int stick[65];
bool vist[65];
int size;	//stick数组大小
int maxLen;	//stick总长度
int nroot;	//共有n根

bool cmp(const int a,const int b)
{
	return a>b;
}

bool dfs(const int lstick,	//要拼成的长度
		 int len,			//当前长度
		 int pos,			//stick数组查到的位置
		 int root)			//当前第几根
{
	if(len==lstick)	return true;

	return false;
}

int main()
{
	freopen("E:/代码2/extra_test/Debug/in.txt","r",stdin);
	while(cin>>size && size)
	{
		maxLen=0;
		for(int s=0;s<size;s++)
		{
			cin>>stick[s];
			maxLen+=stick[s];
		}

		sort(stick,stick+size,cmp);
		for(int s=stick[0];s<=maxLen;s++)
		{
			if(maxLen%s!=0)
				continue;
			//doSearch
			memset(vist,0,sizeof(vist));
			nroot=maxLen/s;
			if(dfs(s,0,0,0))
			{
				cout<<s<<endl;
				break;
			}
		}

	}
	return 0;
}
