#include <iostream>
using namespace std;

int main3() {
	int a, b, c, d;
	cout << "请输入三个数a, b, c的值： " << endl;
	cin >> a >> b >> c;
	d = a > b ? a : b;
	d = d > c ? d : c;
	cout << "三个数中最大的数是： " << d << endl;
	system("pause");
	return 0;
}