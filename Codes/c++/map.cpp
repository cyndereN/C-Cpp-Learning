#include <string>
#include <map>
#include <unordered_map>
using namespace std;

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