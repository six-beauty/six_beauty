//快速排序练习c++实现
//author:sixbeauty

#include<iostream>
#include<vector>
#include<string>

template<typename T>
void quickSort(std::vector<T> &p,int left,int right)	//快速排序实现函数
{
	if(left>=right)	return ;	//若右标志为小于或等于左标志位，则不作任何事

	T keyData=p[left];			//选取第一位为key值
	int	i=left,j=right;			//左、右游标定义

	while(i<j)
	{
		while(i<j && p[j]>keyData)	//第一次进入循环，i=left，所以p[i]的值等于keyData，后面我们要保证p[i]=keyData
			j--;				//右游标移动到第一个小于key值的位置,i<j保证不出界，防止下面的赋值出错

		p[i]=p[j];				//这时p[j]的值等于keyData,但我们不马上赋值

		while(i<j && p[i]<keyData)
			i++;				

		p[j]=p[i];				//经过这一轮后，p[i]的值又重新等于keyData
	}	//跳出循环后，在i以前的值都小于keyData,在i以后的值都大于keyData,这时只要把keyData赋值给p[i]即可
	p[i]=keyData;

	quickSort(p,left,i-1);
	quickSort(p,i+1,right);
}

int main()
{
	//测试代码
	/*int p1[8]={1,4,5,7,11,2,18,9};
	std::vector<int> vetInt;
	for(int i=0;i<8;i++)
		vetInt.push_back(p1[i]);

	quickSort<int>(vetInt,0,7);

	for(std::vector<int>::iterator itr=vetInt.begin();itr!=vetInt.end();itr++)
		std::cout<<*itr<<",";
	std::cout<<std::endl;*/


	//测试代码
	std::string p1[8]={"ba","a","abd","defef","c","ca","daaa","aaa"};
	std::vector<std::string> vetStr;
	for(int i=0;i<8;i++)
		vetStr.push_back(p1[i]);

	quickSort<std::string>(vetStr,0,7);

	for(std::vector<std::string>::iterator itr=vetStr.begin();itr!=vetStr.end();itr++)
		std::cout<<*itr<<",";
	std::cout<<std::endl;
}