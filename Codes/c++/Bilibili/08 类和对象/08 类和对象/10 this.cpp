// this指针指向被调用的成员函数所含的对象 

class Person {
public:
	Person(int age) {

		// 解决命名冲突
		this->age = age;
	}

	Person& PersonAddPerson(Person p) {
		this->age += p.age;
		// 返回对象本身
		return *this;
	}

	int age;
};

void test01() {
	Person p1(10);
	Person p2(10);

	// 链式编程
	p2.PersonAddPerson(p1).PersonAddPerson(p1).PersonAddPerson(p1);
}