#include <iostream>
using namespace std;

int main() {
	int a, b, c, d;
	cout << "������������a, b, c��ֵ�� " << endl;
	cin >> a >> b >> c;
	d = a > b ? a : b;
	d = d > c ? d : c;
	cout << "���������������ǣ� " << d << endl;
	system("pause");
	return 0;
}