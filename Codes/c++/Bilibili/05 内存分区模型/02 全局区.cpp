#include <iostream>
using namespace std;

// 全局变量
int g_a = 10;
int g_b = 10;

// const 修饰的全局变量 全局常量
const int c_g_a = 10;
const int c_g_b = 10;
int main(){
    // 全局区
    
    // 全局变量、静态变量、常量

    // 创建普通局部变量
    int a = 10;
    int b = 10;

    cout << "局部变量a的地址: " << (int)&a << endl;
    cout << "局部变量b的地址: " << (int)&b << endl;

    cout << "全局变量a的地址: " << (int)&g_a << endl;
    cout << "全局变量b的地址: " << (int)&g_b << endl;

    // 静态变量 
    static int s_a = 10;
    static int s_b = 10;
    cout << "静态变量a的地址: " << (int)&s_a << endl;
    cout << "静态变量b的地址: " << (int)&s_b << endl;

    // 常量
    // 字符串常量
    cout << "字符串常量的地址为： " << (int)&"hello_world" << endl;

    // const 修饰的变量
    // const修饰的全局变量，const修饰的局部变量
    cout << "全局常量a的地址: " << (int)&c_g_a << endl;
    cout << "全局常量b的地址: " << (int)&c_g_b << endl;

    // const修饰的局部变量
    const int c_l_a = 10;
    const int c_l_b = 10;
    cout << "局部常量a的地址: " << (int)&c_g_a << endl;
    cout << "局部常量b的地址: " << (int)&c_g_b << endl;

    char *p3="123456";   //123456\0在常量区，p3在栈上。

    return 0;

}