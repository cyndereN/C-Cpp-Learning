#include <iostream>
using namespace std;

int main() {

	// 引用: 给变量起别名
	// 语法：数据类型 &别名 = 原名
	// int &b = a;
	// b = 20;
	// cout << a << endl; // 也是20

	// 注意事项：
	// 1. 必须初始化
	// 2. 初始化之后不可更改

	int a = 10;
	// int &b； //错误，必须初始化
	int& b = a;

	int c = 20;

	b = c; // 赋值操作，而不是更改引用



	return 0;
}