stack<int> sta;
sta.push(1);  // 向栈中添加元素 O(1)
int topElement = sta.top();  //返回栈顶元素 O(1)
sta.pop();     // 从栈中取出并删除元素	O(1)
sta.empty();  // 在栈为空时返回true	O(1)
sta.size();   // 返回栈中的元素数	O(1)

#include <iostream>
#include <stack>
 
using namespace std;
 
template<class T>
void showstack(stack<T> s)
{
    while (!s.empty()) // 如果栈s非空
    {
        cout << ' ' << s.top(); //输出栈顶元素
        s.pop(); // 将栈顶元素弹出栈
    }
    cout << '\n';
}
 
int main ()
{
    stack <int> s;
    s.push(10); // 将元素10压入栈中
    s.push(30);
    s.push(20);
    s.push(5);
    s.push(1);
 
    cout << "The stack s is : ";
    showstack<int>(s); // 显示栈中的元素
 
    cout << "\ns.size() : " << s.size(); // 输出栈的大小（即：栈中元素的个数）
    cout << "\ns.top() : " << s.top(); // 输出暂定元素
 
 
    cout << "\ns.pop() : ";
    s.pop(); // 将栈顶元素弹出栈
 
    showstack<int>(s); // 显示栈中的元素(此时栈中元素已全部出栈)
 
    return 0;
}