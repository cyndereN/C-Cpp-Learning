#include "employee.h"

Employee::Employee(int ID, string name, int dID)
{
	this->m_ID = ID;
	this->m_Name = name;
	this->m_DeptID = dID;
}

void Employee::showInfo()
{
	cout << "职工编号: " << this->m_ID
		<< "\t职工姓名: " << this->m_Name
		<< "\t岗位" << this->getDeptName()
		<< "\t岗位职责：完成经理交给的任务" << endl;
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
	return string("员工");
}
