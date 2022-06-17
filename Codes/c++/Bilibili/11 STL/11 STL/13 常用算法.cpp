// 常用遍历算法:
// for_each // 遍历容器
// transform // 搬运


// for_each
void print01() {
	cout << val << " ";
}
for_each(v.begin(), v.end(), print01);


class print02 {
public:
	void operator()(int val) {
		cout << val << " ";
	}
};
for_each(v.begin(), v.end(), print02());

// transform
// 目标容器需要提前开辟空间
transform(iterator beg1, iterator end1, iterator beg2, _func); // _func类似回调函数

/*********************************************/
// 常用查找算法：
// find			 // 查找元素
// find_if		 // 按条件查找
// adjacent_find // 查找相邻重复元素
// binary_search // 二分查找法
// count         // 统计元素个数
// count_if      // 按条件统计元素个数


// find(iterator beg, iterator end, elem);
// 找到返回指定位置迭代器，找不到返回结束迭代器
class Person {
public:
	Person(string name, int age) {
		this->m_name = name;
		this->m_age = age;
	}

	// 重载== 底层find知道如何对比person数据类型
	bool operator==(const Person& p) {
		if (this->m_name == p.mname && this->m_age == p.m_age) {
			return true;
		}
		return false;
	}

	string m_name;
	int m_age;
};
Person pp("cc", 20);
vector<Person>::iterator it = find(v.gebin(), v.end(), pp);
if (it == v.end()) {
	cout << "没有找到" << endl;
}
else {
	cout << "找到元素" << it->m_age << endl;
}

// find_if(iterator beg, iterator end, _Pred);
class Greater20 {
public:
	bool operator()(Person& p) {
		return p.m_age > 20;
	}
};

vector<Person>::iterator it = find_if(v.begin(), v.end(), Greater20());



// adjacent_find(iterator beg, iterator end) 找相邻重复元素， 返回第一个相邻重复的元素的迭代器

// binary_search(iterator beg, iterator end, elem) // 返回bool类型，在无需序列中不可用

// count(iterator beg, iterator end, elem)  // 统计元素出现次数

// count_if(iterator beg, iterator end, _Pred);

/*********************************************/
// 常用排序算法：
// sort

// random_shuffle(iterator beg, iterator end); // 打乱顺序

// merge(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);
// 容器元素合并，并存储到另一容器中
// 两个容器必须是有序的
// dest, 目标容器开始迭代器
// 提前给目标容器分配空间

// reverse(iterator beg, iterator end);

/*********************************************/
// 常用拷贝和替换算法：
// copy(iterator beg, iterator end, iterator dest);
// 容器内指定范围的元素拷贝到另一容器中
// 提前给目标容器分配空间

// replace(iterator beg, iterator end, oldvalue, newvalue);
// 将区域内旧元素替换成新元素

// replace_if(iterator beg, iterator end, _Pred, newvalue);

// swap(container c1, container c2);




/*********************************************/
// 常用算数生成算法：
// accumulate(v.begin(), v.end(), value);
// 计算容器元素累计总和, value是起始值

// fill(v.begin(), v.end(), value);
// 填充进容器

/*********************************************/
// 常用集合算法
// set_intersection 
// 返回值是交集中最后一个元素的位置
vTarget.resize(min(v1.size(), v2.size())); // 最特殊情况，大容器包含小容器
vector<int>::iterator itEnd = set_intersection(v1.begin(), v1.end(), v2.begin(), v2.begin(), vTarget.begin());
for_each(vTarget.begin(), itEnd, myPrint);


// set_union
// vTarget.resize(v1.size() + v2.size());


// set_difference
// vTarget.resize(max(v1.size(), v2.size()));



