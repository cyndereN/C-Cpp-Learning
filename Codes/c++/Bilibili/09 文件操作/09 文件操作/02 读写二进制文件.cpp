#include <fstream>
#include <string>
#include <iostream>
using namespace std;
// ������д�ļ�
class Person {
public:
	char m_Nmae[64];
	int m_Age;
};


void test01() {
	ofstream ofs;
	ofs.open("Person.txt", ios::out | ios::binary);

	// ����ֱ�� ofstream ofs("Person.txt", ios::out | ios::binary);
	
	// д�ļ�
	Person p = { "����", 18 };
	ofs.write((const char*)&p, sizeof(Person));

	ofs.close();
	


	ifstream ifs;
	ifs.open("Person.txt", ios::in | ios::binary);

	if (!ifs.is_open()) {
		cout << "��ʧ��" << endl;
		return;
	}
	// ���ļ�
	Person p;
	ifs.read((char*)&p, sizeof(Person));

	ifs.close();
}

int main() {
	test01();
	return 0;
}