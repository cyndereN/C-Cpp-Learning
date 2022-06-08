#include <iostream>
using namespace std;
#include <string>

// ��һ�ֽ����ʽֱ�Ӱ���ͷ�ļ�
// #include "person.h"
#include "person.cpp"

// �ڶ��֣���.h��.cppд��һ�𣬽���׺����Ϊ.hpp�ļ�
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
	cout << "������ " << this->m_Name << " ����: " << this->m_Age << endl;
}

void test01() {
	Person<string, int> p("Jerry", 18);
	p.showPerson();
}