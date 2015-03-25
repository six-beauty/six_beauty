#include<iostream>
#include<memory.h>
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
void changeRC(int arr[4][4],int i,int j)
{
	for(int s=0;s<4;s++)
		for(int y=0;y<4;y++)
		{
			if(s==i || y==j)
				arr[s][y]=!arr[s][y];
		}
}
bool isSuccess(int arr[4][4])
{
	int sum=0;
	for(int s=0;s<4;s++)
		for(int y=0;y<4;y++)
			if(arr[s][y])
				return false;
	return true;
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

bool getnext(int narr[4][4],int total)
{
	int arr[N+1]={0};
	for(int s=0;s<=total;s++)
		arr[s]=s;
	do{
		int out[4][4];
		copyArr(narr,out);
		memcpy(out,narr,sizeof(out));
		//获得的数组转换为4*4的坐标，再
		for(int s=0;s<=total;s++)
		{
			int nrow=arr[s]/4;
			int ncol=arr[s]%4;
			changeRC(out,nrow,ncol);
		}
		if(isSuccess(out))
		{
			cout<<total+1<<endl;;
			for(int s=0;s<=total;s++)
			{
				int nrow=arr[s]/4;
				int ncol=arr[s]%4;
				cout<<nrow+1<<" "<<ncol+1<<endl;
			}
			return true;;
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
			arr[s][y]=(sArr[s][y]=='+')?1:0;
		}
	}
	bool flag=false;
	for(int times=9;times<=15;times++)	//times从0到15，输出时要+1
	{
		if(getnext(arr,times))
		{
			flag=true;
			break;
		}
	}
	if(!flag)
	{
		for(int times=0;times<=8;times++)	//times从0到15，输出时要+1
		{
			if(getnext(arr,times))
				break;
		}
	}
	
	return 0;
}
