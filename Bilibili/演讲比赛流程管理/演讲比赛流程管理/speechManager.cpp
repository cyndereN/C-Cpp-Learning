#include "speechManager.h"

// 构造函数
SpeechManager::SpeechManager() {
	this->init_speech();
	this->create_speaker();
	this->load_record();
}

void SpeechManager::show_menu() {
	cout << "1.开始演讲比赛" << endl;
	cout << "2.查看往届比赛" << endl;
	cout << "3.清空比赛记录" << endl;
	cout << "0.退出比赛程序" << endl;
}

void SpeechManager::exit_system() {
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

void SpeechManager::init_speech() {
	// 置空容器
	this->v1.clear();
	this->v2.clear();
	this->victory.clear();
	this->m_speaker.clear();
	this->m_record.clear();

	this->m_index = 1;
}


void SpeechManager::create_speaker() {
	string nameSeed = "ABCDEFGHIJKL";

	for (int i = 0; i < nameSeed.size(); i++) {
		string name = "选手";
		name += nameSeed[i];

		Speaker sp;
		sp.m_name = name;

		for (int j = 0; j < 2; j++) {
			sp.m_score[j] = 0;
		}

		this->v1.push_back(i + 10001);

		this->m_speaker.insert(make_pair(i + 10001, sp));
	}
}

void SpeechManager::start_speech() {
	// 第一轮
	// 抽签，比赛，显示晋级结果
	this->speech_draw();
	this->speech_contest();
	this->show_score();
	// 第二轮
	this->m_index++;
	// 抽签，比赛，显示最终结果
	this->speech_draw();
	this->speech_contest();
	this->show_score();
	// 保存分数到文件中
	this->save_record();

	//重制比赛，获取记录
	this->init_speech();
	this->create_speaker();
	this->load_record();

	cout << "本届比赛完毕" << endl;
	system("pause");
	system("cls");

}

void SpeechManager::speech_draw() {
	cout << "第" << this->m_index << "轮比赛选手正在抽签" << endl;
	if (this->m_index == 1) {
		random_shuffle(v1.begin(), v1.end());

		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;
	}
	else {
		random_shuffle(v2.begin(), v2.end());

		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;
	}

	system("pause");
	cout << endl;
}

void SpeechManager::speech_contest() {
	cout << "第" << this->m_index << "轮比赛正式开始" << endl;

	vector<int> v_src; // 比赛选手容器
	multimap<double, int, greater<double>> groupScore; // 临时容器存放小组成绩
	int num = 0; // 记录人员个数， 6个一组
	if (this->m_index == 1) {
		v_src = v1;
	}
	else {
		v_src = v2;
	}

	// 遍历所有选手进行比赛
	for (vector<int>::iterator it = v_src.begin(); it != v_src.end(); it++) {
		num++;

		// 评委打分
		deque<double> d;

		for (int i = 0; i < 10; i++) {
			double score = (rand() % 401 + 600) / 10.f; // 600-1000
			cout << score << " ";
			d.push_back(score);
		}
		cout << endl;

		sort(d.begin(), d.end(), greater<double>());
		d.pop_front(); //去除最高分
		d.pop_back();

		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double avg = sum / (double)d.size();

		// 打印平均分
		cout << "编号" << *it << "姓名" << this->m_speaker[*it].m_name << " " << avg << endl;

		// 平均分放入map容器
		this->m_speaker[*it].m_score[this->m_index - 1] = avg;

		// 打分数据放入小组临时容器,6人一组
		groupScore.insert(make_pair(avg, *it)); // key是得分，value是具体选手编号

		if (num % 6 == 0) {
			// 第六个和第十二个人的时候，打印临时容器得分排名
			cout << "第" << num / 6 << "小组比赛名次: " << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++) {
				cout << "编号" << it->second << "姓名" << this->m_speaker[it->second].m_name << " " << this->m_speaker[it->second].m_score[this->m_index - 1] << endl;
			}

			// 取走前三名
			int count = 3;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; it++, count++) {
				if (this->m_index == 1) {
					this->v2.push_back((*it).second);
				}
				else {
					this->victory.push_back((*it).second);
				}
			}

			groupScore.clear();

			cout << endl;
		}
	}


	cout << "第" << this->m_index << "轮比赛完毕" << endl;

	/*for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++) {
		cout << "选手编号：" << *it << "姓名：" << this->m_speaker[*it].m_name << "得分：" << this->m_speaker[*it].m_score[this->m_index - 1] << endl;
	}*/

	system("pause");

}

void SpeechManager::show_score() {
	cout << "第" << this->m_index << "轮晋级的选手如下————" << endl;

	vector<int> v;

	if (this->m_index == 1) {
		v = v2;
	}
	else {
		v = victory;
	}

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		cout << "选手编号：" << *it << "姓名：" << this->m_speaker[*it].m_name << "得分：" << this->m_speaker[*it].m_score[this->m_index - 1] << endl;
	}

	cout << endl;
	system("pause");
	system("cls");

	this->show_menu();

}

void SpeechManager::save_record() {
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app); // 追加方式
	for (vector<int>::iterator it = victory.begin(); it != victory.end(); it++) {
		cout << *it << "," << this->m_speaker[*it].m_score[this->m_index - 1] << ",";
	}
	ofs << endl;

	ofs.close();

	cout << "记录已经保存" << endl;
	this->fileIsEmpty = false;
}

void SpeechManager::load_record() {
	ifstream ifs("speech.csv", ios::in); // 读文件
	if (!ifs.is_open()) {
		this->fileIsEmpty = true;
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}
	// 文件清空情况
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		cout << "文件为空" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	// 文件不为空
	this->fileIsEmpty = false;
	ifs.putback(ch); // 将上面读取的单个字符放回来

	string data;

	int index = 0;

	while (ifs >> data) {
		int pos = -1; // 查到","位置的变量

		int start = 0;

		vector<string> v; // 存放6个string字符串

		while (true) {
			pos = data.find(",", start);

			if (pos == -1) {
				// 没找到的情况
				break;
			}

			string temp = data.substr(start, pos - start);
			v.push_back(temp);
			start = pos + 1;
		}

		this->m_record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();

	/*for (map<int, vector<string>>::iterator it = m_record.begin(); it != m_record.end(); it++) {
		cout << it->first << "冠军编号:" << it->second[0] << "得分：" << it->second[1] << endl;
	}*/
}


void SpeechManager::show_record() {
	if (this->fileIsEmpty) {
		cout << "文件不存在或为空" << endl;
	}
	else {
		for (int i = 0; i < this->m_record.size(); i++) {
			cout << "第" << i + 1 << "届冠军编号:" << this->m_record[i][0] << "得分：" << this->m_record[i][1] << endl;
		}
	}


	system("pause");
	system("cls");
}

void SpeechManager::clear_record() {
	cout << "确认? 1、确定； 2、返回" << endl;

	int select = 0;
	cin >> select;

	if (select == 1) {
		// 打开模式，如果存在文件删除并创建

		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		this->init_speech();
		this->create_speaker();
		this->load_record();
	}

	system("pause");
	system("cls");
}

// 析构函数
SpeechManager::~SpeechManager() {

}