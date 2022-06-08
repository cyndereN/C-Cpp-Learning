// 标准模板库
// contatiner, algorithm, iterator
// 容器和算法之间通过迭代器进行无缝连接
// 几乎所有代码都采用了类模板和函数模板

// 六大组件
// 容器、算法、迭代器、仿函数、适配器、空间配置器

// 容器：将运用最广泛的一些数据结构实现出来
// 序列式容器：强调值的排序，序列式容器中的每个元素均有固定位置
// 关联式容器：二叉树结构，各元素之间没有严格的物理上的顺序关系

// 算法：问题的解法，有限的步骤，解决逻辑或数学上的问题
// 质变算法：运算过程中会更改区间内的元素的内容。例如拷贝，删除，替换等等
// 非质变算法：指运算过程中不会更改区间内的元素内容。例如查找、计数、遍历、寻找极值等等。

// 迭代器
// 常用的为双向迭代器和随机访问迭代器

// 1. 常用容器Vector
// 可以插入数据并遍历数组

void test01() {
	vector<int> v;

	v.push_back(10);
	v.push_back(20);
	v.push_back(30);
	v.push_back(40);


	// 第一种
	vector<int>::iterator itBegin = v.begin();
	vector<int>::iterator itEnd = v.end();

	while (itBegin != itEnd) {
		cout << *itBegin << endl;
		itBegin++;
	}

	// 第二种
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		cout << *it << endl;
	}

	// 第三种
	void myPrint(int val) {
		cout << val << endl;
	}
	for_each(v.begin(), v.end(), myPrint);
}
