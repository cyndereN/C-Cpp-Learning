#include <iostream>
using namespace std;
#include "speechManager.h"
#include <ctime>

int main()
{
	srand((unsigned int)time(NULL));

	SpeechManager sm;

	int choice = 0;

	while (true) {
		sm.show_menu();

		cout << "请输入: " << endl;
		cin >> choice;

		switch (choice) {
		case 1: // 开始比赛
			sm.start_speech();
			break;

		case 2: // 查看记录
			sm.show_record();
			break;

		case 3: // 清空记录
			sm.clear_record();
			break;

		case 0: // 退出系统
			sm.exit_system();
			break;

		default:
			system("cls");
			break;
		}
	}

	system("pause");
	return 0;
}
