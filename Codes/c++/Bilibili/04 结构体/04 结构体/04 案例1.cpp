#include <iostream>
using namespace std;
#include <string>

struct Student {
	string sName;
	int score;
};

struct Teacher {
	string tName;
	struct Student sArray[5];
};

void allocateSpace(struct Teacher tArray[], int len) {
	string nameSeed = "ABCDE";


	for (int i = 0; i < len; i++) {
		tArray[i].tName = "Teacher_";
		tArray[i].tName += nameSeed[i];

		for (int j = 0; j < 5; j++) {
			tArray[i].sArray[j].sName = "Student_";
			tArray[i].sArray[j].sName += nameSeed[j];
			int randScore = rand() % 61 + 40; // 40~100
 			tArray[i].sArray[j].score = randScore;
		}
	}
}

void printInfo(Teacher* tArray, int len) {
	for (int i = 0; i < len; i++) {
		cout << (tArray+i)->tName << endl;
		// cout << *(tArray+i).tName << endl;
		// cout << tArray[i].tName << endl;
	}
}


int main() {
	// 随机数种子
	srand((unsigned int)time(NULL));
	//创建三名老师的数组
	struct Teacher tArray[3];

	// 通过函数给3名老师的信息赋值，并给老师带的学生信息赋值
	int len = sizeof(tArray)/sizeof(tArray[0]) ;
	allocateSpace(tArray, len);

	// 打印所有老师及所带的学生信息
	printInfo(tArray, len);

	system("pause");
	return 0;
}