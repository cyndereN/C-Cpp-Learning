#include<bits/stdc++.h>
using namespace std;

// �����������ķ���ֵ
// 1. ��Ҫ���ؾֲ�����������

int& test01() { // ������
	int a = 10; // �ֲ����������ջ��
	return a;
}

int& test02() { 
	static int a = 10;  // ��̬�����������ȫ����
	return a;
}


int main() {

	int& ref = test02();

	test02() = 1000;  // 2. ��������ķ���ֵ�����ã�����������ÿ�����Ϊ��ֵ
	return 0;
}