﻿// 链式存储，在物理存储单元上非连续
// 由一系列结点组成，结点由数据域，指针域组成（stl中是双向循环的）

// 可以对任意位置进行快速插入删除
// 遍历速度没有数组快
// 占用空间大

// 迭代器只支持前移后移，属于双向迭代器

list<int> L1(10, 100);
list<int> L2(L1);

L1.swap(L2);

oid showTheContent(list<int> l)
{
	list<int>::iterator it;
	for (it = l.begin(); it != l.end(); it++)
	{
		cout << *it << " ";
	}
	cout << "\n";
}
int main()
{
	// Sample Code to show List and its functions

	list<int> list1, list2;
	int i;
	// inserting at the back
	for (i = 0; i < 10; i++)
		list1.push_back(i + 1);

	//inserting at the front
	for (i = 0; i < 10; i++)
		list2.push_front(i + 1);

	cout << "Content of List 1: ";
	showTheContent(list1);
	cout << "Content of list 2: ";
	showTheContent(list2);

	// sorting the second list from low to high
	list2.sort();
	cout << "Sorted List2 : ";
	showTheContent(list2);


	list2.sort(myCompare);  // from high to low

	bool myCompare(int val1, int val2) {
		return val1 > val2;
	}

	//Removing five elements from front in list1.
	int times = 5;
	while (times--)
	{
		list1.pop_front();
	}
	cout << "Content of List 1: ";
	showTheContent(list1);
	//Removing five elements from the back in list2.
	times = 5;
	while (times--)
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
	list1.insert(++list1.begin(), 5, 10);
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
	if (list1.empty()) cout << "List 1 is now empty\n";
	else cout << "Not Empty\n";

	// use of assign function
	list1.assign(5, 2); // 2 2 2 2 2
	cout << "List 1: ";
	showTheContent(list1);

	list1.clear();


	return 0;
}

// 任何位置的插入删除：O(1)(假设告诉了你插入删除的位置，不需要你线查找再删除)
// 因为是双链表，如果是单链表的话就是O(n)，因为没有保存前一个节点的指针

// 头尾查询：O(1)

// 其他位置查询/遍历：O（N）