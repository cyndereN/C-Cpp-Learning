#include <iostream>
using namespace std;
#include <string>
#define MAX 1000

// ��ϵ�˽ṹ��
struct Person {
	string m_name;
	int m_sex;
	int m_age;
	string m_phone;
	string m_addr;
};

struct Addressbooks {
	// ͨѶ¼�б������ϵ������
	struct Person personArray[MAX];

	// ͨѶ¼�е�ǰ��¼��ϵ�˸���
	int m_size;
};


void addPerson(Addressbooks* abs) {
	// �ж�ͨѶ¼�Ƿ�����
	if (abs->m_size == MAX) {
		cout << "ͨѶ¼����, �޷����" << endl;
		return;
	}
	else {
		string name;
		cout << "����������: " << endl;
		cin >> name;
		abs->personArray[abs->m_size].m_name = name;

		cout << "�������Ա�: " << endl;
		cout << "1 -- ��" << endl;
		cout << "2 -- Ů" << endl;

		int sex = 0;
		
		while (true) {
			cin >> sex;
			if(sex == 1 || sex == 2) {
				abs->personArray[abs->m_size].m_sex = sex;
				break;
			}
			cout << "����������: ";
		}


		int age = 0;
		cout << "����������: " << endl;
		cin >> age;
		abs->personArray[abs->m_size].m_age = age;

		string phone;
		cout << "������绰: " << endl;
		cin >> phone;
		abs->personArray[abs->m_size].m_phone = phone;

		string addr;
		cout << "�������ַ: " << endl;
		cin >> addr;
		abs->personArray[abs->m_size].m_addr = addr;

		abs->m_size++;

		system("pause");
		system("cls"); 
	}
}

void showPerson(Addressbooks *abs) {
	if (abs->m_size == 0) {
		cout << "��ǰ��¼Ϊ��" << endl;
	}
	else {
		for (int i = 0; i < abs->m_size; i++) {
			cout << "����: " << abs->personArray[i].m_name;
			cout << "�Ա�: " << (abs->personArray[i].m_sex ==1 ? "��":"Ů") << endl;
		}
	}

	system("pause");
	system("cls");
}

// �����ϵ���Ƿ���ڣ������ڷ��ؾ���λ�ã������ڷ���-1
int isExist(Addressbooks* abs, string name) {
	for (int i = 0; i < abs->m_size; i++) {
		if (abs->personArray[i].m_name == name) { // �ҵ���
			return i;
		}
	}
	return -1;
}

void deletePerson(Addressbooks* abs) {
	cout << "��������ϵ������: " << endl;
	string name;
	cin >> name;
	int ret = isExist(abs, name);
	if (ret == -1) {
		cout << "���޴���" << endl;
	}
	else 
	{

		//����ǰ��
		for (int i = ret; i < abs->m_size; i++) {
			abs->personArray[i] = abs->personArray[i + 1];
		}
		abs->m_size--;

		cout << "��ɾ��" << endl;
	}

	system("pause");
	system("cls");
}

void findPerson(Addressbooks* abs) {
	cout << "��������ϵ������: " << endl;
	string name;
	cin >> name;

	int ret = isExist(abs, name);
	
	if (ret != -1)
	{
		cout << "����: " << abs->personArray[ret].m_name << " ";
		cout << "�Ա�: " << (abs->personArray[ret].m_sex == 1 ? "��" : "Ů") << endl;
	}
	else
	{
		cout << "���޴���" << endl;
	}

	system("pause");
	system("cls");
}

void modifyPerson(Addressbooks* abs) {
	cout << "��������Ҫ�޸ĵ���ϵ��" << endl;
	string name;
	cin >> name;

	int ret = isExist(abs, name);

	if (ret != -1) 
	{
		// �ҵ���
		string name;
		cout << "����������: " << endl;
		cin >> name;
		abs->personArray[ret].m_name = name;

		// ����
	}
	else
	{
		cout << "���޴���" << endl;
	}


} 

void cleanPerson(Addressbooks* abs){
	abs->m_size = 0;  // ��ǰ��¼��ϵ������Ϊ0�����߼����
	cout << "�����" << endl;
}

// ��ʾ�˵�
void showMenu() {
	cout << "1. Add" << endl;
	cout << "2. Show" << endl;
	cout << "3. Delete" << endl;
	cout << "4. Find" << endl;
	cout << "5. Edit" << endl;
	cout << "6. Clear" << endl;
	cout << "0. Exit" << endl;
}


int main() {
	// ����ͨѶ¼�ṹ�����
	Addressbooks abs;
	abs.m_size = 0;

	int select = 0;

	while (true) {
		showMenu();
		cin >> select;

		switch (select) {
		case 1:  // ���
			addPerson(&abs);  // ���õ�ַ���ݿ��޸�
			break;
		case 2: // ��ʾ
			showPerson(&abs);
			break;
		case 3:  // ɾ��
			deletePerson(&abs);
			break;
		case 4:  // ����
			findPerson(&abs);
			break;
		case 5:  // �޸�
			modifyPerson(&abs);
			break;
		case 6:  // ���
			cleanPerson(&abs);
			break;
		case 0:
			system("pause");
			return 0;
			break;
		default:
			break;
		}
	}
	
	system("pause");
	return 0;
}