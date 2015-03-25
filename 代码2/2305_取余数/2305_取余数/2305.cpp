#include<iostream>
#include<string.h>
using namespace std;

int main()
{
	int n;
	while(1)
	{
		cin>>n;
		if(n==0)	break;

		char psz[1001]={};
		char msz[10]={};
		cin>>psz>>msz;

		int p=0,m=0;
		for(int s=0;msz[s];s++)
		{
			m*=n;
			m+=msz[s]-'0';
		}

		for(int s=0;psz[s];s++)
		{
			p*=n;
			p+=psz[s]-'0';

			if(p>=m)	p%=m;
		}

		if(!p)
			cout<<0<<endl;
		else
		{
			int modArr[10],y=0;
			for(;p>0 && y<10;y++)
			{
				modArr[y]=p%n;
				p/=n;
			}
			for(int s=y-1;s>=0;s--)
				cout<<modArr[s];
			cout<<endl;
		}
	}
	return 0;
}
