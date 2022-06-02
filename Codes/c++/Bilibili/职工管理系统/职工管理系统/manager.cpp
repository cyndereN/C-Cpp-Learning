#include "manager.h"

Manager::Manager(int ID, string name, int dID)
{
	this->m_ID = ID;
	this->m_Name = name;
	this->m_DeptID = dID;
}

void Manager::showInfo()
{
	cout << "ְ�����: " << this->m_ID
		<< "\tְ������: " << this->m_Name
		<< "\t��λ" << this->getDeptName()
		<< "\t��λְ������ϰ彻�������񣬲��·�����" << endl;
}

int Manager::getID() {
	return this->m_ID;
}
string Manager::getName() {
	return this->m_Name;
}
int Manager::getDeptID() {
	return this->m_DeptID;
}

string Manager::getDeptName()
{
	return string("����");
}
