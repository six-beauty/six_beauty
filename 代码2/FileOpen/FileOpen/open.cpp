#include<iostream>
#include<fstream>
using namespace std;

#include<stdio.h>

int count3_3(int a,int b,int c,int &sum)
{
	sum+=(c/4);
	c=c%4;
	if(c!=0)
	{
		int en=(4-c)*9;
		sum++;
		//处理c的
		switch(c)
		{
		case 1:
			{
				if(b>=5)
				{
					b-=5;
					en=en-5*4;
				}else
				{
					en=en-b*4;
					b=0;
				}
				break;
			}
		case 2:
			{
				if(b>=3)
				{
					b-=3;
					en=en-3*4;
				}else
				{
					en=en-b*4;
					b=0;
				}

				break;
			}
		case 3:
			{
				if(b>=1)
				{
					b-=1;
					en=en-1*4;
				}
				break;
			}
		}
		if(a>en)
			a-=en;
		else
			a=0;
	}

	if(b>0)
	{
		sum+=(b/9);
		if(b%9!=0)
		{
			sum++;
			int ne=(9-b%9)*4;
			if(a>ne)
				a-=ne;
			else
				a=0;
		}
	}
	if(a>0)
	{
		sum+=(a/36);
		if(a%36!=0)
			sum++;
	}

	return sum;
}

bool change3_3(int &a,int &b,int &c,int &d,int &e,int &f,int &sum)
{
	if(!(a+b+c+d+e+f))	return false;

	sum=f+e+d;
	//5*5
	if((a=a-e*11)<0)	
		a=0;
	//4*4 
	if(b>5*d)
		b-=(5*d);
	else
	{
		int ne=(5*d-b)*4;
		b=0;
		if(ne<a)
			a-=ne;
		else
			a=0;
	}
	return true;
}

int main()
{
	ifstream ifs("E:/代码2/FileOpen/Debug/test.txt",ios::out);
	ifstream ifs2("E:/代码2/FileOpen/Debug/test2.txt",ios::out);
	if(!ifs.is_open() || !ifs2.is_open())
	{
		cout<<"open file error!"<<endl;
		return -1;
	}
	char buffer[128]={};
	char buffer2[128]={};
	int a[6],out,yes;

	while(!ifs.eof())
	{
		ifs.getline(buffer,128);
		ifs2.getline(buffer2,128);
		sscanf(buffer,"%d %d %d %d %d %d",a,a+1,a+2,a+3,a+4,a+5);
		sscanf(buffer2,"%d",&out);
	//	cout<<"num:"<<a[0]<<","<<a[1]<<","<<a[2]<<","<<a[3]<<","<<a[4]<<","<<a[5]<<endl;

		int sum=0;
		if(!change3_3(a[0],a[1],a[2],a[3],a[4],a[5],sum))
		{
			cout<<"终止！"<<endl;
			return 0;
		}
		yes=count3_3(a[0],a[1],a[2],sum);
		if(yes != out)
		{
			cout<<"================flag=============="<<endl;
			cout<<"num:"<<a[0]<<","<<a[1]<<","<<a[2]<<","<<a[3]<<","<<a[4]<<","<<a[5]<<endl;
			cout<<"file :"<<out<<",count："<<yes<<endl;

			cout<<"================flag=============="<<endl;
		}
	}

	return 0;
}
