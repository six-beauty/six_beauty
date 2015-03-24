#include<iostream>

using namespace std;
//2以上（大于2）
int analyzing(int n)
{
	int count=1;
	while(n!=1)
	{
		count++;
		if(n%2!=0)
			n=3*n+1;
		else
			n=n/2;
	}
	return count;
 }

int main()
{
	int x,y;
	while(cin>>x>>y)
	{
		int maxc=0;
		for(int i=x;i<=y;i++)
		{
			int out=analyzing(i);
			if(maxc<out)
				maxc=out;
		}
		cout<<x<<' '<<y<<' '<<maxc<<endl;
	}

	return 0;
}

