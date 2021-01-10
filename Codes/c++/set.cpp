#include <set>
#include <unordered_set>
using namespace std;

set<int> st;       //自带去重
st.insert(1);
st.find(1);
st.erase(1);

unordered_set<int> mst;    //允许重复
mst.insert(1);
mst.count(1);

//O(logn)时间内查找、删除、添加