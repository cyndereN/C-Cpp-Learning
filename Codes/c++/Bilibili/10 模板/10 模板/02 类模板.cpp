// ��ģ��û���Զ������Ƶ�
// ��ģ�������Ĭ�ϲ���
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

void test01(){

	// ��ģ���г�Ա��������ʱ�Ŵ���
	Person<string> p1("�����", 999);
}