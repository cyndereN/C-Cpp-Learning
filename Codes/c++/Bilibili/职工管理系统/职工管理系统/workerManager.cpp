#include "workerManager.h"

WorkerManager::WorkerManager() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in); // 读文件

	// 文件不存在的情况
	if (!ifs.is_open()) {
		cout << "文件不存在" << endl;
		// 初始化属性
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	// 文件存在但是没有记录
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		cout << "文件存在但无数据" << endl;
		// 初始化属性
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	// 文件存在并且记录数据
	int num = this->get_EmpNum();
	cout << "职工人数为： " << num << endl;
	this->m_EmpNum = num;

	this->m_EmpArray = new Worker * [this->m_EmpNum];
	this->init_Emp();

	for (int i = 0; i < this->m_EmpNum; i++) {
		cout << "职工编号： " << this->m_EmpArray[i]->getID()
			<< " 职工姓名： " << this->m_EmpArray[i]->getName()
			<< endl;
	}
}

// 实现展示菜单
void WorkerManager::Show_Menu() {
	cout << "*********************************" << endl;
	cout << "********* 0.退出管理程序 *********" << endl;
	cout << "********* 1.增加职工信息 *********" << endl;
	cout << "********* 2.显示职工信息 *********" << endl;
	cout << "********* 3.删除离职员工 *********" << endl;
	cout << "********* 4.修改职工信息 *********" << endl;
	cout << "********* 5.查找职工信息 *********" << endl;
	cout << "********* 6.按照编号排序 *********" << endl;
	cout << "********* 7.清空所有文档 *********" << endl;
	cout << "*********************************" << endl;
}

void WorkerManager::Exit() {
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

void WorkerManager::Add_Emp() {
	cout << "请输入添加职工数量: ";
	int addNum = 0;
	cin >> addNum;

	if (addNum > 0) {
		// 添加，计算添加新空间大小
		int newSize = this->m_EmpNum + addNum;
		// 开辟新空间
		Worker** newSpace = new Worker * [newSize];
		// 将原来空间下的数据拷贝到新空间
		if (this->m_EmpArray != NULL) {
			for (int i = 0; i < this->m_EmpNum; i++) {
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		// 批量添加新数据
		for (int i = 0; i < addNum; i++) {
			int id;
			string name;
			int dSelect;

			cout << "请输入第 " << i + 1 << " 个新职工编号: " << endl;
			cin >> id;
			cout << "请输入第 " << i + 1 << " 个新职工姓名: " << endl;
			cin >> name;
			cout << "请选择第 " << i + 1 << " 个新职工岗位（1、职工； 2、经理； 3、老板）: " << endl;
			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect) {
			case 1:
				worker = new Employee(id, name, dSelect);
				break;
			case 2:
				worker = new Manager(id, name, dSelect);
				break;
			case 3:
				worker = new Boss(id, name, dSelect);
				break;
			default:
				break;
			}

			// 将创建的职工指针保存到数组中
			newSpace[this->m_EmpNum + i] = worker;
		}
		// 释放原有空间
		delete[] this->m_EmpArray;
		//更改新空间指向
		this->m_EmpArray = newSpace;
		this->m_EmpNum = newSize;

		// 更新职工不为空标志
		this->m_FileIsEmpty = false;

		// 保存到文件中
		this->save();
		cout << "成功添加。" << endl;
	}
	else {
		cout << "输入数据有误" << endl;
	}
	// 按任意键后清屏回到上级目录
	system("pause");
	system("cls");
}

void WorkerManager::save() {
	ofstream ofs;
	ofs.open(FILENAME, ios::out);

	for (int i = 0; i < this->m_EmpNum; i++) {
		ofs << this->m_EmpArray[i]->getID() << " "
			<< this->m_EmpArray[i]->getName() << " "
			<< this->m_EmpArray[i]->getDeptID() << endl;
	}
}

int WorkerManager::get_EmpNum() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int num = 0;

	while (ifs >> id && ifs >> name && ifs >> dId) {
		num++;
	}

	return num;
}

void WorkerManager::init_Emp() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int index = 0;

	while (ifs >> id && ifs >> name && ifs >> dId) {
		Worker* worker = NULL;

		if (dId == 1) {
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2) {
			worker = new Manager(id, name, dId);
		}
		else {
			worker = new Boss(id, name, dId);
		}


		this->m_EmpArray[index++] = worker;
	}

	ifs.close();

}


void WorkerManager::show_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在记录或记录为空" << endl;
	}
	else {
		for (int i = 0; i < m_EmpNum; i++) {
			// 利用多态调用接口
			this->m_EmpArray[i]->showInfo();
		}
	}

	system("pause");
	system("cls");
}

