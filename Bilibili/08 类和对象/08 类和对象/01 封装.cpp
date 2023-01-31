#include <bits/stdc++.h>
using namespace std;
// C++面向对象的三大特性为：封装、继承、多态
// C++认为万物皆为对象，对象上有其属性和行为

// 1.封装
// · 将属性和行为作为一个整体，表现生活中的事物
// · 将属性和行为加以权限控制

// 类中的属性和行为统一称为成员
// 属性 成员属性 成员变量
// 行为 成员函数 成员方法


// 2.成员属性设置为私有的优点
// · 可以自己控制读写权限
// · 对于写权限，可以检测数据的有效性

// E.g. 1
// 设计一个圆类
const double PI = 3.14;

class Circle {

	// 访问权限
	// 公共权限
public:
	// 属性
	// 半径
	int m_r;

	// 行为
	// 获取圆的周长
	double calc_perimeter() {
		return 2 * PI * m_r;
	}
};

int main() {
	// 实例化 通过类创建一个对象的过程
	Circle c1;
	c1.m_r = 10;

	return 0;
}

// E.g.2 设计一个立方体类
class Cube {
private:
	int m_L;
	int m_W;
	int m_H;
public:
	void setL(int l) {
		m_L = l;
	}
	int getL() {
		return m_L;
	}
	void setH(int h) {
		m_H = h;
	}
	int getH() {
		return m_H;
	}
	void setW(int w) {
		m_W = w;
	}
	int getL() {
		return m_W;
	}

	int calculate_volume() {
		return m_L * m_W * m_H;
	}

	bool isSameLByClasee(Cube& c) {
		if (m_L == c.getL()) {
			return true;
		}
		return false;
	}
};

bool isSameL(Cube& c1, Cube& c2) {
	if (c1.getL() == c2.getL()) {
		return true;
	}
	return false;
}

// c++ 允许空类，类大小为1（实例化时，会由编译器隐含的添加一个字节）
// 当c++类中有虚函数的时候，会有一个指向虚函数表的指针（vptr），在32位系统分配指针大小为4字节。


// 为什么类内的member variable很多使用指针而不是对象本身？
// 1. 多态行为。对于多态类型，使用指针（或引用）来避免切片：
// 切片的意思就是说：在函数传参处理多态变量时，如果一个派生类对象在向上转换（upcast），
// 用的是传值的方式，而不是指针和引用，那么，这个派生类对象在 upcast 以后，
// 将会被 slice 成基类对象，也就是说，派生类中独有的成员变量和方法都被 slice 掉了，
// 只剩下和基类相同的成员变量和属性。
// class Base { ... };
// class Derived : public Base { ... };

// void fun(Base b) { ... }
// void gun(Base* b) { ... }
// void hun(Base& b) { ... }

// Derived d;
// fun(d);    // oops, all Derived parts silently "sliced" off
// gun(&d);   // OK, a Derived object IS-A Base object
// hun(d);    // also OK, reference also doesn't slice

// 2. 减小内存开销。stack memory is smaller than heap memory.
// 对于非多态类型，指针（或引用）将避免复制可能昂贵的对象。
// Base b;
// fun(b);  // copies b, potentially expensive 
// gun(&b); // takes a pointer to b, no copying
// hun(b);  // regular syntax, behaves as a pointer

// 3. 通过解耦编译单元来减少编译时间： 如果对象都是指针指向的，那么只需要这个类型的前向声明就可以。这可以分离编译过程的各个部分，会显著提高编译时间。
// https://blog.csdn.net/linkvivi/article/details/85325353
// // add.cpp:
// int add(int x, int y)
// {
//     return x + y;
// }

// // main.cpp:
// #include <iostream>
// int add(int x, int y); // 前向声明
// int main()
// {
//     std::cout << "The sum of 3 and 4 is " << add(3, 4) << std::endl;
//     return 0;
// }

// 4. 可以表示对象是可选的（optional）： 
// 指针可以被赋值为 nullptr，也就是空的意思，你可以通过设置指针为 nullptr，来表达忽略该变量的含义