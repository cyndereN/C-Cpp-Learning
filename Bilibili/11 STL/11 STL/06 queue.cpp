// 也不允许遍历

queue<int> que;
que.push(1);  // 向队列中添加元素	O(1)
int frontElement = que.front();  // 返回队头的元素O(1) back()	返回队尾元素	O(1)
que.pop();  // 从队列中取出并删除元素	O(1)

que.empty();  // 在队列为空时返回true	O(1)
que.size();  // 返回队列中的元素数	O(1)
