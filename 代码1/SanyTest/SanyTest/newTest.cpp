#include<iostream>
using namespace std;
int main()
{
	int arr[23]={0};
	for(int i=1;i<23;i++)
		arr[i]=i;
	int *my=arr;
	int n;
	while(cin>>n)
		cout<<my[n]<<endl;

	return 0;
}
	