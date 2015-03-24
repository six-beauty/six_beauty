#include<iostream>
using namespace std;


int countLive(int n)
{
	int step=1;
	while(n!=1)
	{
		if(n%2)
			n = n*3 + 1;
		else
			n = n/2;
		++step;
	}
	return step;
}

void getCycle(int i,int j)
{
	int x = i<j?i:j;
	int y = i>j?i:j;
	int maxC = 1;
	for(int s=x;s<=y;s++)
	{
		int cy = countLive(s);
		if (maxC < cy) maxC=cy;
	}
	cout<<i<<" "<<j<<" "<<maxC<<endl;
}


int main()
{
	int i,j;
	while(cin>>i>>j)
	{
		getCycle(i,j);
	}
	return 0;
}

