#include<iostream>
using namespace std;
const int N=15;
inline void copyArr(const int arr[4][4],int out[4][4])
{
	for(int s=0;s<4;s++)
	{
		for(int y=0;y<4;y++)
			out[s][y]=arr[s][y];
	}
}
inline void changeRC(int arr[4][4],int i,int j)
{
	arr[i][j]=!arr[i][j];
	if(i-1>=0)	arr[i-1][j]=!arr[i-1][j];
	if(i+1<=3)	arr[i+1][j]=!arr[i+1][j];
	if(j-1>=0)	arr[i][j-1]=!arr[i][j-1];
	if(j+1<=3)	arr[i][j+1]=!arr[i][j+1];
}
bool isSuccess(const int arr[4][4])
{
	int sum=0;
	for(int s=0;s<4;s++)
		for(int y=0;y<4;y++)
			sum+=arr[s][y];
	return (sum==0 || sum==16)?true:false;
}

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

void printArr(int arr[4][4])
{
	for(int s=0;s<4;s++)
	{
		for(int y=0;y<4;y++)
			cout<<arr[s][y]<<",";
		cout<<endl;
	}
}

bool getnext(int narr[4][4],int total)
{
	int arr[N]={0};
	for(int s=0;s<=total;s++)
		arr[s]=s;
	do{
		int out[4][4];
		copyArr(narr,out);
		for(int s=0;s<=total;s++)
		{
			int nrow=arr[s]/4;
			int ncol=arr[s]%4;
			changeRC(out,nrow,ncol);
		}
		if(isSuccess(out))
		{
			cout<<total+1<<endl;
			return true;
		}

	}while(tryadd(arr,total,total));
	return false;
}

int main()
{
	int arr[4][4];
	char sArr[4][4];
	//输入数据
	for(int s=0;s<4;s++)
	{
		for(int y=0;y<4;y++)
		{
			cin>>sArr[s][y];
			arr[s][y]=(sArr[s][y]=='b')?1:0;
		}
	}
	int times=0;
	if(isSuccess(arr))
	{
		cout<<times<<endl;
		return true;
	}
	for(;times<=8;times++)
	{
		if(getnext(arr,times))
			break;
	}
	if(times>8)
		cout<<"Impossible"<<endl;

	return 0;
}
