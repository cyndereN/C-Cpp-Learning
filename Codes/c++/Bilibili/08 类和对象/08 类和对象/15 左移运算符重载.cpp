// ��������Զ�����������
class Person {
	friend ostream& operator<<(ostream& out, Person& p);

	// ���ó�Ա�����������������
	// p.operator<<(cout) �򻯰汾 p<<cout
	// һ�㲻�����ó�Ա�������أ���Ϊ�޷�ʵ��cout����ࣩ
private:
	int m_A;
	int m_B;

public:
	Person(int a, int b) {
		m_A = a;  m_B = b;
	}

};

// ֻ������ȫ�ֺ����������������
ostream& operator<<(ostream& out, Person& p) {
	// out��cout�ı���
	out << "m_A = " << p.m_A << " m_B = " << p.m_B;
	return out;
}