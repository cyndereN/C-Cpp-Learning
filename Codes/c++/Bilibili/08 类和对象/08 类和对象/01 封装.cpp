#include <bits/stdc++.h>
using namespace std;
// C++����������������Ϊ����װ���̳С���̬
// C++��Ϊ�����Ϊ���󣬶������������Ժ���Ϊ

// 1.��װ
// �� �����Ժ���Ϊ��Ϊһ�����壬���������е�����
// �� �����Ժ���Ϊ����Ȩ�޿���


// ���е����Ժ���Ϊͳһ��Ϊ��Ա
// ���� ��Ա���� ��Ա����
// ��Ϊ ��Ա���� ��Ա����


// 2.��Ա��������Ϊ˽�е��ŵ�
// �� �����Լ����ƶ�дȨ��
// �� ����дȨ�ޣ����Լ�����ݵ���Ч��

// E.g. 1
// ���һ��Բ��
const double PI = 3.14;

class Circle {

// ����Ȩ��
// ����Ȩ��
public:
	// ����
	// �뾶
	int m_r;

	// ��Ϊ
	// ��ȡԲ���ܳ�
	double calc_perimeter() {
		return 2 * PI * m_r;
	}
};

int main() {
	// ʵ���� ͨ���ഴ��һ������Ĺ���
	Circle c1;
	c1.m_r = 10;

	return 0;
}

// E.g.2 ���һ����������
class Cube {
private:
	int m_L;
	int m_W;
	int m_H;
public:
	void setL(int l) {
		m_L = l;
	}
	int getL() {
		return m_L;
	}
	void setH(int h) {
		m_H = h;
	}
	int getH() {
		return m_H;
	}
	void setW(int w) {
		m_W = w;
	}
	int getL() {
		return m_W;
	}

	int calculate_volume() { 
		return m_L * m_W * m_H;
	}

	bool isSameLByClasee(Cube& c) {
		if (m_L == c.getL()) {
			return true;
		}
		return false;
	}
};

bool isSameL(Cube &c1, Cube &c2) {
	if (c1.getL() == c2.getL()) {
		return true;
	}
	return false;
}