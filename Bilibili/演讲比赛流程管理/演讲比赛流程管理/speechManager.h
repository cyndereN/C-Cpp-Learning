#pragma once
#include <iostream>
using namespace std;
#include <vector>
#include <map>
#include "speaker.h"
#include <algorithm>
#include <deque>
#include <functional>
#include <numeric>
#include <string>
#include <fstream>

class SpeechManager {
public:
	// 构造函数
	SpeechManager();

	void show_menu();

	void exit_system();

	// 析构函数
	~SpeechManager();

	// 初始化容器
	void init_speech();

	void create_speaker();

	void start_speech();

	void speech_draw();

	void speech_contest();

	void show_score();

	void save_record();

	void load_record();
	bool fileIsEmpty;
	map<int, vector<string>>m_record; // 存放往届数据

	void show_record();

	void clear_record();

	// 成员属性
	vector<int> v1; // 第一轮

	vector<int> v2; // 第二轮

	vector<int> victory; // 前三名容器

	map<int, Speaker> m_speaker;

	int m_index;
};