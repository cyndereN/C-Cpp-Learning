// thisָ��ָ�򱻵��õĳ�Ա���������Ķ���

class Person {
public:
	Person(int age) {

		// ���������ͻ
		this->age = age;
	}

	Person& PersonAddPerson(Person p) {
		this->age += p.age;
		// ���ض�����
		return *this;
	}

	int age;
};

void test01() {
	Person p1(10);
	Person p2(10);

	// ��ʽ���
	p2.PersonAddPerson(p1).PersonAddPerson(p1).PersonAddPerson(p1);
}