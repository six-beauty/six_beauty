/*朴素思想 --->>  TLE*/

#include<iostream>
using namespace std;

const __int64 inf=1e18;

int cmp(const void* a,const void* b)
{
	return *(int*)a-*(int*)b;
}

int main(int p)
{
	int n;
	while(cin>>n)
	{
		__int64* w=new __int64[2*n];  //每块木板的价值

		for(int i=0;i<2*n;i++)
			w[i]=inf;

		for(p=0;p<n;p++)
			scanf("%I64d",&w[p]);

		int mincost=0;
		while(true)
		{
			qsort(w,2*n,sizeof(__int64),cmp);

			if(w[1]==inf)
				break;

			w[p]=w[0]+w[1];
			w[0]=w[1]=inf;
			mincost+=w[p++];
		}

		cout<<mincost<<endl;

		delete w;
	}
	return 0;
}
