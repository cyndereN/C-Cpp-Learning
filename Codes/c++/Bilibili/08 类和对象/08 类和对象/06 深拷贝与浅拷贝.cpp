#include <iostream>
using namespace std;
// ����������ڶ������ٵģ�һ��Ҫ�Լ��ṩ�������캯������ֹǳ��������������
class Person {
public:
	Person() {
		cout << "person��Ĭ�Ϲ��캯������" << endl;
	}

	Person(int age, int height) {
		m_age = age;
		m_height = new int(height);  // new�������ص���һ����ַ
		cout << "person���вι��캯������" << endl;
	}

	Person(const Person& p) {
		cout << "Person�Ŀ������캯������" << endl;
		m_age = p.m_age;
		// m_height = p.m_height; ������Ĭ��ʵ�ֵľ������д���
		// ����������ڶ�����������ռ䣬���п�������
		m_height = new int(*p.m_height);
	}

	~Person() {
		// �������룬���������ٵ������ͷ�
		if (m_height != NULL) { //!ǳ�����������Ƕ����ڴ��ظ��ͷ�  ������Լ�ʵ�ֿ������캯��
			delete m_height;
			m_height = NULL;
		}
		cout << "person��������������" << endl;
	}

	int m_age;
	int* m_height;
};

void test01() {
	Person p1(18, 160);
	cout << "p1������Ϊ " << p1.m_age << endl;
	cout << "p1�����Ϊ " << *p1.m_height << endl;
	Person p2(p1);
	cout << "p2������Ϊ " << p2.m_age << endl;
	cout << "p2�����Ϊ " << *p2.m_height << endl;
}

int main() {
	test01();
	return 0;
}