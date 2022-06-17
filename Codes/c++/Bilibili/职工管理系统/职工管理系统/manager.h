#pragma once
#include <iostream>
using namespace std;
#include "worker.h"

class Manager : public Worker {
public:
	Manager(int ID, string name, int dID);
	virtual int getID();
	virtual string getName();
	virtual int getDeptID();
	virtual void showInfo();
	virtual string getDeptName();
};