#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <deque>

using namespace std;

const int NMAX = 110000;

int N, L[NMAX], R[NMAX], sol, A[NMAX];
long long S[NMAX], ans = -1;
int st[NMAX], tail;

int read()
{
	int x = 0;
	char c;
	while((c = getchar()) < '0' || c > '9');
	do
	{
		x = (x << 1) + (x << 3) + c - '0';
	}while((c = getchar()) >= '0' && c <= '9');
	return x;
}

int main()
{
	int i, x;
	long long tmp;
	scanf("%d", &N);
	for(i = 1;i <= N;i += 1)
	{
		A[i] = read();
		S[i] = S[i - 1] + A[i];
	}
	A[0] = A[N + 1] = -1;
	for(i = 1;i <= N + 1;i += 1)
	{
		while(tail && A[st[tail - 1]] > A[i])
		{
			x = st[--tail];
			R[x] = i - 1;
		}
		st[tail++] = i;
	}
	tail = 0;
	for(i = N;i >= 0;i -= 1)
	{
		while(tail && A[st[tail - 1]] > A[i])
		{
			x = st[--tail];
			L[x] = i + 1;
		}
		st[tail++] = i;
	}
	tail = 0;
	for(i = 1;i <= N;i += 1)
	{
		tmp = (S[R[i]] - S[L[i] - 1]) * A[i];
		if(tmp > ans)
		{
			ans = tmp;
			sol = i;
		}
	}
	printf("%lld\n", ans);
	printf("%d %d\n", L[sol], R[sol]);
	exit(0);
}
