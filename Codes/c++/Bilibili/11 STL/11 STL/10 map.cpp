// map容器所有元素都是pair
// pair中第一个元素为key(键值)，起到索引作用，第二个元素为value(实值)
// 所有元素会根据元素键值自动排序

// map/multimap属于关联式容器，底层结构用二叉树实现

map<int, int> m;
m.insert(pair<int, int>(1, 10));
m.insert(pair<int, int>(2, 20));
m.insert(map<int, int>::value_type(3, 30));
m[4] = 40;
m.size();
m.empty();
m.swap(mp);
m.erase(pos); // 删除pos迭代器所指的元素，返回下一个元素的迭代器
m.erase(beg, end);

map<int, int>::iterator = m.find(key);
m.count(key);

// map由红黑树实现，其元素都是键值对，每个元素的键是排序的准则，每个键只能出现一次，不允许重复
// 增删改查基本是O(log N)
// 优点：适用平衡二叉树实现，便于元素查找，而且可以把值映射到另外一个值，可以创建字典

// 缺点：每次插入都需要调整红黑树，对效率存在一定的影响

// 适用场景：适用于需要储存一个字典，并要求方便的根据key找value的场景

// hash_map, hash_set, hash_multimap, and hash_multiset采用哈希表实现，不同操作的时间复杂度为：
// 插入:O(1)，最坏情况O(N)。
// 查看:O(1)，最坏情况O(N)。
// 删除:O(1)，最坏情况O(N)。