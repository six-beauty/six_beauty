#include<iostream>
using namespace std;
struct tagStep
{
	int row;
	int col;
};
void changeRC(const int arr[4][4],int out[4][4],int i,int j)
{
	for(int s=0;s<4;s++)
		for(int y=0;y<4;y++)
		{
			if(s==i || y==j)
				out[s][y]=!arr[s][y];
			else
				out[s][y]=arr[s][y];
		}
}
bool isSuccess(int arr[4][4])
{
	int sum=0;
	for(int s=0;s<4;s++)
		for(int y=0;y<4;y++)
			sum+=arr[s][y];
	return (sum==0)?true:false;
}

tagStep stepArr[100];
bool isLastTime(int arr[4][4],int count,int oldR,int oldC)
{
	int outArr[4][4];		
	//本次能结束？
	for(int s=0;s<4;s++)
	{
		for(int y=0;y<4;y++)
		{
			if(s==oldR && y== oldC)
				continue;

			changeRC(arr,outArr,s,y);
			if(isSuccess(outArr))
			{
				tagStep ts={s,y};
				stepArr[count]=ts;
				return true;
			}
		}
	}
	return false;
}

void dealChange(int arr[4][4],int &count,int oldR,int oldC)
{
	if(isLastTime(arr,count,oldR,oldC))
	{
		count++;
		return ;
	}
	int outArr[4][4];
	//不能结束
	for(int s=0;s<4;s++)
	{
		for(int y=0;y<4;y++)
		{	
			if(s==oldR && y== oldC)
				continue;
			//当前步骤放入
			changeRC(arr,outArr,s,y);
			if(isLastTime(outArr,count+1,s,y))
			{
				tagStep ts={s,y};
				stepArr[count]=ts;
				count++;
				return ;
			}
		}
	}
	dealChange()
}

//void printArr(int arr[4][4])
//{
//	for(int s=0;s<4;s++)
//	{
//		for(int y=0;y<4;y++)
//			cout<<arr[s][y]<<" | ";
//		cout<<endl;
//	}
//}

int main()
{
	int arr[4][4];
	char sArr[4][4];
	//输入数据
	for(int s=0;s<4;s++)
		for(int y=0;y<4;y++)
		{
			cin>>sArr[s][y];
			arr[s][y]=(sArr[s][y]=='+')?1:0;
		}
	
//	printArr(arr);
//	cout<<"========flag========"<<endl;
	int times=0;
	dealChange(arr,times,4,4);
	cout<<times<<endl;
	for(int s=0;s<times;s++)
		cout<<stepArr[s].row<<" "<<stepArr[s].col<<endl;

	return 0;
}

