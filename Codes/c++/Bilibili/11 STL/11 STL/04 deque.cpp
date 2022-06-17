//  双端数组 可以对头端进行插入删除

// vector对头部的插入删除效率低，数据量越大，效率越低
// deque对头部的插入速度比vector快
// vector访问元素时的速度比deque快

// deque有个中控器，维护每段缓冲区中的内容（类似指针数组），使得像一片连续的内存

void printDeque(const deque<int>& d) {
	for (deque<int>::const_iterator it = d.begin(); it != d.end(); it++) {
		// *it = 100; 容器中的数据不可以修改了
		cout << *it << " ";
	}
	cout << endl;
}

// 对于支持随机访问的迭代器的容器都可以利用sort算法直接对其进行排序
d.sort(d.begin(), d.end()); // 默认从小到大升序


// 头部尾部插入删除：O(1)

// 中间插入删除：O(N)

// 查找：O(N)