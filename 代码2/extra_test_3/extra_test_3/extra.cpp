#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int cmp(const void *a,const void *b)
{
	return *(int *)b-*(int *)a;
}

const int MAXN=65;
int n,stick[MAXN];
bool vis[MAXN];
bool dfs(int len,int InitLen,int start,int num)
{
	if(num==n)
		return true;
	int tmp=-1;
	for(int i=start;i<n;i++)
	{
		if(vis[i]||stick[i]==tmp)
			continue;
		vis[i]=true;
		if(len+stick[i]<InitLen)
		{
			if(dfs(len+stick[i],InitLen,i+1,num+1))
				return true;
			else
				tmp=stick[i];
		}
		else if(len+stick[i]==InitLen)
		{
			if(dfs(0,InitLen,0,num+1))
				return true;
			else
				tmp=stick[i];
		}
		vis[i]=false;
		if(len==0)
			break;
	}
	return false;
}

int main()
{
	while(scanf("%d",&n),n)
	{
		int SumLen=0;
		bool flag=true;
		for(int i=0;i<n;i++)
		{
			scanf("%d",&stick[i]);
			SumLen+=stick[i];
		}
		qsort(stick,n,sizeof(stick[0]),cmp);
		for(int InitLen=stick[0];InitLen<=SumLen-InitLen;InitLen++)
		{
			memset(vis,false,sizeof(vis));
			if(!(SumLen%InitLen)&&dfs(0,InitLen,0,0))
			{
				printf("%d\n",InitLen);
				flag=false;
				break;
			}
		}
		if(flag)
			printf("%d\n",SumLen);
	}
	return 0;
}