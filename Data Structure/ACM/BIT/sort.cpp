#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool cmp(int a, int b){
    return a>b;
}

int main(){
    vector<int> arr{2, 3, 1, 5, 4};
    arr.push_back(6);
    sort(arr.begin(), arr.end(), cmp);  //降序
    vector<int> :: iterator p1 = arr.begin();
    for(p1 ; p1!=arr.end(); p1++){
        cout << *p1 << endl;
    }
    return 0;
}

nth_element(arr.begin(), arr.begin()+n, arr.end());
swap(arr[0], arr[1]); //O(1)
reverse(arr.begin(), arr.end()); //O(n)
int newLength = unique(arr.begin(), arr.end()) - arr.begin(); //新数组长度
//unique: 假设arr已经排好序，使arr中不出现重复数字，返回去重后数组的结束指针(多余的元素不算)
bool isExist = binary_search(arr.begin(), arr.end(), 1); //O(logn)查找对应元素是否存在
int firstLoc = lower_bound(arr.begin(), arr.end(), 2) - arr.begin();
int lastLoc = upper_bound(arr.begin(), arr.end(), 2) - arr.begin();
//如果把一个数插入有序数组，那么他应该插入哪个位置。返回第一个/最后一个位置的指针