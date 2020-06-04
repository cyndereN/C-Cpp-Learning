#include<iostream>
#include<iomanip>
#include<string>
#include<iomanip>
#include<vector>
#include<set>
using namespace std;
//输入的顺序是dragon 、ninja、iceman、lion、wolf
//红方司令部按照iceman、lion、wolf、ninja、dragon的顺序循环制造武士
//蓝方司令部按照lion、dragon、ninja、iceman、wolf的顺序循环制造武士

enum Cwpn { Csword, Cbomb, Carrow };//表示武器种类
enum Cwor { Cdragon, Cninja, Ciceman, Clion, Cwolf };//表示武士种类
enum Ccolor { Cred, Cblue };//表示武士或司令部的颜色
enum Cflag { Credflag, Cblueflag, Cnoflag };//表示城市中的旗帜
string string_wpn[3] = { "sword","bomb","arrow" };//武器的名字
string string_wor[5] = { "dragon", "ninja", "iceman", "lion", "wolf" };//武士的名字
string string_color[2] = { "red","blue" };//武士或司令部 颜色的名字
int use_of_HP[5] = { 0 };//武士的生命值//待输入
int attack[5] = { 0 };//武士的攻击力//待输入

class city;
class headquarter;
class warrior;
class dragon;
class ninja;
class iceman;
class lion;
class wolf;
class weapon;
class sword;
class bomb;
class arrow;

int nowtime = 0;//从0开始的分钟数
int minute = 0;
int hour = 0;

int gr = 0;
int M = 0, N = 0, R = 0, K = 0, T = 0;//M-初始生命元 N-中间城市数 R-arrow攻击力 K-lion每走一步忠诚度降低K T-要输出0~T分钟所有事件
bool endflag = false;//游戏结束标志
//======================================================================================================
//标记该做第几个武士 的数 +1
int plus_one(int a){
	if (a <= 3)  return a + 1;
	else  return 0;
}
//======================================================================================================
class city{
public:
	int num;//编号
	Cflag flag = Cnoflag;
	int HP;
	int HP_win_get = 0;
	warrior * warrior_in_city[2] = { NULL,NULL };//城市中的武士
	warrior * warrior_in_city_temp[2] = { NULL,NULL };
	int warrior_in_city_num = 0;//城市中武士的数目（射箭之前）,只能为0,1,2
	int fight_die_mark = 0;//记录战死的情况（真的发生了一对一的战斗）0-没人死，1-红的死，2-蓝的死，3-红蓝都死
	int arrow_die_mark = 0;//记录被箭射死的情况：0-没人死，1-红的死，2-蓝的死，3-红蓝都死
	int change_flag = 0;//记录胜负数量用于决定什么时候换旗
	int lion_HP_mark[2] = { 0,0 };
	void produce_HP();
};
city mycity[21];
//------------------------------------------
//武士
class warrior{
public:
	Ccolor color;//颜色
	Cwor kind;//种族
	int ID;//编号
	int HP;//生命值
	int ATT;//攻击力
	headquarter * home;//指向他出生的司令部
	int place;//在哪个位置
	weapon * weapon_ptr[3] = { NULL,NULL,NULL };//指向武士拥有的武器，sword bomb arrow对号入座
	double morale;//士气值，对dragon以外没用
	int loyalty;//忠诚度,对lion以外没用
	int go_on_step = 0;//走的步数，对iceman以外没用
	
	warrior(int hHP, int total, Ccolor headcolor);
	void march();
	virtual void rob_unsure() {}
	virtual ~warrior();
	void fight(warrior* ptr);
	void fightback(warrior* ptr);
};
class dragon :public warrior{
public:
	dragon(int hHP, int total, Ccolor headcolor); //此时司令部中怪物总数还没有++
};
class ninja :public warrior{
public:
	ninja(int hHP, int total, Ccolor headcolor);//此时司令部中怪物总数还没有++
};
class iceman:public warrior{
public:
	iceman(int hHP, int total, Ccolor headcolor);//此时司令部中怪物总数还没有++
};
class lion :public warrior{
public:
	lion(int hHP, int total, Ccolor headcolor);//此时司令部中怪物总数还没有++
};
class wolf :public warrior{
public:
	wolf(int hHP, int total, Ccolor headcolor);//此时司令部中怪物总数还没有++
};
//------------------------------------------
class weapon {
public:
	int beiyong = 0;
	warrior* owner = NULL;
	virtual int & get_ATT() = 0;
	virtual int & get_left_time() = 0;
	virtual void left_time_minus_one() {};
	virtual void blunt();
	weapon(warrior* ptr);
};
class sword :public weapon {
public:
	int ATT;
	sword(warrior* ptr);
	virtual int & get_ATT();
	virtual void blunt();
	virtual int & get_left_time();
};
class bomb :public weapon {
public:
	bomb(warrior* ptr);
	virtual int & get_ATT();
	virtual int & get_left_time();
};
class arrow :public weapon {
public:
	int ATT = R;
	int left_time = 3;
	arrow(warrior* ptr);
	virtual int & get_left_time();
	virtual void left_time_minus_one();
	virtual int & get_ATT();
};
//------------------------------------------
class headquarter :public city{
public:
	Ccolor color;//颜色
	int HP = 0;//生命元

	vector<warrior*> warrior_ptr;//司令部生产的的武士列表(未完全删除！！！！)
	int total_num = 0;//该司令部所拥有的武士总数(不管死活)
	int exist_num = 0;//该司令部所拥有的活着的武士总数
	int num_of_warrior[5] = { 0 };//每种武士的数目，按题中统一的顺序
	warrior* warrior_in_headquarter[2] = { NULL,NULL };//目前站在司令部的武士
	warrior* warrior_in_headquarter_temp[2] = { NULL,NULL };
	warrior* warrior_do_nothing[2] = { NULL,NULL };//到达司令部无所事事的武士列表
	int warrior_do_nothing_counter = 0;
	int occupy_num = 0;//此司令部已经有多少敌军

	int order[5] = { 0 };//生产顺序
	int to_make = 0;//该制造(按他自己的标准排的)第几种武士了
	//bool stop_or_not = false;//是否不再生产武士

