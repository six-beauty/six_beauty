#include<iostream>
using namespace std;

int totalv;
int marbles[6];
static int counter =0;


inline void ableDevide(bool flag)
{
	cout<<"Collection #"<<counter<<":\n";
	if(flag)
		cout<<"Can be divided.\n";
	else
		cout<<"Can't be divided.\n";
	cout<<endl;
}

bool dfs(const int half,int val,int pos)
{
	if(half==val)	return true;
	for(int s=pos;s<6;s++)
	{
		if(marbles[s])
		{
			if(val+(6-s) <= half)
			{
				val+=(6-s);
				marbles[s]--;
				if(dfs(half,val,s))
					return true;
			}
		}
	}
	return false;
}

void doDevide()
{
	if(totalv%2==1)
	{
		ableDevide(false);
		return ;
	}

	//doSearch
	if(marbles[0]>totalv/2)
	{
		ableDevide(false);
		return ;
	}
	ableDevide(dfs(totalv/2,0,0));
}

int main()
{
	//freopen("C:/Documents and Settings/Windows XP/×ÀÃæ/in.txt","r",stdin);
	while(1)
	{
		counter++;
		totalv=0;
		for(int s=5;s>=0;s--)
		{
			cin>>marbles[s];
			//½Ø¶Ï
			if(marbles[s]>60)
				marbles[s]=(marbles[s]%2)?61:60;
			totalv+=marbles[s]*(6-s);
		}

		if(totalv==0)	return 0;
		doDevide();
	}

	return 0;
}