#pragma once
#include <iostream>
using namespace std;

template<class T1, class T2>
class Person {
	Person(T1 name, T2 age);
	void showPerson();

public:
	T1 m_Name;
	T2 m_Age;
};

