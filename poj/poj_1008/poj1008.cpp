#include "iostream"
using namespace std;

int  getN(int n )
{
	if(n==1||n<=0)
	{
		return 1;
	}
	if(n%2)
		return 1+getN(n*3+1);
	else
		return 1+getN(n/2);
} 


int main(){
	int n11, n22;
	while(cin>>n11>>n22)
	{
		int n1=n11<n22?n11:n22;
		int n2=n11>n22?n11:n22;
		int Max = 1;
		for(int i = n1;i<=n2;i++)
		{
			int out = getN(i);
			if (out >Max) Max = out;
		}
		cout<<n1<<" "<<n2<<" "<<Max<<endl;
	}
	return 0;
}
