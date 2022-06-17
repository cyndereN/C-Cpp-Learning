#include "manager.h"

Manager::Manager(int ID, string name, int dID)
{
	this->m_ID = ID;
	this->m_Name = name;
	this->m_DeptID = dID;
}

void Manager::showInfo()
{
	cout << "职工编号: " << this->m_ID
		<< "\t职工姓名: " << this->m_Name
		<< "\t岗位" << this->getDeptName()
		<< "\t岗位职责：完成老板交给的任务，并下发任务" << endl;
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
	return string("经理");
}
