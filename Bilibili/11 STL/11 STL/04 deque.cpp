//  双端数组 可以对头端进行插入删除

// vector对头部的插入删除效率低，数据量越大，效率越低
// deque对头部的插入速度比vector快
// vector访问元素时的速度比deque快
// vector：所有元素存储在单个连续的物理内存块中。访问元素时（如 vec[i]），CPU 可以直接通过 基地址 + 偏移量 
// 计算出元素的物理地址（O(1) 时间），且连续内存利于缓存预取（Cache Prefetching），减少缓存未命中（Cache Miss）。
// deque：元素被分块存储在多个固定大小的连续内存块（通常是指针数组指向这些块）。访问元素时（如 deq[i]），需要先计算目标块的位置（i / block_size），
// 再计算块内偏移（i % block_size）。虽然也是 O(1)，但多了一次间接寻址，可能引发额外的缓存未命中。


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

// 随机访问 O(1)

// 查找：O(N)