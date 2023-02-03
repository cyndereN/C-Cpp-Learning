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


// ----------------------------
// ----------------------------
// ----------------------------
// ----------------------------

#include <iostream>
 
using namespace std;
 
double vals[] = {10.1, 12.6, 33.1, 24.1, 50.0};
 
double& setValues(int i) {  
   double& ref = vals[i];    
   return ref;   // 返回第 i 个元素的引用，ref 是一个引用变量，ref 引用 vals[i]
 
 
}
 
// 要调用上面定义函数的主函数
int main ()
{
 
   cout << "改变前的值" << endl;
   for ( int i = 0; i < 5; i++ )
   {
       cout << "vals[" << i << "] = ";
       cout << vals[i] << endl;
   }
 
   setValues(1) = 20.23; // 改变第 2 个元素
   setValues(3) = 70.8;  // 改变第 4 个元素
 
   cout << "改变后的值" << endl;
   for ( int i = 0; i < 5; i++ )
   {
       cout << "vals[" << i << "] = ";
       cout << vals[i] << endl;
   }
   return 0;
}