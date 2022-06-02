#include "employee.h"

Employee::Employee(int ID, string name, int dID)
{
	this->m_ID = ID;
	this->m_Name = name;
	this->m_DeptID = dID;
}

void Employee::showInfo()
{
	cout << "ְ�����: " << this->m_ID
		<< "\tְ������: " << this->m_Name
		<< "\t��λ" << this->getDeptName()
		<< "\t��λְ����ɾ�����������" << endl;
}

int Employee::getID() {
	return this->m_ID;
}
string Employee::getName() {
	return this->m_Name;
}
int Employee::getDeptID() {
	return this->m_DeptID;
}

string Employee::getDeptName()
{
	return string("Ա��");
}
