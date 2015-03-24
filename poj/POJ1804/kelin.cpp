#include <iostream>
using namespace std;


int sort(int* array , int length)
{
	int  count = 0;
	bool hasSwap = false;
	do{
		for(int i =0;i<length;i++)
		{
			if(array[i]>array[i+1])
			{
				int temp = array[i];
				array[i+1] = array[i];
				array[i] = temp;
				hasSwap = true;
				count++;
			}
		}
	}while(hasSwap);
	return count;
}



int main(void)
{
	int arrayCount;
	cin>>arrayCount;
	int* pArray = new int[arrayCount];
	int* valueList =  new int[arrayCount];
	for(int i=0;i<arrayCount;i++)
	{
		cout<<arrayCount<<endl;
		cout<<i<<endl;
		int pLength,j=0;
		cin>>pLength;
		int* array = new int[pLength];
		if(pLength>j)
		{
			cout<<pLength<<" :"<<" :"<<j<<endl;
			int value;
			cin>>value;
			array[j]=value;
			j++;
			valueList[i]=sort(array,pLength);
		}
	}
	cout<<arrayCount<<endl;
	for(int i=0;i<arrayCount;i++)
	{
		cout<<"Scenario #"<<i<<":"<<endl;
		cout<<valueList[i]<<endl;
	}
	return 0;
}

