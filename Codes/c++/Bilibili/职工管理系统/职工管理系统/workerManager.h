#pragma once // ��ֹͷ�ļ��ظ�����
#include <iostream>
using namespace std;

#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

#include <fstream>
#define FILENAME "empFile.txt"

// ���û��Ĺ�ͨ�˵�����
// ��ְ����ɾ�Ĳ�Ĳ���
// ���ļ��Ķ�д����

class WorkerManager {
public:
	WorkerManager();
	
	void Show_Menu();

	void Exit();
	
	//��¼ְ������
	int m_EmpNum;
	//ְ������ָ��
	Worker** m_EmpArray;

	void Add_Emp();

	void save();

	// �ж��ļ��Ƿ�Ϊ��
	bool m_FileIsEmpty;

	//ͳ���ļ�������
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