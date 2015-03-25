#include<iostream>
using namespace std;

const int large=200030;

typedef struct
{
	int x;
	int step;
}pos;

int n,k;
bool vist[large];   //数组较大，必须开为全局数组，不然肯定RE
pos queue[large];

void BFS(void)
{
	int head,tail;
	queue[head=tail=0].x=n;
	queue[tail++].step=0;/*

	vist[n]=true;
*/
	while(head<tail)
	{
		pos w=queue[head++];

		if(w.x==k)
		{
			cout<<w.step<<endl;
			break;
		}

		if(w.x-1>=0 && !vist[w.x-1])     //w.x-1>=0  是剪枝
		{
			vist[w.x-1]=true;
			queue[tail].x=w.x-1;
			queue[tail++].step=w.step+1;
		}
		if(w.x<=k && !vist[w.x+1])     //w.x<=k  是剪枝
		{
			vist[w.x+1]=true;
			queue[tail].x=w.x+1;
			queue[tail++].step=w.step+1;
		}
		if(w.x<=k && !vist[2*w.x])     //w.x<=k  是剪枝
		{
			vist[2*w.x]=true;
			queue[tail].x=2*w.x;
			queue[tail++].step=w.step+1;
		}
	}
	for(int s=0;s<=tail;s++)
		cout<<s<<":step("<<queue[s].step<<"),"<<queue[s].x<<"        vist:"<<vist[s]<<endl;

	return;
}

int main(void)
{
	while(cin>>n>>k)
	{
		memset(vist,false,sizeof(vist));
		BFS();
	}

	return 0;
}