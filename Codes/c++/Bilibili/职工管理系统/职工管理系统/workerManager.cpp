#include "workerManager.h"

WorkerManager::WorkerManager() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in); // ���ļ�

	// �ļ������ڵ����
	if (!ifs.is_open()) {
		cout << "�ļ�������" << endl;
		// ��ʼ������
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	// �ļ����ڵ���û�м�¼
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		cout << "�ļ����ڵ�������" << endl;
		// ��ʼ������
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	
	// �ļ����ڲ��Ҽ�¼����
	int num = this->get_EmpNum();
	cout << "ְ������Ϊ�� " << num << endl;
	this->m_EmpNum = num;

	this->m_EmpArray = new Worker * [this->m_EmpNum];
	this->init_Emp();

	for (int i = 0; i < this->m_EmpNum; i++) {
		cout << "ְ����ţ� " << this->m_EmpArray[i]->getID()
			<< " ְ�������� " << this->m_EmpArray[i]->getName()
			<< endl;
	}
}

// ʵ��չʾ�˵�
void WorkerManager::Show_Menu(){
	cout << "*********************************" << endl;
	cout << "********* 0.�˳�������� *********" << endl;
	cout << "********* 1.����ְ����Ϣ *********" << endl;
	cout << "********* 2.��ʾְ����Ϣ *********" << endl;
	cout << "********* 3.ɾ����ְԱ�� *********" << endl;
	cout << "********* 4.�޸�ְ����Ϣ *********" << endl;
	cout << "********* 5.����ְ����Ϣ *********" << endl;
	cout << "********* 6.���ձ������ *********" << endl;
	cout << "********* 7.��������ĵ� *********" << endl;
	cout << "*********************************" << endl;
}

