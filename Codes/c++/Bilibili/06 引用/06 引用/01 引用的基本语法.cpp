#include <iostream>
using namespace std;

int main() {

	// ����: �����������
	// �﷨���������� &���� = ԭ��
	// int &b = a;
	// b = 20;
	// cout << a << endl; // Ҳ��20

	// ע�����
	// 1. �����ʼ��
	// 2. ��ʼ��֮�󲻿ɸ���

	int a = 10;
	// int &b�� //���󣬱����ʼ��
	int& b = a;

	int c = 20;

	b = c; // ��ֵ�����������Ǹ�������



	return 0;
}