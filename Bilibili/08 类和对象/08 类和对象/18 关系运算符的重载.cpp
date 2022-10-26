class Person {
public:
	Person(string name, int age) {
		m_Name = name;
		m_Age = age;
	}

	bool operator==(Person& p) {
		if (this->m_Name == p.m_Name && this->m_Age == p.m_Age) {
			return true;
		}
		return false;
	}

	string m_Name;
	int m_Age;
};

void test01() {
	Person p1("Tom", 18);
	Person p2("Tom", 18);

	if (p1 == p2) {
		cout << "p1 和 p2是相等的" << endl;
	}
}