void WorkerManager::Exit() {
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

void WorkerManager::Add_Emp() {
	cout << "���������ְ������: ";
	int addNum = 0;
	cin >> addNum;

	if (addNum > 0) {
		// ��ӣ���������¿ռ��С
		int newSize = this->m_EmpNum + addNum;
		// �����¿ռ�
		Worker ** newSpace = new Worker* [newSize];
		// ��ԭ���ռ��µ����ݿ������¿ռ�
		if (this->m_EmpArray != NULL) {
			for (int i = 0; i < this->m_EmpNum; i++) {
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		// �������������
		for (int i = 0; i < addNum; i++) {
			int id;
			string name;
			int dSelect; 

			cout << "������� " << i + 1 << " ����ְ�����: " << endl;
			cin >> id;
			cout << "������� " << i + 1 << " ����ְ������: " << endl;
			cin >> name;
			cout << "��ѡ��� " << i + 1 << " ����ְ����λ��1��ְ���� 2������ 3���ϰ壩: " << endl;
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

			// ��������ְ��ָ�뱣�浽������
			newSpace[this->m_EmpNum + i] = worker;
		}
		// �ͷ�ԭ�пռ�
		delete[] this->m_EmpArray;
		//�����¿ռ�ָ��
		this->m_EmpArray = newSpace;
		this->m_EmpNum = newSize;

		// ����ְ����Ϊ�ձ�־
		this->m_FileIsEmpty = false;

		// ���浽�ļ���
		this->save();
		cout << "�ɹ���ӡ�" << endl;
	} else {
		cout << "������������" << endl;
	}
	// ��������������ص��ϼ�Ŀ¼
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
		cout << "�ļ������ڼ�¼���¼Ϊ��" << endl;
	}
	else {
		for (int i = 0; i < m_EmpNum; i++) {
			// ���ö�̬���ýӿ�
			this->m_EmpArray[i]->showInfo();
		}
	}

	system("pause");
	system("cls");
}

void WorkerManager::Del_Emp() {
	// ������ɾ������������ǰ��
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else {
		cout << "��������: " << endl;
		int id = 0;
		cin >> id;

		int index = this->isExist(id);

		if (index != -1) {
			for (int i = index; i < this->m_EmpNum - 1; i++) {
				// ����ǰ��
				this->m_EmpArray[i] = this->m_EmpArray[i+1];
			}
			this->m_EmpNum--;
			this->save();

			cout << "ɾ���ɹ�" << endl;
		}
		else {
			cout << "ɾ��ʧ�ܣ�δ�ҵ���Ա��" << endl;
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
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else {
		cout << "��������: " << endl;
		int id = 0;
		cin >> id;

		int index = this->isExist(id);

		if (index != -1) {
			// ���ͷ�ԭ���Ķ�������
			delete this->m_EmpArray[index];

			int newId = 0;
			string newName = "";
			int dSelect = 0;

			cout << "��������ְ�����: " << endl;
			cin >> newId;
			cout << "��������ְ������: " << endl;
			cin >> newName;
			cout << "��ѡ����ְ����λ��1��ְ���� 2������ 3���ϰ壩: " << endl;
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
			cout << "�޸ĳɹ�" << endl;

			this->save();
		}
		else {

			cout << "����ʧ�ܣ�δ�ҵ���Ա��" << endl;
		}
	}
	system("pause");
	system("cls");
}


void WorkerManager::Find_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else {
		string name;
		cout << "��������ҵ�����: ";
		cin >> name;

		bool flag = false;

		for (int i = 0; i < m_EmpNum; i++) {
			if (this->m_EmpArray[i]->getName() == name) {
				cout << "���ҳɹ�, ���Ϊ: " << this->m_EmpArray[i]->getID() << endl;

				flag = true;
				this->m_EmpArray[i]->showInfo();
			}
		}

		if (flag == false) cout << "����ʧ�ܣ����޴���" << endl;
	}

	system("pause");
	system("cls");
}

void WorkerManager::Sort_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
		system("pause");
		system("cls");
	}
	else {
		cout << "��ѡ������ʽ����1������; 2�����򣩣�" << endl;
		int select = 0;
		cin >> select;

		// ѡ������
		for (int i = 0; i < m_EmpNum; i++) {
			int minOrMax = i;

			for (int j = i + 1; j < this->m_EmpNum; j++) {
				if (select == 1) { // ����
					if (this->m_EmpArray[minOrMax]->getID() > this->m_EmpArray[j]->getID()) minOrMax = j;
				}
				else { // ����
					if (this->m_EmpArray[minOrMax]->getID() < this->m_EmpArray[j]->getID()) minOrMax = j;
				}
			}

			// �ж�һ��ʼ�϶�����С�����ֵ�ǲ��Ǽ������Сֵ�����ֵ ������� ��������
			if (i != minOrMax) {
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
				this->m_EmpArray[minOrMax] = temp;
			}
		}

		cout << "����ɹ�" << endl;
		this->save();
		this->show_Emp();
	}
}

void WorkerManager::Clean_File() {
	cout << "ȷ����գ���1��ȷ�ϣ� 2�����أ�" << endl;
	int select = 0;
	cin >> select;

	if (select == 1) {
		// ��ģʽ ios::trunc���������ɾ���ļ������´���
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();

		if (this->m_EmpArray != NULL) {
			// ɾ��ÿ��ְ������
			for (int i = 0; i < this->m_EmpNum; i++) {
				if (this->m_EmpArray != NULL) {
					delete this->m_EmpArray[i];
				}
			}
			this->m_EmpNum = 0;
			
			// ɾ����������ָ��
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_FileIsEmpty = true;
		}

		cout << "��ճɹ�" << endl;
	}
	system("pause");
	system("cls");
}



WorkerManager::~WorkerManager() {
	// Ҳ���Բ�д���ó����Զ��ͷţ�����ֶ��ͷ�
	if (this->m_EmpArray != NULL) { // ���鲻Ϊ�գ���ÿ��Ԫ���ÿ� 
		for (int i = 0; i < this->m_EmpNum; i++) {
			if (this->m_EmpArray != NULL) {
				delete this->m_EmpArray[i];
			}
		}
	}
	delete[] this->m_EmpArray;
	this->m_EmpArray = NULL;
}