#include<iostream>
#include<queue>
using namespace std;

struct stepNode 
{
	int x;
	int y;
	int step;
};

bool vist[301][301];
int chessSize;

queue<stepNode> stepQueue;

void doSearch(stepNode stepSour,stepNode stepDest)
{
	//初始化
	memset(vist,0,sizeof(vist));
	while(stepQueue.size())	stepQueue.pop();

	stepQueue.push(stepSour);
	while(!stepQueue.empty())
	{
		stepNode stepHead=stepQueue.front();
		stepQueue.pop();

		if(stepHead.x==stepDest.x && stepHead.y==stepDest.y)
		{
			cout<<stepHead.step<<endl;
			return ;
		}

		for(int s=-1;s<=1;s+=2)
		{
			for(int y=-2;y<=2;y+=4)
			{
				int newx=stepHead.x+s,newy=stepHead.y+y;
				if(!vist[newx][newy] && newx>=0 && newx<chessSize && newy>=0 && newy<chessSize )
				{
					stepNode stepTail={newx,newy,stepHead.step+1};
					stepQueue.push(stepTail);
					vist[newx][newy]=true;
				}
			}
		}

		for(int s=-2;s<=2;s+=4)
		{
			for(int y=-1;y<=1;y+=2)
			{
				int newx=stepHead.x+s,newy=stepHead.y+y;
				if(!vist[newx][newy] && newx>=0 && newx<chessSize && newy>=0 && newy<chessSize )
				{
					stepNode stepTail={newx,newy,stepHead.step+1};
					stepQueue.push(stepTail);
					vist[newx][newy]=true;;
				}
			}
		}//for

	}//while
	cout<<0<<endl;
}

int main()
{
//	freopen("E:/代码2/poj_1915/Debug/in.txt","r",stdin);
//	freopen("E:/代码2/poj_1915/Debug/out.txt","w",stdout);
	int n;
	cin>>n;
	for(int s=0;s<n;s++)
	{
		/*cin>>chessSize;
		stepNode stepSour,stepDest;
		cin>>stepSour.x>>stepSour.y;
		cin>>stepDest.x>>stepDest.y;
		stepDest.step=stepSour.step=0;
		doSearch(stepSour,stepDest);*/
	}
	return 0;
}

