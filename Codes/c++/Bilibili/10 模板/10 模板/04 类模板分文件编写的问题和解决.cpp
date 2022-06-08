#include <iostream>
using namespace std;
#include <string>

// 第一种解决方式直接包含头文件
// #include "person.h"
#include "person.cpp"

// 第二种，将.h和.cpp写到一起，将后缀名改为.hpp文件
#include "person.hpp"

template<class T1, class T2>
class Person {
	Person(T1 name, T2 age);
	void showPerson();

public:
	T1 m_Name;
	T2 m_Age;
};

template<class T1, class T2>
Person<T1, T2>::Person(T1 name, T2 age) {
	this->m_Name = name;
	this->m_Age = age;
}

template<class T1, class T2>
void Person<T1, T2>::showPerson() {
	cout << "姓名： " << this->m_Name << " 年龄: " << this->m_Age << endl;
}

void test01() {
	Person<string, int> p("Jerry", 18);
	p.showPerson();
}