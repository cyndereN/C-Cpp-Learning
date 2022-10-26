#include <iostream>
using namespace std;
#include <string>
#define MAX 1000

// 联系人结构体
struct Person {
	string m_name;
	int m_sex;
	int m_age;
	string m_phone;
	string m_addr;
};

struct Addressbooks {
	// 通讯录中保存的联系人数组
	struct Person personArray[MAX];

	// 通讯录中当前记录联系人个数
	int m_size;
};


void addPerson(Addressbooks* abs) {
	// 判断通讯录是否已满
	if (abs->m_size == MAX) {
		cout << "通讯录已满, 无法添加" << endl;
		return;
	}
	else {
		string name;
		cout << "请输入姓名: " << endl;
		cin >> name;
		abs->personArray[abs->m_size].m_name = name;

		cout << "请输入性别: " << endl;
		cout << "1 -- 男" << endl;
		cout << "2 -- 女" << endl;

		int sex = 0;

		while (true) {
			cin >> sex;
			if (sex == 1 || sex == 2) {
				abs->personArray[abs->m_size].m_sex = sex;
				break;
			}
			cout << "请重新输入: ";
		}


		int age = 0;
		cout << "请输入年龄: " << endl;
		cin >> age;
		abs->personArray[abs->m_size].m_age = age;

		string phone;
		cout << "请输入电话: " << endl;
		cin >> phone;
		abs->personArray[abs->m_size].m_phone = phone;

		string addr;
		cout << "请输入地址: " << endl;
		cin >> addr;
		abs->personArray[abs->m_size].m_addr = addr;

		abs->m_size++;

		system("pause");
		system("cls");
	}
}

void showPerson(Addressbooks* abs) {
	if (abs->m_size == 0) {
		cout << "当前记录为空" << endl;
	}
	else {
		for (int i = 0; i < abs->m_size; i++) {
			cout << "姓名: " << abs->personArray[i].m_name;
			cout << "性别: " << (abs->personArray[i].m_sex == 1 ? "男" : "女") << endl;
		}
	}

	system("pause");
	system("cls");
}

// 检测联系人是否存在，若存在返回具体位置，不存在返回-1
int isExist(Addressbooks* abs, string name) {
	for (int i = 0; i < abs->m_size; i++) {
		if (abs->personArray[i].m_name == name) { // 找到了
			return i;
		}
	}
	return -1;
}

void deletePerson(Addressbooks* abs) {
	cout << "请输入联系人姓名: " << endl;
	string name;
	cin >> name;
	int ret = isExist(abs, name);
	if (ret == -1) {
		cout << "查无此人" << endl;
	}
	else
	{

		//数据前移
		for (int i = ret; i < abs->m_size; i++) {
			abs->personArray[i] = abs->personArray[i + 1];
		}
		abs->m_size--;

		cout << "已删除" << endl;
	}

	system("pause");
	system("cls");
}

void findPerson(Addressbooks* abs) {
	cout << "请输入联系人姓名: " << endl;
	string name;
	cin >> name;

	int ret = isExist(abs, name);

	if (ret != -1)
	{
		cout << "姓名: " << abs->personArray[ret].m_name << " ";
		cout << "性别: " << (abs->personArray[ret].m_sex == 1 ? "男" : "女") << endl;
	}
	else
	{
		cout << "查无此人" << endl;
	}

	system("pause");
	system("cls");
}

void modifyPerson(Addressbooks* abs) {
	cout << "请输入您要修改的联系人" << endl;
	string name;
	cin >> name;

	int ret = isExist(abs, name);

	if (ret != -1)
	{
		// 找到了
		string name;
		cout << "请输入姓名: " << endl;
		cin >> name;
		abs->personArray[ret].m_name = name;

		// 下略
	}
	else
	{
		cout << "查无此人" << endl;
	}


}

void cleanPerson(Addressbooks* abs) {
	abs->m_size = 0;  // 当前记录联系人重制为0，做逻辑清空
	cout << "已清空" << endl;
}

// 显示菜单
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
	// 创建通讯录结构体变量
	Addressbooks abs;
	abs.m_size = 0;

	int select = 0;

	while (true) {
		showMenu();
		cin >> select;

		switch (select) {
		case 1:  // 添加
			addPerson(&abs);  // 利用地址传递可修改
			break;
		case 2: // 显示
			showPerson(&abs);
			break;
		case 3:  // 删除
			deletePerson(&abs);
			break;
		case 4:  // 查找
			findPerson(&abs);
			break;
		case 5:  // 修改
			modifyPerson(&abs);
			break;
		case 6:  // 清空
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