void WorkerManager::Del_Emp() {
	// 数组中删除本质是数据前移
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或记录为空" << endl;
	}
	else {
		cout << "请输入编号: " << endl;
		int id = 0;
		cin >> id;

		int index = this->isExist(id);

		if (index != -1) {
			for (int i = index; i < this->m_EmpNum - 1; i++) {
				// 数据前移
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;
			this->save();

			cout << "删除成功" << endl;
		}
		else {
			cout << "删除失败，未找到该员工" << endl;
		}
	}
	system("pause");
	system("cls");

}

int WorkerManager::isExist(int id) {
	int index = -1;

	for (int i = 0; i < this->m_EmpNum; i++) {
		if (this->m_EmpArray[i]->getID() == id) {
			index = i;

			break;
		}
	}

	return index;
}

void WorkerManager::Mod_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或记录为空" << endl;
	}
	else {
		cout << "请输入编号: " << endl;
		int id = 0;
		cin >> id;

		int index = this->isExist(id);

		if (index != -1) {
			// 先释放原来的堆区数据
			delete this->m_EmpArray[index];

			int newId = 0;
			string newName = "";
			int dSelect = 0;

			cout << "请输入新职工编号: " << endl;
			cin >> newId;
			cout << "请输入新职工姓名: " << endl;
			cin >> newName;
			cout << "请选择新职工岗位（1、职工； 2、经理； 3、老板）: " << endl;
			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect) {
			case 1:
				worker = new Employee(newId, newName, dSelect);
				break;
			case 2:
				worker = new Manager(newId, newName, dSelect);
				break;
			case 3:
				worker = new Boss(newId, newName, dSelect);
				break;
			default:
				break;
			}

			this->m_EmpArray[index] = worker;
			cout << "修改成功" << endl;

			this->save();
		}
		else {

			cout << "查找失败，未找到该员工" << endl;
		}
	}
	system("pause");
	system("cls");
}


void WorkerManager::Find_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或记录为空" << endl;
	}
	else {
		string name;
		cout << "请输入查找的姓名: ";
		cin >> name;

		bool flag = false;

		for (int i = 0; i < m_EmpNum; i++) {
			if (this->m_EmpArray[i]->getName() == name) {
				cout << "查找成功, 编号为: " << this->m_EmpArray[i]->getID() << endl;

				flag = true;
				this->m_EmpArray[i]->showInfo();
			}
		}

		if (flag == false) cout << "查找失败，查无此人" << endl;
	}

	system("pause");
	system("cls");
}

void WorkerManager::Sort_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或记录为空" << endl;
		system("pause");
		system("cls");
	}
	else {
		cout << "请选择排序方式：（1、升序; 2、降序）：" << endl;
		int select = 0;
		cin >> select;

		// 选择排序
		for (int i = 0; i < m_EmpNum; i++) {
			int minOrMax = i;

			for (int j = i + 1; j < this->m_EmpNum; j++) {
				if (select == 1) { // 升序
					if (this->m_EmpArray[minOrMax]->getID() > this->m_EmpArray[j]->getID()) minOrMax = j;
				}
				else { // 降序
					if (this->m_EmpArray[minOrMax]->getID() < this->m_EmpArray[j]->getID()) minOrMax = j;
				}
			}

			// 判断一开始认定的最小或最大值是不是计算的最小值或最大值 如果不是 交换数据
			if (i != minOrMax) {
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
				this->m_EmpArray[minOrMax] = temp;
			}
		}

		cout << "排序成功" << endl;
		this->save();
		this->show_Emp();
	}
}

void WorkerManager::Clean_File() {
	cout << "确认清空？（1、确认； 2、返回）" << endl;
	int select = 0;
	cin >> select;

	if (select == 1) {
		// 打开模式 ios::trunc，如果存在删除文件并重新创建
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();

		if (this->m_EmpArray != NULL) {
			// 删除每个职工对象
			for (int i = 0; i < this->m_EmpNum; i++) {
				if (this->m_EmpArray != NULL) {
					delete this->m_EmpArray[i];
				}
			}
			this->m_EmpNum = 0;

			// 删除堆区数组指针
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_FileIsEmpty = true;
		}

		cout << "清空成功" << endl;
	}
	system("pause");
	system("cls");
}



WorkerManager::~WorkerManager() {
	// 也可以不写，让程序自动释放，最好手动释放
	if (this->m_EmpArray != NULL) { // 数组不为空，把每个元素置空 
		for (int i = 0; i < this->m_EmpNum; i++) {
			if (this->m_EmpArray != NULL) {
				delete this->m_EmpArray[i];
			}
		}
	}
	delete[] this->m_EmpArray;
	this->m_EmpArray = NULL;
}