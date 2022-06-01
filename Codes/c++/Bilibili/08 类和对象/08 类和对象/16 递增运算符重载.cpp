#include <iostream>
using namespace std;

// ���ص�������� ������ ǰ��++�ͺ���++
class MyInteger {
	friend ostream& operator<<(ostream& cout, MyInteger myint);
public:
	MyInteger() {
		m_num = 0;
	}

	// ����ǰ��++
	MyInteger& operator++() {//��������Ϊ��һֱ��һ�����ݽ��е�������, e.g.++(++a)
		m_num++;
		return *this;
	}

	// ���غ���++
	// int ����ռλ������������������ǰ�úͺ��õ���
	MyInteger operator++(int) {
		// �ȼ�¼��ʱ���
		MyInteger temp = *this;
		// �����
		m_num++;
		// ��󽫼�¼�������
		return temp;  // һ������ֵ��ԭ��c++Ҳû�� (a++)++����
	}

private:
	int m_num;
};

// ��������
ostream& operator<<(ostream& cout, MyInteger myint) {
	cout << myint.m_num;
	return cout;
}

void test01() {
	MyInteger myint;
	cout << myint << endl;
}

int main() {

	system("pause");
	return 0;
}