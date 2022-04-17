// list由双向链表实现，元素存放在堆中，每个元素都是存放在一块内存中，它的内存空间可以是不连续的，通过指针来进行数据访问，
// 这个特点使得它的随机储存变得非常的没有效率，但是由于链表的特点，它可以很有效率的支持任意地方的插入和删除操作

// 任何位置的插入删除：O(1)(假设告诉了你插入删除的位置，不需要你线查找再删除)

// 头尾查询：O(1)

// 其他位置查询：O（N）

#include <iostream>
#include <bits/stdc++.h>
using namespace std;


void showTheContent(list<int> l)
{
     list<int>::iterator it;
      for(it=l.begin();it!=l.end();it++)
   {
       cout <<  *it << " ";
   }
   cout << "\n";
}
int main()
{
   // Sample Code to show List and its functions

   list<int> list1,list2;
   int i;
   // inserting at the back
   for(i=0;i<10;i++)
    list1.push_back(i+1);

   //inserting at the front
   for(i=0;i<10;i++)
    list2.push_front(i+1);

   cout << "Content of List 1: ";
   showTheContent(list1);
   cout << "Content of list 2: ";
   showTheContent(list2);

   // sorting the second list
   list2.sort();
   cout << "Sorted List2 : ";
   showTheContent(list2);

   //Removing five elements from front in list1.
   int times = 5;
   while(times--)
   {
       list1.pop_front();
   }
   cout << "Content of List 1: " ;
   showTheContent(list1);
   //Removing five elements from the back in list2.
   times=5;
   while(times--)
   {
       list2.pop_back();
   }
   cout << "Content of List 2: ";
   showTheContent(list2);

    //seek the first element of list 1
    cout << list1.front() << " is now at the front in list 1\n";
    // seek the last element in list 2
    cout << list2.back() << " is now the last element in list 2\n";

    //Inserting elements in list 1.
    list1.insert(list1.begin(),5,10);
    cout << "After Insertion list 1: ";
    showTheContent(list1);

    //remove() to remove all the elements with value 10.
    list1.remove(10);
    cout << "After Removal list 1: ";
    showTheContent(list1);

    // size() to know the number of elements
    cout << "No. of elements in list 1: ";
    cout << list1.size() << "\n";

    //Reversing the content of list 2
    list2.reverse();
    cout << "Reversed list 2: ";
    showTheContent(list2);

    //erasing first element of list 2
    list2.erase(list2.begin());
    cout << "After erasing from list 2: ";
    showTheContent(list2);

    //Removing all elements from list 1.
    list1.clear();
    // Use of empty() function
    if(list1.empty()) cout << "List 1 is now empty\n";
    else cout << "Not Empty\n";

    // use of assign function
    list1.assign(5,2); // 2 2 2 2 2
    cout << "List 1: ";
    showTheContent(list1);


    return 0;
}

// vector

// 特点:快速的随机储存，快速的在最后插入删除元素

// 适用：需要高效随机储存，需要高效的在末尾插入删除元素，不需要高效的在其他地方插入和删除元素

// deque

// 特点：比较快速的随机存储(比vector的慢),快速的在头尾插入删除元素

// 适用：需要随机储存，需要高效的在头尾插入删除元素的场景

// list

// 特点：快速在任意位置插入删除元素，快速访问头尾元素

// 适用：需要大量插入删除操作，不关心随机储存的场景

// deque可以看作是vector和list的折中方案