#include <iostream>
using namespace std;
int * func(){
    // 利用new关键字可以将数据开辟到堆区
    int* p = new int(10);
    return p;
}

void test(){
    int * arr = new int[10];  // 堆区创建10整型数据的数组

    for(int i = 0; i < 10; i++){
        arr[i] = i + 100;
        cout << arr[i] << endl;
    }

    delete[] arr; // 释放数组要加中括号
}

int main(){
    int *p = func();

    cout << *p << endl;

    delete p;  // 释放


    test();
    

    return 0;
}