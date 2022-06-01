class Base {
public:
	Base() {
		m_A = 100;
	}
	int m_A;

	void func(){}

	static int s_A;
};

int Base::s_A = 100;  //�����ʼ��

class Son :public Base {
public:
	Son() {
		m_A = 200;
	}
	int m_A;
	static int s_A;
};
int Son::s_A = 200;

void test01() {
	Son s;
	cout << "Son�� m_A = " << s.m_A << endl; // 200
	cout << "Base�� m_A = " << s.Base::m_A << endl; // 100
	s.func();
	s.Base::func();    // ������ʸ�����Ҫ��������

	cout << "Son�� s_A = " << s.s_A << endl; // 200
	cout << "Base�� s_A = " << s.Base::s_A << endl; // 200

	// ͨ����������
	cout << "Son�� s_A = " << Son::s_A << endl; // 200
	cout << "Base�� s_A = " << Son::Base::s_A << endl; // 200
}