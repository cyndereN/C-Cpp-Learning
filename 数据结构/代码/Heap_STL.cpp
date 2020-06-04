#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

const int NMAX = 10000;

int L;
priority_queue<int, vector<int>, less<int> > PQ;
//priority_queue<int, vector<int>, greater<int> >

int main()
{
	int i, x;
	scanf("%d", &L);
	for(i = 1;i <= L;i += 1)
	{
		scanf("%d", &x);
		PQ.push(x);
	}
	for(i = 1;i <= L;i += 1)
	{
		printf("%d ", PQ.top());
		PQ.pop();
	}
	printf("\n");
	exit(0);
}
