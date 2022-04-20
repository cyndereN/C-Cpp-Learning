#include <queue>
using namespace std;

queue<int> que;
que.push(1);  // 向队列中添加元素	O(1)
int frontElement = que.front();  // 返回队头的元素	O(1) back()	返回队尾元素	O(1)
que.pop();  // 从队列中取出并删除元素	O(1)
que.empty();  // 在队列为空时返回true	O(1)
que.size();  // 返回队列中的元素数	O(1)

priority_queue<int> que2;
que2.push(1);
int minElement = que2.top();
que2.pop();   
que2.empty();  
que2.size();  


#include <iostream>
#include <queue>
 
using namespace std;
 
void showq(queue <int> gq)
{
    queue <int> g = gq;
    while (!g.empty())
    {
        cout << '\t' << g.front();
        g.pop();
    }
    cout << '\n';
}
 
int main()
{
    queue <int> gquiz;
    gquiz.push(10);
    gquiz.push(20);
    gquiz.push(30);
 
    cout << "The queue gquiz is : ";
    showq(gquiz);
 
    cout << "\ngquiz.size() : " << gquiz.size();
    cout << "\ngquiz.front() : " << gquiz.front();
    cout << "\ngquiz.back() : " << gquiz.back();
 
    cout << "\ngquiz.pop() : ";
    gquiz.pop();
    showq(gquiz);
 
    return 0;
}
