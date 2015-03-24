#include<iostream>
using namespace std;


void quickSortForK(int* array,int LIndex, int RIndex, int k)
{
	if(LIndex - RIndex ==1)
	{
		if(array[LIndex]>array[RIndex])
		{
			int temp = array[LIndex];
			array[LIndex] = array[RIndex];
			array[RIndex] = temp;
		}
		return;
	}


	int L,R;
	L=R=0;
	for(int i=0;i<RIndex-LIndex;i++)
	{
		if(array[RIndex]>array[LIndex+i])
		{
			L++;
			if(L>=1&&R>=1)
			{
				int atemp= array[LIndex+L];
				array[LIndex+L] = array[LIndex+i];
				array[LIndex+i] = atemp;


			}
		}
		else
			R++;
	}
	int intTemp = array[RIndex];
	array[RIndex] = array[LIndex+L];
	array[LIndex+L] = intTemp;
	if(L>0&&LIndex+L>k)
		quickSortForK(array,LIndex,LIndex+L-1,k);
	if(R>0&&LIndex+L<k)
		quickSortForK(array,LIndex+L+1,RIndex,k);


}


int main(void)
{
	int Count,i=0;
	cin>>Count;
	int* array = new int[Count];
	for(int i=0;i<Count;i++)
	{
		cin>>*(array+i);
	}
	cout<<endl;
	int k = Count/2;
	quickSortForK(array,0,Count-1,k);
	cout<<array[Count/2]<<endl;

	cout<<endl;
	for(int i =0;i<Count;i++){
		cout<<array[i]<<" ";
	}
	cin>>Count;
}

