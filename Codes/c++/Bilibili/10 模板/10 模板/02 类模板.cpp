// 类模板没有自动类型推导
// 类模板可以有默认参数
template<class NameType, class AgeType = int>
class Person {
	Person(NameType name, AgeType age) {
		m_Name = name;
		m_Age = age;
	}

public:
	NameType m_Name;
	AgeType m_Age;
};

void test01() {

	// 类模板中成员函数调用时才创建
	Person<string> p1("孙悟空", 999);
}