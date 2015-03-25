#include<iostream>
#include<math.h>
using namespace std;

int primeArr[10000]={2,3};		//素数的数组
int count=1;

inline void getPrimeArr(int max)
{
	if(primeArr[count]>max)	return;

	int now=primeArr[count]+2;
	for(int s=now;s<=max;s+=2)
	{
		bool flag=true;
		double half=sqrt((double)s);
		for(int y=1;primeArr[y]<=half;)
		{
			if(s%primeArr[y++]==0)
			{
				flag=false;
				break;
			}
		}
		if(flag)
		{
			primeArr[++count]=s;
		}
	}
}
inline bool isInPrimeArr(int num)
{
	for(int s=0;primeArr[s]<=num;s++)
	{
		if(primeArr[s]==num)
			return true;
	}
	return false;
}
inline void isSuit(int max)
{
	//getPrimeArr(max);
	for(int s=0;primeArr[s]<max;s++)
	{
		int leave=max-primeArr[s];
		if(isInPrimeArr(leave))
		{
			cout<<max<<" = "<<primeArr[s]<<" + "<<leave<<endl;
			return;
		}
	}
	cout<<"Goldbach's conjecture is wrong."<<endl;
	return ;
}

int main()
{
	int max;
	getPrimeArr(1000000);
	while(cin>>max)
	{
		if(max==0)	break;
		isSuit(max);
	}
	return 0;
}

