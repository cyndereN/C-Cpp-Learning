// 无法遍历， 只有栈顶元素可以访问到
// 可以判断为空
// 可以返回元素个数

stack<int> sta;

sta.push(1);  // 向栈中添加元素 O(1)
int topElement = sta.top();  //返回栈顶元素 O(1)
sta.pop();     // 从栈中取出并删除元素	O(1)

sta.empty();  // 在栈为空时返回true	O(1)
sta.size();   // 返回栈中的元素数	O(1)

