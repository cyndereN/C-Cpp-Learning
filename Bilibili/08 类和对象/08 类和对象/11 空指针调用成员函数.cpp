#include <iostream>
using namespace std;
// 空指针可以调用成员函数，不可以调用虚函数。因为虚函数是
// 通过虚函数表来调用的，虚函数表是在构造函数中初始化的，而空指针没有构造函数，所以不能调用虚函数
class Person {
public:
	void showClassName() {
		cout << "this is Person class" << endl;
	}

	void showPersonAge() {
		// !解决：
		if (this == NULL)  return;
		cout << "age = " << m_age << endl;
	}

	int m_age;
};

void test01() {
	Person* p = NULL;
	p->showClassName(); // 没崩
	p->showPersonAge(); // !崩了，因为编译器默认加了this->在属性前面，而传入的指针是NULL
}