	headquarter() {}; //构造函数
	bool able_to_make_temp();//是否还能继续制造眼下即将要制造的武士，能-true 不能-false
	void make_warrior();//制造一个武士
	void print_HP();//报告生命元数量
};
headquarter red, blue;
//======================================================================================================
//city成员函数
void city::produce_HP() {
	this->HP += 10;
	return;
}
//---------------------------------------------------------------------
//warrior类成员函数
warrior::warrior(int hHP, int total, Ccolor headcolor) {
	color = headcolor;
	if (color == Cred) {
		home = &red;
		place = 0;
	}
	else {
		home = &blue;
		place = N + 1;
	}
	ID = total + 1;
}
//武士前进一步
void warrior::march() {
	if (color == Cred) {
		if (place == 0) {//武士还在司令部
			place++;
			mycity[place].warrior_in_city_temp[0] = this;
		}
		else if (place >= 1 && place <= N - 1) {
			mycity[place].warrior_in_city[0] = NULL;
			place++;
			mycity[place].warrior_in_city_temp[0] = this;
		}
		else if (place == N) {
			mycity[place].warrior_in_city[0] = NULL;
			place++;
			blue.warrior_in_headquarter_temp[0] = this;
			blue.warrior_do_nothing[blue.warrior_do_nothing_counter] = this;
			blue.warrior_do_nothing_counter++;
		}
	}
	else {
		if (place == N + 1) {
			place--;
			mycity[place].warrior_in_city_temp[1] = this;
		}
		else if (place >= 2 && place <= N) {
			mycity[place].warrior_in_city[1] = NULL;
			place--;
			mycity[place].warrior_in_city_temp[1] = this;
		}
		else if (place == 1) {
			mycity[place].warrior_in_city[1] = NULL;
			place--;
			red.warrior_in_headquarter_temp[1] = this;
			red.warrior_do_nothing[red.warrior_do_nothing_counter] = this;
			red.warrior_do_nothing_counter++;
		}
	}
	if (kind == Ciceman) {
		go_on_step++;
		if (go_on_step % 2 == 0) {
			ATT += 20;
			if (HP <= 9)
				HP = 1;
			else HP -= 9;
		}
	}
}
warrior::~warrior() {
	home->exist_num--;
	home->num_of_warrior[kind]--;
}
void warrior::fight(warrior* ptr) {
	if (weapon_ptr[0] != NULL) {//有sword
		ptr->HP = ptr->HP - ATT - weapon_ptr[0]->get_ATT();
		weapon_ptr[0]->blunt();
		if (weapon_ptr[0]->get_ATT() <= 0)
			weapon_ptr[0] = NULL;
	}
	else if (weapon_ptr[0] == NULL)//没有sword
		ptr->HP -= ATT;
}
void warrior::fightback(warrior* ptr) {
	if (kind != Cninja) {
		if (weapon_ptr[0] != NULL) {//有sword
			ptr->HP = ptr->HP - ATT / 2 - weapon_ptr[0]->get_ATT();
			weapon_ptr[0]->blunt();
			if (weapon_ptr[0]->get_ATT() <= 0)
				weapon_ptr[0] = NULL;
		}
		else if (weapon_ptr[0] == NULL)//没有sword
			ptr->HP -= ATT / 2;
	}
}
//dragon成员函数
dragon::dragon(int hHP, int total, Ccolor headcolor) :warrior(hHP, total, headcolor) {//此时司令部中怪物总数还没有++
	kind = Cdragon;
	HP = use_of_HP[0];
	ATT = attack[0];
	double temp_hHP = hHP;
	morale = temp_hHP / use_of_HP[0];
	int weaponid = ID % 3;
	switch (weaponid) {
	case 0:weapon_ptr[0] = new sword(this); 
		if (weapon_ptr[0]->get_ATT() == 0)
			weapon_ptr[0] = NULL; 
		break;
	case 1:weapon_ptr[1] = new bomb(this); break;
	case 2:weapon_ptr[2] = new arrow(this); break;
	}
}
//ninja成员函数
ninja::ninja(int hHP, int total, Ccolor headcolor) :warrior(hHP, total, headcolor) {//此时司令部中怪物总数还没有++
	kind = Cninja;
	HP = use_of_HP[1];
	ATT = attack[1];
	int weaponid;
	for (int i = 0; i < 2; i++) {
		if (i == 1) weaponid = (ID + 1) % 3;
		else weaponid = ID % 3;
		switch (weaponid) {
		case 0:weapon_ptr[0] = new sword(this);
			if (weapon_ptr[0]->get_ATT() == 0)
				weapon_ptr[0] = NULL;
			break;
		case 1:weapon_ptr[1] = new bomb(this); break;
		case 2:weapon_ptr[2] = new arrow(this); break;
		}
	}
}
//iceman成员函数
iceman::iceman(int hHP, int total, Ccolor headcolor) :warrior(hHP, total, headcolor) {//此时司令部中怪物总数还没有++
	kind = Ciceman;
	HP = use_of_HP[2];
	ATT = attack[2];
	int weaponid = ID % 3;
	switch (weaponid) {
	case 0:weapon_ptr[0] = new sword(this); 
		if (weapon_ptr[0]->get_ATT() == 0)
			weapon_ptr[0] = NULL; 
		break;
	case 1:weapon_ptr[1] = new bomb(this); break;
	case 2:weapon_ptr[2] = new arrow(this); break;
	}
}
//lion成员函数
lion::lion(int hHP, int total, Ccolor headcolor) :warrior(hHP, total, headcolor) {//此时司令部中怪物总数还没有++
	kind = Clion;
	HP = use_of_HP[3];
	ATT = attack[3];
	loyalty = hHP;
}
//wolf成员函数
wolf::wolf(int hHP, int total, Ccolor headcolor) :warrior(hHP, total, headcolor) {//此时司令部中怪物总数还没有++
	kind = Cwolf;
	HP = use_of_HP[4];
	ATT = attack[4];
}
//---------------------------------------------------------------------
//weapon成员函数
weapon::weapon(warrior* ptr) {
	owner = ptr;
}
void weapon::blunt() {}
//sword成员函数
int & sword::get_ATT() {
	return ATT;
}
sword::sword(warrior* ptr):weapon(ptr) {
	ATT = ptr->ATT * 2 / 10;
}
void sword::blunt() {
	ATT = ATT * 8 / 10;
}
int & sword::get_left_time() {
	return beiyong;
}
//bomb成员函数
bomb::bomb(warrior* ptr) :weapon(ptr) {};
int & bomb::get_ATT() {
	return beiyong;
}
int & bomb::get_left_time() {
	return beiyong;
}
//arrow成员函数
arrow::arrow(warrior* ptr) :weapon(ptr) {};
int & arrow::get_left_time() {
	return left_time;
}
void arrow::left_time_minus_one() {
	left_time--;
	if (left_time == 0)
		owner->weapon_ptr[2] = NULL;
}
int & arrow::get_ATT() {
	return beiyong;
}
//---------------------------------------------------------------------
//headquarter成员函数
//是否还能继续制造眼下即将要制造的武士，能-true 不能-false
bool headquarter::able_to_make_temp() {
	return use_of_HP[order[to_make]] <= HP;
}
//制造一个武士
void headquarter::make_warrior() {
	HP -= use_of_HP[order[to_make]];
	warrior* temp = NULL;
	switch (order[to_make]) {
	case 0:temp = new dragon(HP, total_num, color);
		cout << setw(3) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute << " " << string_color[color] << " dragon " << temp->ID << " born" << endl;
		cout << "Its morale is ";
		printf("%.2f", temp->morale);
		cout << endl;
		break;
	case 1:temp = new ninja(HP, total_num, color);
		cout << setw(3) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute << " " << string_color[color] << " ninja " << temp->ID << " born" << endl;
		break;
	case 2:temp = new iceman(HP, total_num, color);
		cout << setw(3) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute << " " << string_color[color] << " iceman " << temp->ID << " born" << endl;
		break;
	case 3:temp = new lion(HP, total_num, color);
		cout << setw(3) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute << " " << string_color[color] << " lion " << temp->ID << " born" << endl;
		cout << "Its loyalty is " << temp->loyalty << endl;
		break;
	case 4:temp = new wolf(HP, total_num, color);
		cout << setw(3) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute << " " << string_color[color] << " wolf " << temp->ID << " born" << endl;
		break;
	}
	warrior_in_headquarter[color] = temp;
	++num_of_warrior[order[to_make]];
	++total_num;
	++exist_num;
	to_make = plus_one(to_make);
}
//报告生命元数量
void headquarter::print_HP() {
	cout << setw(3) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute << " " << HP << " elements in " << string_color[color] << " headquarter" << endl;
}
//======================================================================================================
void mymove(warrior** src, warrior** dest) {
	dest[0] = src[0]; src[0] = NULL;
	dest[1] = src[1]; src[1] = NULL;
	return;
}
void renew_warrior_in_city_num() {
	for (int i = 1; i <= N; i++) {
		mycity[i].warrior_in_city_num = 0;
		for (int j = 0; j < 2; j++) {
			if (mycity[i].warrior_in_city[j] != NULL) {
				mycity[i].warrior_in_city_num++;
			}
		}
	}
}
void march_print(){
	if (red.warrior_in_headquarter[1] != NULL) {
		cout << setw(3) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute << " blue " << string_wor[red.warrior_in_headquarter[1]->kind] << " " << red.warrior_in_headquarter[1]->ID << " reached red headquarter with " << red.warrior_in_headquarter[1]->HP << " elements and force " << red.warrior_in_headquarter[1]->ATT << endl;
		red.occupy_num++;
	}
	if (red.occupy_num == 2){
		cout << setw(3) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute << " red headquarter was taken" << endl;
		endflag = true;
	}
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < 2; j++) {
			if (mycity[i].warrior_in_city[j] != NULL) {
				cout << setw(3) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute << " " << string_color[j] << " " << string_wor[mycity[i].warrior_in_city[j]->kind] << " " << mycity[i].warrior_in_city[j]->ID << " marched to city " << i << " with " << mycity[i].warrior_in_city[j]->HP << " elements and force " << mycity[i].warrior_in_city[j]->ATT << endl;
			}
		}
	}
	if (blue.warrior_in_headquarter[0] != NULL) {
		cout << setw(3) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute << " red " << string_wor[blue.warrior_in_headquarter[0]->kind] << " " << blue.warrior_in_headquarter[0]->ID << " reached blue headquarter with " << blue.warrior_in_headquarter[0]->HP << " elements and force " << blue.warrior_in_headquarter[0]->ATT << endl;
		blue.occupy_num++;
		if (blue.occupy_num == 2) {
			cout << setw(3) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute << " blue headquarter was taken" << endl;
			endflag = true;
		}
	}
}
//======================================================================================================
//======================================================================================================
//======================================================================================================
//让该逃跑的狮子逃跑
void lion_ecsape() {
	if (red.warrior_in_headquarter[0] != NULL) {
		if (red.warrior_in_headquarter[0]->kind == Clion) {
			if (red.warrior_in_headquarter[0]->loyalty <= 0) {
				cout << setw(3) << setfill('0') << hour << ":05 red lion " << red.warrior_in_headquarter[0]->ID << " ran away" << endl;
				red.warrior_in_headquarter[0] = NULL;
			}
		}
	}
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < 2; j++) {//先看红色再看蓝色
			if (mycity[i].warrior_in_city[j] != NULL) {
				if (mycity[i].warrior_in_city[j]->kind == Clion/*如果这位是lion*/) {
					if (mycity[i].warrior_in_city[j]->loyalty <= 0) {
						cout << setw(3) << setfill('0') << hour << ":05 " << string_color[j] << " lion " << mycity[i].warrior_in_city[j]->ID << " ran away" << endl;
						mycity[i].warrior_in_city[j] = NULL;
					}
				}
			}
		}
	}
	if (blue.warrior_in_headquarter[1] != NULL) {
		if (blue.warrior_in_headquarter[1]->kind == Clion) {
			if (blue.warrior_in_headquarter[1]->loyalty <= 0) {
				cout << setw(3) << setfill('0') << hour << ":05 blue lion " << blue.warrior_in_headquarter[1]->ID << " ran away" << endl;
				blue.warrior_in_headquarter[1] = NULL;
			}
		}
	}
}
//所有武士前进一步
void warrior_march(){
    for (int i = 0; i < 2; i++)
		if (red.warrior_in_headquarter[i] != NULL)
			red.warrior_in_headquarter[i]->march();
	for (int i = 1; i <= N; i++)
		for (int j = 0; j < 2; j++)
			if (mycity[i].warrior_in_city[j] != NULL)
				mycity[i].warrior_in_city[j]->march();
	for (int i = 0; i < 2; i++)
		if (blue.warrior_in_headquarter[i] != NULL)
			blue.warrior_in_headquarter[i]->march();
}
//------------------------------------------------------------
//武士放箭
void warrior_shot_arrow() {
	for (int i = 1; i <= N; i++)
		mycity[i].arrow_die_mark = 0;

	//红色司令部，只能红武士向右放箭射蓝武士
	if (red.warrior_in_headquarter[0] != NULL && mycity[1].warrior_in_city[1] != NULL) {//存在一对敌人
		if (red.warrior_in_headquarter[0]->weapon_ptr[2] != NULL) {//有arrow，可以放箭
			red.warrior_in_headquarter[0]->weapon_ptr[2]->left_time_minus_one();//arrow减少
			mycity[1].warrior_in_city[1]->HP -= R;//中箭的人HP减少
			if (mycity[1].warrior_in_city[1]->HP <= 0) {//如果射死了
				mycity[1].arrow_die_mark += 2;
				cout << setw(3) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute << " red " << string_wor[red.warrior_in_headquarter[0]->kind] << " " << red.warrior_in_headquarter[0]->ID << " shot and killed blue " << string_wor[mycity[1].warrior_in_city[1]->kind] <<" "<< mycity[1].warrior_in_city[1]->ID << endl;
			}
			else cout << setw(3) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute << " red " << string_wor[red.warrior_in_headquarter[0]->kind] << " " << red.warrior_in_headquarter[0]->ID << " shot" << endl;
		}
	}
	//city 1 red shot blue
	if (mycity[1].warrior_in_city[0] != NULL && mycity[2].warrior_in_city[1] != NULL) {
		if (mycity[1].warrior_in_city[0]->weapon_ptr[2] != NULL) {
			mycity[1].warrior_in_city[0]->weapon_ptr[2]->left_time_minus_one();
			mycity[2].warrior_in_city[1]->HP -= R;
			if (mycity[2].warrior_in_city[1]->HP <= 0) {
				mycity[2].arrow_die_mark += 2;
				cout << setw(3) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute << " red " << string_wor[mycity[1].warrior_in_city[0]->kind] << " " << mycity[1].warrior_in_city[0]->ID << " shot and killed blue " << string_wor[mycity[2].warrior_in_city[1]->kind] << " " << mycity[1 + 1].warrior_in_city[1]->ID << endl;
			}
			else cout << setw(3) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute << " red " << string_wor[mycity[1].warrior_in_city[0]->kind] << " " << mycity[1].warrior_in_city[0]->ID << " shot" << endl;
		}
	}
	//2~N-1的城市按序号依次筛选,红武士射蓝武士
	for (int i = 2; i <= N-1; i++) {
		if (mycity[i].warrior_in_city[0] != NULL && mycity[i + 1].warrior_in_city[1] != NULL) {
			if (mycity[i].warrior_in_city[0]->weapon_ptr[2] != NULL) {
				mycity[i].warrior_in_city[0]->weapon_ptr[2]->left_time_minus_one();
				mycity[i + 1].warrior_in_city[1]->HP -= R;
				if (mycity[i + 1].warrior_in_city[1]->HP <= 0) {
					mycity[i + 1].arrow_die_mark += 2;
					cout << setw(3) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute << " red " << string_wor[mycity[i].warrior_in_city[0]->kind] << " " << mycity[i].warrior_in_city[0]->ID << " shot and killed blue " << string_wor[mycity[i+1].warrior_in_city[1]->kind] << " " << mycity[i + 1].warrior_in_city[1]->ID << endl;
				}
				else cout << setw(3) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute << " red " << string_wor[mycity[i].warrior_in_city[0]->kind] << " " << mycity[i].warrior_in_city[0]->ID << " shot" << endl;
			}
		}
		if (mycity[i].warrior_in_city[1] != NULL && mycity[i - 1].warrior_in_city[0] != NULL) {
			if (mycity[i].warrior_in_city[1]->weapon_ptr[2] != NULL) {
				mycity[i].warrior_in_city[1]->weapon_ptr[2]->left_time_minus_one();
				mycity[i - 1].warrior_in_city[0]->HP -= R;
				if (mycity[i - 1].warrior_in_city[0]->HP <= 0) {
					mycity[i - 1].arrow_die_mark += 1;
					cout << setw(3) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute << " blue " << string_wor[mycity[i].warrior_in_city[1]->kind] << " " << mycity[i].warrior_in_city[1]->ID << " shot and killed red " << string_wor[mycity[i - 1].warrior_in_city[0]->kind] << " " << mycity[i - 1].warrior_in_city[0]->ID << endl;
				}
				else cout << setw(3) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute << " blue " << string_wor[mycity[i].warrior_in_city[1]->kind] << " " << mycity[i].warrior_in_city[1]->ID << " shot" << endl;
			}
		}
	}
	if (mycity[N].warrior_in_city[1] != NULL && mycity[N-1].warrior_in_city[0] != NULL) {
		if (mycity[N].warrior_in_city[1]->weapon_ptr[2] != NULL) {
			mycity[N].warrior_in_city[1]->weapon_ptr[2]->left_time_minus_one();
			mycity[N - 1].warrior_in_city[0]->HP -= R;
			if (mycity[N - 1].warrior_in_city[0]->HP <= 0) {
				mycity[N - 1].arrow_die_mark += 1;
				cout << setw(3) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute << " blue " << string_wor[mycity[N].warrior_in_city[1]->kind] << " " << mycity[N].warrior_in_city[1]->ID << " shot and killed red " << string_wor[mycity[N - 1].warrior_in_city[0]->kind] << " " << mycity[N - 1].warrior_in_city[0]->ID << endl;
			}
			else cout << setw(3) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute << " blue " << string_wor[mycity[N].warrior_in_city[1]->kind] << " " << mycity[N].warrior_in_city[1]->ID << " shot" << endl;
		}
	}
	//蓝色司令部，只能蓝武士射红武士
	if (blue.warrior_in_headquarter[1] != NULL && mycity[N].warrior_in_city[0] != NULL) {
		if (blue.warrior_in_headquarter[1]->weapon_ptr[2] != NULL) {
			blue.warrior_in_headquarter[1]->weapon_ptr[2]->left_time_minus_one();
			mycity[N].warrior_in_city[0]->HP -= R;
			if (mycity[N].warrior_in_city[0]->HP <= 0) {
				mycity[N].arrow_die_mark += 1;
				cout << setw(3) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute << " blue " << string_wor[blue.warrior_in_headquarter[1]->kind] << " " << blue.warrior_in_headquarter[1]->ID << " shot and killed red " << string_wor[mycity[N].warrior_in_city[0]->kind] << " " << mycity[N].warrior_in_city[0]->ID << endl;
			}
			else cout << setw(3) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute << " blue " << string_wor[blue.warrior_in_headquarter[1]->kind] << " " << blue.warrior_in_headquarter[1]->ID << " shot" << endl;
		}
	}
}
//------------------------------------------------------------
//武士放炸弹
void warrior_use_bomb() {
	for (int i = 1; i <= N; i++) {//逐个城市判断
		if (mycity[i].warrior_in_city_num == 2)
			if (mycity[i].warrior_in_city[0]->HP > 0 && mycity[i].warrior_in_city[1]->HP > 0) {
				int red_ATT = mycity[i].warrior_in_city[0]->ATT;
				int red_sword = 0;
				if (mycity[i].warrior_in_city[0]->weapon_ptr[0] != NULL)
					red_sword = mycity[i].warrior_in_city[0]->weapon_ptr[0]->get_ATT();
				int blue_ATT = mycity[i].warrior_in_city[1]->ATT;
				int blue_sword = 0;
				if (mycity[i].warrior_in_city[1]->weapon_ptr[0] != NULL)
					blue_sword = mycity[i].warrior_in_city[1]->weapon_ptr[0]->get_ATT();
				int red_decide = 0;
				int blue_decide = 0;
				if (mycity[i].flag == Credflag || mycity[i].flag == Cnoflag && i % 2 == 1) {//红色先手
					red_decide = blue_sword + blue_ATT / 2;
					blue_decide = red_sword + red_ATT;
					if (mycity[i].warrior_in_city[1]->kind != Cninja) {
						if (blue_decide >= mycity[i].warrior_in_city[1]->HP
							&& mycity[i].warrior_in_city[1]->weapon_ptr[1] != NULL) {//蓝武士用bomb
							mycity[i].warrior_in_city[1]->weapon_ptr[1] = NULL;
							mycity[i].warrior_in_city[0]->HP = 0; mycity[i].warrior_in_city[1]->HP = 0;
							cout << setw(3) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute << " blue " << string_wor[mycity[i].warrior_in_city[1]->kind] << " " << mycity[i].warrior_in_city[1]->ID << " used a bomb and killed red " << string_wor[mycity[i].warrior_in_city[0]->kind] << " " << mycity[i].warrior_in_city[0]->ID << endl;
						}
						else if (red_decide >= mycity[i].warrior_in_city[0]->HP
							&& mycity[i].warrior_in_city[0]->weapon_ptr[1] != NULL
							&& blue_decide < mycity[i].warrior_in_city[1]->HP) {//红武士用bomb
							mycity[i].warrior_in_city[0]->weapon_ptr[1] = NULL;
							mycity[i].warrior_in_city[0]->HP = 0; mycity[i].warrior_in_city[1]->HP = 0;
							cout << setw(3) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute << " red " << string_wor[mycity[i].warrior_in_city[0]->kind] << " " << mycity[i].warrior_in_city[0]->ID << " used a bomb and killed blue " << string_wor[mycity[i].warrior_in_city[1]->kind] << " " << mycity[i].warrior_in_city[1]->ID << endl;
						}
					}
					else {
						if (blue_decide >= mycity[i].warrior_in_city[1]->HP
							&& mycity[i].warrior_in_city[1]->weapon_ptr[1] != NULL) {//蓝武士用bomb
							mycity[i].warrior_in_city[1]->weapon_ptr[1] = NULL;
							mycity[i].warrior_in_city[0]->HP = 0; mycity[i].warrior_in_city[1]->HP = 0;
							cout << setw(3) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute << " blue " << string_wor[mycity[i].warrior_in_city[1]->kind] << " " << mycity[i].warrior_in_city[1]->ID << " used a bomb and killed red " << string_wor[mycity[i].warrior_in_city[0]->kind] << " " << mycity[i].warrior_in_city[0]->ID << endl;
						}
					}
				}
				else if (mycity[i].flag == Cblueflag || mycity[i].flag == Cnoflag && i % 2 == 0) {//蓝色先手
					red_decide = blue_ATT + blue_sword;
					blue_decide = red_ATT / 2 + red_sword;
					if (mycity[i].warrior_in_city[0]->kind != Cninja) {
						if (red_decide >= mycity[i].warrior_in_city[0]->HP
							&& mycity[i].warrior_in_city[0]->weapon_ptr[1] != NULL) {//红武士用bomb
							mycity[i].warrior_in_city[0]->weapon_ptr[1] = NULL;
							mycity[i].warrior_in_city[0]->HP = 0; mycity[i].warrior_in_city[1]->HP = 0;
							cout << setw(3) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute << " red " << string_wor[mycity[i].warrior_in_city[0]->kind] << " " << mycity[i].warrior_in_city[0]->ID << " used a bomb and killed blue " << string_wor[mycity[i].warrior_in_city[1]->kind] << " " << mycity[i].warrior_in_city[1]->ID << endl;
						}
						else if (blue_decide >= mycity[i].warrior_in_city[1]->HP
							&& mycity[i].warrior_in_city[1]->weapon_ptr[1] != NULL
							&& red_decide < mycity[i].warrior_in_city[0]->HP) {//蓝武士用bomb
							mycity[i].warrior_in_city[1]->weapon_ptr[1] = NULL;
							mycity[i].warrior_in_city[0]->HP = 0; mycity[i].warrior_in_city[1]->HP = 0;
							cout << setw(3) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute << " blue " << string_wor[mycity[i].warrior_in_city[1]->kind] << " " << mycity[i].warrior_in_city[1]->ID << " used a bomb and killed red " << string_wor[mycity[i].warrior_in_city[0]->kind] << " " << mycity[i].warrior_in_city[0]->ID << endl;
						}
					}
					else {
						if (red_decide >= mycity[i].warrior_in_city[0]->HP
							&& mycity[i].warrior_in_city[0]->weapon_ptr[1] != NULL) {//红武士用bomb
							mycity[i].warrior_in_city[0]->weapon_ptr[1] = NULL;
							mycity[i].warrior_in_city[0]->HP = 0; mycity[i].warrior_in_city[1]->HP = 0;
							cout << setw(3) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute << " red " << string_wor[mycity[i].warrior_in_city[0]->kind] << " " << mycity[i].warrior_in_city[0]->ID << " used a bomb and killed blue " << string_wor[mycity[i].warrior_in_city[1]->kind] << " " << mycity[i].warrior_in_city[1]->ID << endl;
						}
					}
				}
			}
	}
}
//------------------------------------------------------------
//此处已经保证了双方都有血 // 攻击顺序 // i-城市编号
void attack_between_two(int i, warrior * wred, warrior * wblue){
	if (mycity[i].flag == Credflag || mycity[i].flag == Cnoflag && i % 2 == 1) {//红色先手
		wred->fight(wblue);
		cout << setw(3) << setfill('0') << hour << ":40 red " << string_wor[wred->kind] << " " << wred->ID << " attacked blue " << string_wor[wblue->kind] << " " << wblue->ID << " in city " << i << " with " << wred->HP << " elements and force " << wred->ATT << endl;
		if (wblue->HP > 0) {//蓝色没死，则反击
			wblue->fightback(wred);
			if (wblue->kind != Cninja)
				cout << setw(3) << setfill('0') << hour << ":40 blue " << string_wor[wblue->kind] << " " << wblue->ID << " fought back against red " << string_wor[wred->kind] << " " << wred->ID << " in city " << i << endl;
			if (wred->HP <= 0) {//蓝色反击杀死红色
				cout << setw(3) << setfill('0') << hour << ":40 red " << string_wor[wred->kind] << " " << wred->ID << " was killed in city " << i << endl;
				mycity[i].fight_die_mark += 1;
			}
		}
		else {//红色杀死蓝色
			cout << setw(3) << setfill('0') << hour << ":40 blue " << string_wor[wblue->kind] << " " << wblue->ID << " was killed in city " << i << endl;
			mycity[i].fight_die_mark += 2;
		}
	}
	else if (mycity[i].flag == Cblueflag || mycity[i].flag == Cnoflag && i % 2 == 0) {//蓝色先手
		wblue->fight(wred);
		cout << setw(3) << setfill('0') << hour << ":40 blue " << string_wor[wblue->kind] << " " << wblue->ID << " attacked red " << string_wor[wred->kind] << " " << wred->ID << " in city " << i << " with " << wblue->HP << " elements and force " << wblue->ATT << endl;
		if (wred->HP > 0) {//红色没死，则反击
			wred->fightback(wblue);
			if (wred->kind != Cninja)
				cout << setw(3) << setfill('0') << hour << ":40 red " << string_wor[wred->kind] << " " << wred->ID << " fought back against blue " << string_wor[wblue->kind] << " " << wblue->ID << " in city " << i << endl;
			if (wblue->HP <= 0) {//红色反击杀死蓝色
				cout << setw(3) << setfill('0') << hour << ":40 blue " << string_wor[wblue->kind] << " " << wblue->ID << " was killed in city " << i << endl;
				mycity[i].fight_die_mark += 2;
			}
		}
		else {//蓝色杀死红色
			cout << setw(3) << setfill('0') << hour << ":40 red " << string_wor[wred->kind] << " " << wred->ID << " was killed in city " << i << endl;
			mycity[i].fight_die_mark += 1;
		}
	}
}
void attack_in_world(){//发生战斗
	for (int i = 1; i <= N; i++) {//逐个城市看有没有战争，如果有，进行战争
		//fight and fight back
		mycity[i].fight_die_mark = 0;
		if (mycity[i].warrior_in_city[0] != NULL && mycity[i].warrior_in_city[1] != NULL){
			if (mycity[i].warrior_in_city[0]->HP > 0 && mycity[i].warrior_in_city[1]->HP > 0) {
				attack_between_two(i, mycity[i].warrior_in_city[0], mycity[i].warrior_in_city[1]);
			}
		}
		//dragon yell
		if (mycity[i].warrior_in_city_num == 2) {
			for (int j = 0; j < 2; j++) {//先看红色再看蓝色
				if (mycity[i].warrior_in_city[j]->kind == Cdragon/*如果这位是dragon*/) {
					if (mycity[i].warrior_in_city[j]->HP > 0/*这位活着*/) {
						if (mycity[i].warrior_in_city[1 - j]->HP <= 0/*另一位死了*/)
							mycity[i].warrior_in_city[j]->morale += 0.2;
						else if (mycity[i].warrior_in_city[1 - j]->HP > 0/*另一位也活着*/)
							mycity[i].warrior_in_city[j]->morale -= 0.2;
						if (mycity[i].warrior_in_city[j]->color == mycity[i].flag || (mycity[i].flag == Cnoflag && (i + 1) % 2 == j))
							if (mycity[i].warrior_in_city[j]->morale > 0.8)
								cout << setw(3) << setfill('0') << hour << ":40 " << string_color[j] << " dragon " << mycity[i].warrior_in_city[j]->ID << " yelled in city " << i << endl;
					}
				}
			}
		}
		//wolf rob
		if (mycity[i].warrior_in_city_num == 2) {
			for (int j = 0; j < 2; j++) {//先看红色再看蓝色
				if (mycity[i].warrior_in_city[j]->kind == Cwolf/*如果这位是wolf*/) {
					if (mycity[i].warrior_in_city[j]->HP > 0/*这位活着*/) {
						if (mycity[i].warrior_in_city[1 - j]->HP <= 0/*另一位死了*/) {
							for (int k = 0; k < 3; k++) {
								if (mycity[i].warrior_in_city[j]->weapon_ptr[k] == NULL && mycity[i].warrior_in_city[1 - j]->weapon_ptr[k] != NULL) {
									mycity[i].warrior_in_city[j]->weapon_ptr[k] = mycity[i].warrior_in_city[1 - j]->weapon_ptr[k];
									mycity[i].warrior_in_city[1 - j]->weapon_ptr[k] = NULL;
									mycity[i].warrior_in_city[j]->weapon_ptr[k]->owner = mycity[i].warrior_in_city[j];
								}
							}
						}
					}
				}
			}
		}
		//get HP(temp) and change flag
		if (mycity[i].warrior_in_city_num == 2) {
			if (mycity[i].warrior_in_city[0]->HP > 0 && mycity[i].warrior_in_city[1]->HP <= 0) {
				if (mycity[i].change_flag <= 0)
					mycity[i].change_flag -= 1;
				else mycity[i].change_flag = -1;
				mycity[i].warrior_in_city[0]->home->HP_win_get += mycity[i].HP;
				cout << setw(3) << setfill('0') << hour << ":40 red " << string_wor[mycity[i].warrior_in_city[0]->kind] << " " << mycity[i].warrior_in_city[0]->ID << " earned "<<mycity[i].HP<<" elements for his headquarter" << endl;
				mycity[i].HP = 0;
				//if (i == 9)cout << "红色赢一次 红色赢一次 红色赢一次 红色赢一次 红色赢一次 红色赢一次 红色赢一次 红色赢一次 红色赢一次 红色赢一次" << endl;
			}
			else if (mycity[i].warrior_in_city[0]->HP <= 0 && mycity[i].warrior_in_city[1]->HP > 0) {
				if(mycity[i].change_flag>=0)
					mycity[i].change_flag += 1;
				else mycity[i].change_flag = 1;
				mycity[i].warrior_in_city[1]->home->HP_win_get += mycity[i].HP;
				cout << setw(3) << setfill('0') << hour << ":40 blue " << string_wor[mycity[i].warrior_in_city[1]->kind] << " " << mycity[i].warrior_in_city[1]->ID << " earned " << mycity[i].HP << " elements for his headquarter" << endl;
				mycity[i].HP = 0;
				//if (i == 9)cout << "蓝色赢一次 蓝色赢一次 蓝色赢一次 蓝色赢一次 蓝色赢一次 蓝色赢一次 蓝色赢一次 蓝色赢一次 蓝色赢一次 蓝色赢一次" << endl;
			}
			else if (mycity[i].warrior_in_city[0]->HP > 0 && mycity[i].warrior_in_city[1]->HP > 0) {
				mycity[i].change_flag = 0;
				//if(i==9) cout << "平局 平局 平局 平局 平局 平局 平局 平局 平局 平局 平局 平局 平局 平局 平局 平局 平局 平局 平局 平局" << endl;
			}
			//else if (i == 9) cout << "无事发生 无事发生 无事发生 无事发生 无事发生 无事发生 无事发生 无事发生 无事发生 无事发生 无事发生 无事发生" << endl;
			//----------------change flag------------------
			if (mycity[i].change_flag == -2) {
				Cflag temp = mycity[i].flag;
				mycity[i].flag = Credflag;
				if(temp!=Credflag)
					cout << setw(3) << setfill('0') << hour << ":40 red flag raised in city " << i << endl;
			}
			else if (mycity[i].change_flag == 2) {
				Cflag temp = mycity[i].flag;
				mycity[i].flag = Cblueflag;
				if (temp != Cblueflag)
					cout << setw(3) << setfill('0') << hour << ":40 blue flag raised in city " << i << endl;
			}
		}
	}
	//红色司令部奖励武士
	for (int i = N; i >= 1; i--)
		if (mycity[i].warrior_in_city_num == 2)
			if (mycity[i].warrior_in_city[0]->HP > 0 && mycity[i].warrior_in_city[1]->HP <= 0 && red.HP >= 8) {
				mycity[i].warrior_in_city[0]->HP += 8;
				red.HP -= 8;
			}
	//蓝色司令部奖励武士
	for (int i = 1; i <= N; i++)
		if (mycity[i].warrior_in_city_num == 2)
			if (mycity[i].warrior_in_city[1]->HP > 0 && mycity[i].warrior_in_city[0]->HP <= 0 && blue.HP >= 8) {
				mycity[i].warrior_in_city[1]->HP += 8;
				blue.HP -= 8;
			}
	red.HP += red.HP_win_get; red.HP_win_get = 0;
	blue.HP += blue.HP_win_get; blue.HP_win_get = 0;
}
//------------------------------------------------------------
void record_lion_HP() {
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < 2; j++) {//先看红色再看蓝色
			if (mycity[i].warrior_in_city[j] != NULL) {
				if (mycity[i].warrior_in_city[j]->kind == Clion/*如果这位是lion*/) {
					if (mycity[i].warrior_in_city[j]->HP > 0/*这位活着*/) {
						mycity[i].lion_HP_mark[j] = mycity[i].warrior_in_city[j]->HP;
					}
				}
			}
		}
	}
}
void lion_alive_loyalty_decrease() {
	for (int i = 1; i <= N; i++) {
		if (mycity[i].warrior_in_city_num == 2) {
			for (int j = 0; j < 2; j++) {//先看红色再看蓝色
				if (mycity[i].warrior_in_city[j]->kind == Clion/*如果这位是lion*/) {
					if (mycity[i].warrior_in_city[j]->HP > 0/*这位活着*/) {
						if (mycity[i].warrior_in_city[1 - j]->HP > 0/*另一位没死*/) {
							mycity[i].warrior_in_city[j]->loyalty -= K;
						}
					}
				}
			}
		}
	}
}
void lion_dead_HP_move() {
	for (int i = 1; i <= N; i++) {
		if (mycity[i].warrior_in_city_num == 2) {
			for (int j = 0; j < 2; j++) {//先看红色再看蓝色
				if (mycity[i].warrior_in_city[j]->kind == Clion/*如果这位是lion*/) {
					if (mycity[i].warrior_in_city[j]->HP <= 0/*这位死了*/) {
						if (mycity[i].warrior_in_city[1 - j]->HP > 0/*另一位没死*/) {
							mycity[i].warrior_in_city[1 - j]->HP += mycity[i].lion_HP_mark[j];
						}
					}
				}
			}
		}
	}
}
void delete_dead() {
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < 2; j++) {
			if (mycity[i].warrior_in_city[j]!=NULL) {
				if (mycity[i].warrior_in_city[j]->HP <= 0) {
					mycity[i].warrior_in_city[j] = NULL;
				}
			}
		}
	}
}
//------------------------------------------------------------
void print_weapon(warrior* tempwarrior) {
	if (tempwarrior->weapon_ptr[0] == NULL && tempwarrior->weapon_ptr[1] == NULL && tempwarrior->weapon_ptr[2] == NULL)
		cout << setw(3) << setfill('0') << hour << ":55 " << string_color[tempwarrior->color] << " " << string_wor[tempwarrior->kind] << " " << tempwarrior->ID << " has no weapon" << endl;
	else {
		cout << setw(3) << setfill('0') << hour << ":55 " << string_color[tempwarrior->color] << " " << string_wor[tempwarrior->kind] << " " << tempwarrior->ID << " has ";
		bool first_flag = true;
		for (int k = 2; k >= 0; k--) {
			if (tempwarrior->weapon_ptr[k] != NULL) {
				if (first_flag == false)  cout << ",";
				switch (k) {
				case 0:cout << "sword(" << tempwarrior->weapon_ptr[k]->get_ATT() << ")";
					break;
				case 1:cout << "bomb";
					break;
				case 2:cout << "arrow(" << tempwarrior->weapon_ptr[k]->get_left_time() << ")";
					break;
				}
				first_flag = false;
			}
		}
		cout << endl;
	}
}
void warrior_report() {
	for (int j = 0; j < 2; j++) {
		if (j == 1) {
			for (int k = 0; k < 2; k++) {
				warrior* tempwarrior = red.warrior_do_nothing[k];
				if (tempwarrior != NULL)
					print_weapon(tempwarrior);
			}
		}
		for (int i = 1; i <= N; i++) {
			warrior* tempwarrior = mycity[i].warrior_in_city[j];
			if (tempwarrior != NULL) {
				print_weapon(tempwarrior);
			}
		}
		if (j == 0) {
			for (int k = 0; k < 2; k++) {
				warrior* tempwarrior = blue.warrior_do_nothing[k];
				if (tempwarrior != NULL)
					print_weapon(tempwarrior);
			}
		}
	}
}
//======================================================================================================
void timepass(int endtime){
	while (nowtime <= endtime && endflag != true) {
		minute = nowtime % 60;
		hour = nowtime / 60;
		switch (minute){
		case 0:
			//先判断能不能制造
			if (red.able_to_make_temp() == true)
				red.make_warrior();
			if (blue.able_to_make_temp() == true)
				blue.make_warrior();
			break;
		case 5:
			lion_ecsape();
			break;
		case 10:
			warrior_march();
			//从temp搬到正式的数组里
			mymove(red.warrior_in_headquarter_temp, red.warrior_in_headquarter);
			mymove(blue.warrior_in_headquarter_temp, blue.warrior_in_headquarter);
			for (int i = 1; i <= N; i++)
				mymove(mycity[i].warrior_in_city_temp, mycity[i].warrior_in_city);
			march_print();
			break;
		case 20:
			for (int i = 1; i <= N; i++)
				mycity[i].produce_HP();
			break;
		case 30:
			//没有对手的武士取走生命元
			renew_warrior_in_city_num();
			for (int i = 1; i <= N; i++) {
				if (mycity[i].warrior_in_city_num == 1) {
					if (mycity[i].warrior_in_city[0] != NULL) {//red
						red.HP += mycity[i].HP;
						cout << setw(3) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute << " red " << string_wor[mycity[i].warrior_in_city[0]->kind] << " " << mycity[i].warrior_in_city[0]->ID << " earned "<<mycity[i].HP<<" elements for his headquarter" << endl;
						mycity[i].HP = 0;
					}
					else if (mycity[i].warrior_in_city[1] != NULL) {
						blue.HP += mycity[i].HP;
						cout << setw(3) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute << " blue " << string_wor[mycity[i].warrior_in_city[1]->kind] << " " << mycity[i].warrior_in_city[1]->ID << " earned "<< mycity[i].HP<<" elements for his headquarter" << endl;
						mycity[i].HP = 0;
					}
				}
			}
			break;
		case 35:
			//有arrow的武士放箭
			warrior_shot_arrow();
			break;
		case 38:
			//拥有bomb的武士评估是否应该使用bomb。如果是，就用bomb和敌人同归于尽
			warrior_use_bomb();
			break;
		case 40:
			for (int i = 1; i <= N; i++)
				for (int j = 0; j < 2; j++)
					mycity[i].lion_HP_mark[j] = 0;
			record_lion_HP();
			attack_in_world();
			lion_alive_loyalty_decrease();//lion忠诚度修改
			lion_dead_HP_move();//lion的HP转移
			delete_dead();//删掉HP<=0的武士
			break;
		case 50:
			red.print_HP();
			blue.print_HP();
			break;
		case 55:
			warrior_report();
			break;
		default:break;
		}
		++nowtime;
	}
}
//======================================================================================================
void reset() {
	for (int i = 1; i <= N; i++) {
		mycity[i].arrow_die_mark = 0;
		mycity[i].change_flag = 0;
		mycity[i].fight_die_mark = 0;
		mycity[i].flag = Cnoflag;
		mycity[i].HP = 0;
		mycity[i].HP_win_get = 0;
		for (int j = 0; j < 2; j++) {
			mycity[i].warrior_in_city[j] = NULL;
			mycity[i].warrior_in_city_temp[j] = NULL;
			mycity[i].lion_HP_mark[j] = 0;
		}
		mycity[i].warrior_in_city_num = 0;
	}
	for (int j = 0; j < 2; j++) {
		red.warrior_do_nothing[j] = NULL;
		blue.warrior_do_nothing[j] = NULL;
		red.warrior_in_headquarter[j] = NULL;
		blue.warrior_in_headquarter[j] = NULL;
		red.warrior_in_headquarter_temp[j] = NULL;
		blue.warrior_in_headquarter_temp[j] = NULL;
	}
	red.total_num = 0; blue.total_num = 0;
	red.HP_win_get = 0; blue.HP_win_get = 0;
	red.occupy_num = 0; blue.occupy_num = 0;
	red.to_make = 0; blue.to_make = 0;
	red.change_flag = 0; red.warrior_do_nothing_counter = 0;
	blue.change_flag = 0; blue.warrior_do_nothing_counter = 0;
	endflag = false;
	nowtime = 0; minute = 0; hour = 0;
}
//======================================================================================================
int main(){
	red.color = Cred; 
	blue.color = Cblue; 
	red.order[0] = 2;red.order[1] = 3;red.order[2] = 4;red.order[3] = 1;red.order[4] = 0;
	blue.order[0] = 3; blue.order[1] = 0; blue.order[2] = 1; blue.order[3] = 2; blue.order[4] = 4;
	cin >> gr;
	int counter = 1;
	while (gr > 0) {
		reset();
		cout << "Case " << counter << ":" << endl;
		cin >> M >> N >> R >> K >> T;
		red.HP = M; blue.HP = M;
		for (int i = 0; i < 5; i++)
			cin >> use_of_HP[i];
		for (int i = 0; i < 5; i++)
			cin >> attack[i];
		timepass(T);
		counter++;
		gr--;
	}
	return 0;
}