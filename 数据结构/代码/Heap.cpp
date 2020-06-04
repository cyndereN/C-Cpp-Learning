#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int NMAX = 10000;

int N, L, H[NMAX];

void maintain(int x)
{
	int l = 2 * x, r = 2 * x + 1, f = x;
	if(l <= N && H[l] < H[f])
		f = l;
	if(r <= N && H[r] < H[f])
		f = r;
	if(f != x)
	{
		swap(H[f], H[x]);
		maintain(f);
	}
}

void buildHeap()
{
	int i;
	for(i = (N>>1);i;i -= 1)
		maintain(i);
}

void bubble(int x)
{
	int i;
	for(i = N;i > 1;i >>= 1)
	{
		if(H[i] < H[i>>1])
			swap(H[i], H[i>>1]);
		else
			break;
	}
}

void insert(int x)
{
	H[++N] = x;
	bubble(N);
}

int pop()
{
	swap(H[1], H[N]);
	N -= 1;
	maintain(1);
	return H[N + 1];
}

int main()
{
	int i;
	scanf("%d", &L);
	N = L;
	for(i = 1;i <= L;i += 1)
		scanf("%d", &H[i]);
	buildHeap();
	L += 1;
	insert(-1);
	for(i = 1;i <= L;i += 1)
		printf("%d ", pop());
	printf("\n");
	exit(0);
}
