// 和数组类似，也称为单端数组

// 不同之处在于数组是静态空间，vector可以动态扩展
// 动态扩展：并不是在原空间后续接新空间，而是找更大的内存空间，然后将原数据拷贝新空间，释放原空间

// vector 的迭代器支持随机访问

vector<int> v4(10, 100);

vector<int> v4;
v4.assign(10, 100);  // 十个100

vector<int> v3;
v3.assign(v.begin(), v1.end());

v.empty()  // 是否为空
v.capacity()
v.size()
v.resize(int num);
v.resize(int num, elem);   // 多出来的以elem填充 少则删除

v.push_back();
v.pop_back();
v.insert(v.begin(), 100); // 第一个参数是迭代器
v.insert(v.begin(),2, 100);
v.erase(v.begin());
v.erase(v.begin(), v.end()); // 清空
v.clear();

v[i]; v.at(i);
v.front() // 第一个元素
v.end() // 最后一个元素

// vector容器互换
v1.swap(v2)
// 巧用swap可以收缩内存空间
vector<int>(v).swap(v); // 匿名对象没有进行绑定操作会立刻析构

// 预留空间
reserve(int len); // 容器预留len个元素长度，预留位置不初始化，元素不可访问
vector<int> v;

v.reserve(100000);

int num = 0;  // 统计开辟次数
int* p = NULL;
for (int i = 0; i < 10000; i++) {
	v.push_back(i);

	if (p != &v[0]) {
		p = &v[0];
		num++; // 30次，reserve之后1次
	}
}



// 头部插入删除：O(N)

// 尾部插入删除:O(1)

// 中间插入删除：O(N)

// 查找：O(N)