#include<iostream>
#include<algorithm>
using namespace std;

int stickArr[65];
bool vist[65];
int noEnouth[65];
int neSize;
int size;
int maxLen;


bool cmp(const int a,const int b)
{
	return a>b;
}
int getNext(int beg)
{
	for(int s=beg+1;s<=maxLen;s++)
	{
		if(maxLen%s==0)
			return s;
	}
	return maxLen+1;
}
int getBegin(int beg)
{
	if(maxLen%beg==0)
		return beg;
	else
		return getNext(beg);
}

bool isIncl(int per)
{
	for(int s=0;s<size;s++)
	{
		if(!vist[s] && per==stickArr[s])
		{
			vist[s]=true;
			return true;
		}
	}
	for(int s=0;s<size;s++)
	{
		if(!vist[s])
		{
			int noEn=per-stickArr[s];
			if(noEn<0)		//若小于0，继续循环
				continue;
			//剪枝，在noEnouth里面的就不要再重复做了
			for(int y=0;y<neSize;y++)
			{
				if(noEnouth[y]==noEn)
					return false;
			}
			//判断是否能凑出来
			vist[s]=true;
			if(isIncl(noEn))
				return true;
			else
				vist[s]=false;
		}//if
	}//for
	noEnouth[neSize++]=per;

	return false;
}

bool doSearch(int per)
{
	memset(vist,0,sizeof(vist));
	memset(noEnouth,0,sizeof(noEnouth));
	int times=maxLen/per;
	neSize=0;
	for(int s=0;s<times;s++)
	{
		if(!isIncl(per))
			return false;
	}
	return true;
}

int main()
{
	freopen("E:/代码2/extra_test/Debug/in.txt","r",stdin);
	while(cin>>size && size)
	{
		maxLen=0;
		for(int s=0;s<size;s++)
		{
			cin>>stickArr[s];
			maxLen+=stickArr[s];
		}

		sort(stickArr,stickArr+size,cmp);

		for(int s=getBegin(stickArr[0]);s<=maxLen;s=getNext(s))
		{
			if(doSearch(s))	
			{
				cout<<s<<endl;
				break;
			}
		}

	}
	return 0;
}

