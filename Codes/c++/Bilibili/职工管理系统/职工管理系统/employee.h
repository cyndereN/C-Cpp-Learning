#pragma once
#include <iostream>
using namespace std;
#include "worker.h"

class Employee : public Worker {

public:
	Employee(int ID, string name, int dID);
	virtual int getID();
	virtual string getName();
	virtual int getDeptID();
	virtual void showInfo();
	virtual string getDeptName();
};