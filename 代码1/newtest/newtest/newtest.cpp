#include<iostream>
#include<string.h>

using namespace std;
/*
class Stock{
private:
	char *stockcode=new char[100]; //这个语句在编译时有两个错误
	int quan;
	double price;
public:
	Stock(char na[],int q=1000,double p=8.98)
	{
		strcpy(stockcode,na);
		quan=q;
		price=p;
	}
	void print()
	{
		cout<<this->stockcode<<"   "<<quan<<"   "<<price<<endl;
	}
};		*/
int main()
{
	/*
	Stock stock("123456",500);
	stock.print();
	*/
	char pSourceStr[1024]={"abcdefghight"};
	char pDestStr[1024]={};
	memset(pDestStr,1,1024);
	strncpy(pDestStr,pSourceStr,100);
	for(int i=0;i<1024;i++)
		if(pDestStr[i]==0)
			cout<<i<<":"<<pDestStr[i]<<endl;
	cout<<(int)'\0'<<endl;

	return 0;
}