// ���ã�������������ͬ����߸�����

// ����������
// �� ͬһ����������
// �� ����������ͬ
// �� �����������Ͳ�ͬ�����߸�����ͬ����˳��ͬ
// ����ֵ������Ϊ���ص�����

//int func() {
//	cout << "this is func" << endl;
//}

void func() {
	cout << "this is func" << endl;
}

void func(int a) {
	cout << "this is func (int a)" << endl;
}
func(10)

void func(double a) {
	cout << "this is func (double a)" << endl;
}
func(3.14)

void func(double a, int b) {
	cout << "this is func (double a int b)" << endl;
}
func(3.14,10)

// ע������

// 1. ������Ϊ��������
void func(int& a) {
	cout << "func(int &a)����" << endl;
}
int a = 10;
func(a);

void func(const int& a) {
	cout << "func(cosnt int &a)����" << endl;
}
func(10);

// 2.������������Ĭ�ϲ��������ֶ����ԣ�������������