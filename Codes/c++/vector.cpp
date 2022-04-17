#include <vector>
vector<int> arr(100);
int _arr[100];
vector<int> list;

for(int i=0; i<100 ; i++){
    scanf("%d", &arr[i]);
    cout << arr[i] << endl;
}

for(int i=0; i<100; i++){
    int a;
    cin >> a;
    list.push_back(a);
    printf("%d\n", list[i]);
}

for(int i=0; i<list.size() ; i++){
    printf("%d", arr[i]);
}

vector<int> arr1[100];
int arr2[100];
vector<int> :: iterator p1 = arr1.begin();
int* p2 = arr2;

for(p1=arr1.begin(); p1!=arr1.end(); p1++){
    cout << *p1 << endl;
}
for(p2=arr2, int i=0; i<100 ; i++, p2++){
    cout << *p2 << endl;
}

list.size() //O(1)
list.clear() //O(n)
list.empty() //O(1)
list.end() //O(1)，实际不存在
list.erase(p1) //O(n), 删除
list.push_back(1)  //O(1)
list.pop_back()  //O(1)


// 头部插入删除：O(N)

// 尾部插入删除:O(1)

// 中间插入删除：O(N)

// 查找：O(N)