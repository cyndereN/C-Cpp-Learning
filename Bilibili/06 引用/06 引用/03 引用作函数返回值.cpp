#include<bits/stdc++.h>
using namespace std;

// 引用作函数的返回值
// 1. 不要返回局部变量的引用

int& test01() { // 错误案例
	int a = 10; // 局部变量存放在栈区
	return a;
}

int& test02() {
	static int a = 10;  // 静态变量，存放在全局区
	return a;
}


int main() {

	int& ref = test02();

	test02() = 1000;  // 2. 如果函数的返回值是引用，这个函数调用可以作为左值
	return 0;
}