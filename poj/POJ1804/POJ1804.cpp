#include<iostream>
#include<memory.h>
#include<stdlib.h>
using namespace std;

int compare(const void* px,const void* py)
{
	int x = *(int*)px;
	int y = *(int*)py;
	return x-y;
}

int qSwap(int* arry ,const int dest,const int src)
{
	if(dest>=src) return 0;

	int save=arry[src];
	for(int i=src;i>dest;i--)
		arry[i]=arry[i-1];
	arry[dest]=save;
	return src-dest;
}

int LogSwapTime(int* arry,const int* qarry,int len)
{
	int count=0;
	for(int i=0;i<len;i++)
	{
		int srcE=qarry[i];
		int src=i;

		while(arry[src]!=srcE&&src<len)
			src++;
		count+=qSwap(arry,i,src);
	}
	return count;
}


int main()
{
	int nscen;
	cin>>nscen;
	for(int i=0;i<nscen;i++)
	{
		int lenSeq;
		cin>>lenSeq;
		int *arry = new int[lenSeq];
		for(int j=0;j<lenSeq;j++)
		{
			cin>>*(arry+j);
		}

		int *qarry = new int[lenSeq];
		memcpy(qarry,arry,sizeof(int)*lenSeq);
		qsort(qarry,lenSeq,sizeof(int),compare);

		int out=LogSwapTime(arry,qarry,lenSeq);
		cout<<"Scenario #"<<i+1<<":"<<endl;
		cout<<out<<endl<<endl;


		delete[] arry;
	}

	return 0;
}

