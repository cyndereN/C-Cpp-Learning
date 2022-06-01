#include <iostream>
using namespace std;

// 重载递增运算符 分两种 前置++和后置++
class MyInteger {
	friend ostream& operator<<(ostream& cout, MyInteger myint);
public:
	MyInteger() {
		m_num = 0;
	}

	// 重载前置++
	MyInteger& operator++() {//返回引用为了一直对一个数据进行递增操作, e.g.++(++a)
		m_num++;
		return *this;
	}

	// 重载后置++
	// int 代表占位参数，可以用于区分前置和后置递增
	MyInteger operator++(int) {
		// 先记录当时结果
		MyInteger temp = *this;
		// 后递增
		m_num++;
		// 最后将记录结果返回
		return temp;  // 一定返回值，原生c++也没有 (a++)++操作
	}

private:
	int m_num;
};

// 重载左移
ostream& operator<<(ostream& cout, MyInteger myint) {
	cout << myint.m_num;
	return cout;
}

void test01() {
	MyInteger myint;
	cout << myint << endl;
}

int main() {

	system("pause");
	return 0;
}