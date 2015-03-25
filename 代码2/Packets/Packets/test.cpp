#include<cstdio>
#include<cstring>
using namespace std;
int main()
{
	int i=0,j=0,k=0,s[10];
	while(scanf("%d%d%d%d%d%d",&s[0],&s[1],&s[2],&s[3],&s[4],&s[5])!=EOF)
	{
		if(s[0]==0&&s[1]==0&&s[2]==0&&s[3]==0&&s[4]==0&&s[5]==0)
			break;
		int out=s[5]+s[4]+s[3];
		if(s[0]>=11*s[4])
			s[0]=s[0]-11*s[4];
		else
			s[0]=0;
		if(s[1]>=5*s[3])
			s[1]=s[1]-5*s[3];
		else
		{

			int temp1=(5*s[3]-s[1])*4;
			s[1]=0;
			if(s[0]>=temp1)
				s[0]=s[0]-temp1;
			else
				s[0]=0;
		}
		out=out+s[2]/4;
		if(s[2]%4!=0)
		{
			out++;
			int temp2=36-(s[2]%4)*9;
			if(s[2]%4==1)
			{
				if(s[1]>=5)
				{
					s[1]=s[1]-5;
					temp2=temp2-20;
				}
				else
				{
					temp2=temp2-s[1]*4;
					s[1]=0;
				}
			}
			else if(s[2]%4==2)
			{
				if(s[1]>=3)
				{
					s[1]=s[1]-3;
					temp2=temp2-12;
				}
				else
				{
					temp2=temp2-s[1]*4;
					s[1]=0;
				}
			}
			else if(s[2]%4==3)
			{
				if(s[1]>=1)
				{
					s[1]=s[1]-1;
					temp2=temp2-4;
				}
			}
			if(s[0]>=temp2)
				s[0]=s[0]-temp2;
			else
				s[0]=0;
		}
		if(s[1])
		{
			out=out+s[1]/9;
			if(s[1]%9!=0)
			{
				out++;
				int temp3=36-(s[1]%9)*4;
				if(s[0]>=temp3)
				{
					s[0]=s[0]-temp3;
				}
				else
					s[0]=0; 	
			}

		}
		if(s[0])
		{
			out=out+s[0]/36;
			if(s[0]%36!=0)
			{
				out++;
			}
		}

		printf("%d\n",out);
	}
	return 0;
}