#pragma once // 防止头文件重复包含
#include <iostream>
using namespace std;

#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

#include <fstream>
#define FILENAME "empFile.txt"

// 与用户的沟通菜单界面
// 对职工增删改查的操作
// 与文件的读写交互

class WorkerManager {
public:
	WorkerManager();

	void Show_Menu();

	void Exit();

	//记录职工人数
	int m_EmpNum;
	//职工数组指针
	Worker** m_EmpArray;

	void Add_Emp();

	void save();

	// 判断文件是否为空
	bool m_FileIsEmpty;

	//统计文件中人数
	int get_EmpNum();

	void init_Emp();

	void show_Emp();

	int isExist(int id);

	void Del_Emp();

	void Mod_Emp();

	void Find_Emp();

	void Sort_Emp();

	void Clean_File();

	~WorkerManager();
};