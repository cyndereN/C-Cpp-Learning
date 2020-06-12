#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

struct Node
{
	int value;
	Node *next;
};

Node *create(int value)
{
	Node *n = (Node *)malloc(sizeof(Node));
	n->value = value;
	n->next = NULL;
	return n;
}

Node *insert(Node *pos, int value)
{
	Node *n = create(value);
	n->next = pos->next;
	pos->next = n;
	return n;
}

int main()
{
	Node *head, *tail, *i;
	tail = head = create(1);
	tail = insert(head, 10);
	insert(tail, 53);
	for(i = head;i;i = i->next)
		printf("%d\n", i->value);
}
