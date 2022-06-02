#pragma once
#include <iostream>
using namespace std;
#include <string>

class Worker {
protected:
	int m_ID;
	string m_Name;
	int m_DeptID;
public:
	virtual void showInfo() = 0;
	virtual int getID() = 0;
	virtual string getName() = 0;
	virtual int getDeptID() = 0;
	virtual string getDeptName() = 0;
};