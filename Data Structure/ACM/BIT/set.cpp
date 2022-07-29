#include <set>
#include <unordered_set>
using namespace std;

set<int> st;       //自带去重
st.insert(1);
st.find(1);
st.erase(1);

// set由红黑树实现，其内部元素依照其值自动排序，每个元素只出现一次，不允许重复(红黑树是平衡二叉树的一种)
// 增删改查近似：O(log N)
// 优点：使用平衡二叉树实现，便于元素查找，而且保持了元素的唯一性，支持自动排序

// 缺点：每次插入元素，都需要调整红黑树，效率有一定的影响

// 适用场景：适用与经常查找一个元素是否在某集群中并且不要排序的场景

// multiset和set相同，只不过它允许重复元素，也就是说multiset可包括多个数值相同的元素

// hash_map, hash_set, hash_multimap, and hash_multiset采用哈希表实现，不同操作的时间复杂度为：
// 插入:O(1)，最坏情况O(N)。
// 查看:O(1)，最坏情况O(N)。
// 删除:O(1)，最坏情况O(N)。