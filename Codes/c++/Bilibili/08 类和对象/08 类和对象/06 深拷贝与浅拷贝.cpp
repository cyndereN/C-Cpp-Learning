#include <iostream>
using namespace std;
// 如果有属性在堆区开辟的，一定要自己提供拷贝构造函数，防止浅拷贝带来的问题 
class Person {
public:
	Person() {
		cout << "person的默认构造函数调用" << endl;
	}

	Person(int age, int height) {
		m_age = age;
		m_height = new int(height);  // new创建返回的是一个地址
		cout << "person的有参构造函数调用" << endl;
	}

	Person(const Person& p) {
		cout << "Person的拷贝构造函数调用" << endl;
		m_age = p.m_age;
		// m_height = p.m_height; 编译器默认实现的就是这行代码
		// 深拷贝操作：在堆区重新申请空间，进行拷贝操作
		m_height = new int(*p.m_height);
	}

	~Person() {
		// 析构代码，将堆区开辟的数据释放
		if (m_height != NULL) { //!浅拷贝的问题是堆区内存重复释放  解决？自己实现拷贝构造函数
			delete m_height;
			m_height = NULL;
		}
		cout << "person的析构函数调用" << endl;
	}

	int m_age;
	int* m_height;
};

void test01() {
	Person p1(18, 160);
	cout << "p1的年龄为 " << p1.m_age << endl;
	cout << "p1的身高为 " << *p1.m_height << endl;
	Person p2(p1);
	cout << "p2的年龄为 " << p2.m_age << endl;
	cout << "p2的身高为 " << *p2.m_height << endl;
}

int main() {
	test01();
	return 0;
}