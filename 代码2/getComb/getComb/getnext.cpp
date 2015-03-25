//Memory Time 
//260K  141MS 
#include<iostream>
using namespace std;
const int N=15;

bool tryadd(int arr[N],int total,int x)		//total总共多少位，当前加哪位
{
	if(arr[x]+1>N-(total-x))
	{
		if(x-1<0)
			return false;
		else
			return tryadd(arr,total,x-1);
	}else{
		arr[x]+=1;
		for(int s=x+1;s<=total;s++)
			arr[s]=arr[s-1]+1;
		return true;
	}
}

void getnext(int total)
{
	int arr[N]={0};
	for(int s=0;s<=total;s++)
		arr[s]=s;
	do{
		cout<<arr[0]<<",";
		cout<<arr[1]<<",";
		cout<<arr[2]<<",";
		cout<<arr[3]<<",";
		cout<<endl;
	}while(tryadd(arr,total,total));
}


int main()
{
	//int arr[16]={1,4,15,16};
	int total;
	while(cin>>total)
		getnext(total);
	

	return 0;
}
