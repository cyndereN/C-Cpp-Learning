// 算术仿函数，关系仿函数，逻辑仿函数
#include <functional>

negate<int> n;
cout << n(50) << endl; //-50

sort(v.begin(), v.end(), greater<int>());

vector<bool> v2;
v2.resize(v.size());
transform(v.begin(), v.end(), logical_not<bool>());