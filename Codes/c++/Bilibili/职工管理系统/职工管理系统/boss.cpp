#include "boss.h"

Boss::Boss(int ID, string name, int dID)
{
	this->m_ID = ID;
	this->m_Name = name;
	this->m_DeptID = dID;
}

void Boss::showInfo()
{
	cout << "ְ�����: " << this->m_ID
		<< "\tְ������: " << this->m_Name
		<< "\t��λ" << this->getDeptName()
		<< "\t��λְ�𣺹���˾����" << endl;
}

int Boss::getID() {
	return this->m_ID;
}
string Boss::getName() {
	return this->m_Name;
}
int Boss::getDeptID() {
	return this->m_DeptID;
}
string Boss::getDeptName()
{
	return string("�ϰ�");
}
