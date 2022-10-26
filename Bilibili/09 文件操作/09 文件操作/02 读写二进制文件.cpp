#include <fstream>
#include <string>
#include <iostream>
using namespace std;
// 二进制写文件
class Person {
public:
	char m_Nmae[64];
	int m_Age;
};


void test01() {
	ofstream ofs;
	ofs.open("Person.txt", ios::out | ios::binary);

	// 或者直接 ofstream ofs("Person.txt", ios::out | ios::binary);

	// 写文件
	Person p = { "张三", 18 };
	ofs.write((const char*)&p, sizeof(Person));

	ofs.close();



	ifstream ifs;
	ifs.open("Person.txt", ios::in | ios::binary);

	if (!ifs.is_open()) {
		cout << "打开失败" << endl;
		return;
	}
	// 读文件
	Person p;
	ifs.read((char*)&p, sizeof(Person));

	ifs.close();
}

int main() {
	test01();
	return 0;
}