#include <cstdio>
#include <queue>

using namespace std;

const int MAXN = 100001;

int N, K;

int vis[MAXN];
int ret[MAXN];

queue<int> q;

int BFS(int s, int d)
{
	if (s == d) return 0;
	q.push(s);
	
	int cur;
	
	while (!q.empty())
	{
		cur = q.front();
		q.pop();
		
		//if (cur == d) break;
		
		// vis[cur] = 1;
		
		/*
			注意BFS的概念，这里的做法是：如果起点不是终点，把起点放入队列。然后搜索起点周围的节点。注意标记为访问的时间很重要，
			并不是在POP的时候标记，而是在以POP出节点为中心向四周扫描的时候，将周围的邻居标记。并且考察邻居是否为终点。而不是考察POP
			出的那个节点是否为终点。这样做才能保证BFS找到的第一个解是最优解。
		*/
		
		if (cur + 1 < MAXN && !vis[cur + 1])
		{
			q.push(cur + 1);
			ret[cur + 1] = ret[cur] + 1;
			vis[cur + 1] = 1;
		}
		
		if (cur + 1 == d) break;
		
		if (cur - 1 >= 0 && !vis[cur - 1])
		{
			q.push(cur - 1);
			ret[cur - 1] = ret[cur] + 1;
			vis[cur - 1] = 1;
		}
		
		if (cur - 1 == d) break;
		
		if (cur << 1 < MAXN && !vis[cur << 1])
		{
			q.push(cur << 1);
			ret[cur << 1] = ret[cur] + 1;
			vis[cur << 1] = 1;
		}
		
		if (cur << 1 == d) break;
	};
	
	return ret[d];
}

int main()
{
	scanf("%d %d", &N, &K);
	printf("%d/n", BFS(N, K));
	return 0;
}