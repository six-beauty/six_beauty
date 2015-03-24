#include<iostream>
#include<algorithm> 
using namespace std;

int main()
{
	int n;
	cin>>n;
	int* arry=new int[n];
	for(int i=0;i<n;i++)
		cin>>arry[i];
	sort(arry,arry+n);

	int sum=-arry[0];
	for(int i=0;i<n;i++)
		sum+=arry[i]*(n-i);
	cout<<sum<<endl;


	delete[] arry;

	return 0;
}

