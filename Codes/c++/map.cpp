#include <string>
#include <map>
#include <unordered_map>
using namespace std;


// map由红黑树实现，其元素都是键值对，每个元素的键是排序的准则，每个键只能出现一次，不允许重复
// 增删改查基本是O(log N)
// 优点：适用平衡二叉树实现，便于元素查找，而且可以把值映射到另外一个值，可以创建字典

// 缺点：每次插入都需要调整红黑树，对效率存在一定的影响

// 适用场景：适用于需要储存一个字典，并要求方便的根据key找value的场景


pair<string, int> pr{"xiaoming", 180}; 
pair<int, int> point(1,2);
pair<int, int> origin;

origin = makea_pair(0,0);
origin.first == origin.second;
origin.swap;
//map包含的第一个数据结构，由任意两种类型构成。自带比较函数

map<string, int> studentHeight;
studentHeight["xiaoming"] = 170;
studentHeight["xiaohong"] = 150;
pair<string, int> id;
id = make_pair("someone", 110);
studentHeight.insert(id);
studentHeight.erase("xiaoming");
//map包含的第二个数据结构，可以看成一个超级数组，下标任意类型
//O(logn)，可以insert pair