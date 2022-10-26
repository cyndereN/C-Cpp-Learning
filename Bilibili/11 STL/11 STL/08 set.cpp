// 所有元素在插入时自动被排序

// set/multiset属于关联式容器，底层结构是二叉树

// multiset允许重复元素出现

set<int> st;
st.insert(1);
st.size();
st.empty();
st1.swap(st2);
st.find(1); // 若存在返回迭代器，不存在返回st.end();
st.erase(1);
st.clear();
st.count(1);

// 利用仿函数可以改变排序规则
class MyCompare {
public:
	bool operator()(int v1, int v2) {
		return v1 > v2;
	}
};

// 指定排序规则改为从大到小
set<int, MyCompare>s2;
s2.insert(1);
...

// set由红黑树实现，其内部元素依照其值自动排序，每个元素只出现一次，不允许重复(红黑树是平衡二叉树的一种)
// 增删改查近似：O(log N)
// 优点：使用平衡二叉树实现，便于元素查找，而且保持了元素的唯一性，支持自动排序

// 缺点：每次插入元素，都需要调整红黑树，效率有一定的影响

// 适用场景：适用于经常查找一个元素是否在某集群中并且不要排序的场景

// hash_map, hash_set, hash_multimap, and hash_multiset采用哈希表实现，不同操作的时间复杂度为：
// 插入:O(1)，最坏情况O(N)。
// 查看:O(1)，最坏情况O(N)。
// 删除:O(1)，最坏情况O(N)。