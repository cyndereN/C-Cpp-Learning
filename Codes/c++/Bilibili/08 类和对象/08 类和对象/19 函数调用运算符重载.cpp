// �������������()Ҳ��������
// ���غ�ʹ�÷�ʽ�ǳ������ĵ��ã���˳�Ϊ�º���
// �º���û�й̶�д�����ǳ����

class MyPrint {
public:
	void operator()(string test){
		cout << test << endl;
	}
};

void test01() {
	MyPrint mp;
	mp("Hello World");
}

class MyAdd {
public:

	int operator()(int num1, int num2) {
		return num1 + num2;
	}
};

void test02() {
	MyAdd ma;
	int ret = ma(100, 100);
	cout << "ret = " << ret << endl;

	// ������������
	cout << MyAdd()(100, 100) << endl;
}