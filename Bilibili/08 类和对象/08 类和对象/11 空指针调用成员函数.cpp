#include <iostream>
using namespace std;

class Person {
public:
	void showClassName() {
		cout << "this is Person class" << endl;
	}

	void showPersonAge() {
		// 解决：
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