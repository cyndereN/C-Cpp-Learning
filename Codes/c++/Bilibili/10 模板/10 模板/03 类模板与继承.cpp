// ������̳еĸ�����һ����ģ��ʱ������������ʱҪָ����������T������
// ����ָ�� �������޷�����������ڴ�
// ��������ָ��������T�����ͣ�����Ҳ������ģ��

template<class T>
class Base {
	T m;
};
class Son :public Base<int> {

};
// classic Son:public Base // ����
template<class T1, class T2>
class Son2 :public Base<T2> {
	T1 obj;
};

void test02() {
	
}


// ���캯��������ʵ��

template<class T1, class T2>
class Person {
	Person(T1 name, T2 age);/*{
		m_Name = name;
		m_Age = age;
	}*/

public:
	T1 m_Name;
	T2 m_Age;
};

template<class T1, class T2>
Person<T1, T2>::Person(T1 name, T2 age) {
	this->m_Name = name;
	this->m_Age = age;
}