#include<iostream>
#include<cmath>
#include<memory.h>
using namespace std;
const int LARGE=100000;
struct stepNode
{
	int step;
	int value;
};
bool vist[10001];
stepNode stepArr[LARGE];

bool isPrime(int value)
{
	if(value==2)	return true;
	if(value==1 || value%2 == 0)	return false;

	int vSQ=(int)sqrt((double)value);
	for(int s=3;s<=vSQ;s+=2)
	{
		if(value%s==0)
			return false;
	}
	return true;
}

inline void getArr(int arr[4],int value)
{
	for(int s=0;s<4;s++)
	{
		arr[s]=value%10;
		value/=10;
	}
}

void doSearch(int sour,int dest)
{
	//初始化
	memset(vist,0,sizeof(vist));
	int head,tail;

	stepArr[head=tail=0].value=sour;
	stepArr[tail++].step=0;
	vist[sour]=1;

	int destArr[4];
	getArr(destArr,dest);

	while(head<=tail)
	{
		stepNode headStep=stepArr[head++];
		if(headStep.value==dest)
		{
			cout<<headStep.step<<endl;		//结束
			break;
		}
		
		int headArr[4];
		getArr(headArr,headStep.value);
		
		//个位的
		for(int s=1;s<=9;s+=2)
		{
			if(s==headArr[0])	continue;

			int prime=(headStep.value/10)*10+s;
			if(isPrime(prime) && !vist[prime])
			{	//存入队列
				stepArr[tail].value=prime;
				stepArr[tail++].step=headStep.step+1;
				vist[prime]=true;
			}
		}
		//十位
		for(int s=0;s<=9;s++)
		{
			if(s==headArr[1])	continue;

			int prime=(headStep.value/100)*100+s*10+headStep.value%10;
			if(isPrime(prime) && !vist[prime])
			{	//存入队列
				stepArr[tail].value=prime;
				stepArr[tail++].step=headStep.step+1;
				vist[prime]=true;
			}
		}
		//百位
		for(int s=0;s<=9;s++)
		{
			if(s==headArr[2])	continue;

			int prime=(headStep.value/1000)*1000+s*100+headStep.value%100;
			if(isPrime(prime) && !vist[prime])
			{	//存入队列
				stepArr[tail].value=prime;
				stepArr[tail++].step=headStep.step+1;
				vist[prime]=true;
			}
		}
		//千位
		for(int s=1;s<=9;s++)
		{
			if(s==headArr[3])	continue;

			int prime=s*1000+headStep.value%1000;
			if(isPrime(prime) && !vist[prime])
			{	//存入队列
				stepArr[tail].value=prime;
				stepArr[tail++].step=headStep.step+1;
				vist[prime]=true;
			}
		}
	}
	/*for(int s=0;s<=tail;s++)
		cout<<s<<":step("<<stepArr[s].step<<"),"<<stepArr[s].value<<"        vist:"<<vist[s]<<endl;*/
}

int main()
{
	int sour,dest,n;
	cin>>n;
	for(int s=0;s<n;s++)
	{
		cin>>sour>>dest;
		doSearch(sour,dest);
	}
	return 0;
}

