#include <iostream>
using namespace std;

class Person {
public:
	void showClassName() {
		cout << "this is Person class" << endl;
	}

	void showPersonAge() {
		// �����
		if (this == NULL)  return;
		cout << "age = " << m_age << endl;
	}

	int m_age;
};

void test01() {
	Person* p = NULL;
	p->showClassName(); // û��
	p->showPersonAge(); // !���ˣ���Ϊ������Ĭ�ϼ���this->������ǰ�棬�������ָ����NULL
}