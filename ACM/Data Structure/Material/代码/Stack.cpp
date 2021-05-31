#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <stack>
#include <deque>

using namespace std;

const int QMAX = 100;

stack<int> S1;
deque<int> S2;
int S3[QMAX], tail;

int main()
{
	S1.push(1);
	S1.push(2);
	S1.push(3);
	printf("%d\n", S1.top());
	S1.pop();
	printf("%d\n\n", S1.top());
	
	S2.push_front(1);
	S2.push_front(2);
	S2.push_front(3);
	printf("%d\n", S2.front());
	S2.pop_front();
	printf("%d\n\n", S2.front());
	
	S3[tail++] = 1;
	S3[tail++] = 2;
	S3[tail++] = 3;
	printf("%d\n", S3[tail - 1]);
	tail -= 1;
	printf("%d\n", S3[tail - 1]);
	exit(0);
}
