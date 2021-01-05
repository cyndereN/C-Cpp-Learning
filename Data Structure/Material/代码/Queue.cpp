#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <deque>

using namespace std;

const int QMAX = 100;

queue<int> Q1;
deque<int	> Q2;
int Q3[QMAX], head, tail;

int main()
{
	Q1.push(1);
	Q1.push(2);
	Q1.push(3);
	printf("%d\n", Q1.front());
	Q1.pop();
	printf("%d\n\n", Q1.front());
	
	Q2.push_back(1);
	Q2.push_back(2);
	Q2.push_back(3);
	printf("%d\n", Q2.front());
	Q2.pop_front();
	printf("%d\n\n", Q2.front());
	
	Q3[tail++] = 1;
	Q3[tail++] = 2;
	Q3[tail++] = 3;
	printf("%d\n", Q3[head]);
	head += 1;
	printf("%d\n", Q3[head]);
	exit(0);
}
