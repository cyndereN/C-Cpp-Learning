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

bool isSameL(Cube &c1, Cube &c2) {
	if (c1.getL() == c2.getL()) {
		return true;
	}
	return false;
}