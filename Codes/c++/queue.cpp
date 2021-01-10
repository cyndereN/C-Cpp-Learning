#include <queue>
using namespace std;

queue<int> que;
que.push(1);
int frontElement = que.front();
que.pop();
que.empty();
que.size();

priority_queue<int> que2;
que2.push(1);
int minElement = que2.top();
que2.pop();
que2.empty();
que2.size();