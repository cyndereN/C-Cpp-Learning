// private只有自己能访问，但是也想要类外特殊的一些函数或类进行访问，就需要用到友元的技术
// 关键字 friend
// 三种实现:
// · 全局函数作友元
// · 类作友元
// · 成员函数做友元

class Building {
	//goodGay全局函数是Building好朋友，可以访问building中私有成员
	friend void goodGay(Building& building);

	// GoodGay类是本类的友元，可以访问本类中私有成员
	friend class GoodGay;

	// GoodGay类下visit01成员函数是本类的友元，可以访问本类中私有成员
	friend void GoodGay::visit01();


public:
	string m_sittingroom;
	Building() {
		m_sittingroom = "客厅";
		m_bedroom = "卧室";
	}
private:
	string m_bedroom;
};


//  全局函数
void goodGay(Building& building) {
	cout << "友元全局函数访问客厅" << building.m_sittingroom << endl;
	cout << "友元全局函数访问卧室" << building.m_bedroom << endl;
}

void test01() {
	Building b;
	goodGay(b);
}

/*********************************************************/
// 类做友元
class GoodGay {

public:
	Building* building;

	void visit();  // 访问building中属性

	void visit01();
};

// 类外写成员函数
Building::Building() {
	m_sittingroom = "客厅";
	m_bedroom = "卧室";
}

GoodGay::GoodGay() {
	// 创建建筑物对象
	building = new Building;
}

void GoodGay::visit() {
	cout << "好基友类正在访问: " << building->m_sittingroom << endl;
	cout << "好基友类正在访问: " << building->m_bedroom << endl;
}

void test02() {
	GoodGay gg;
	gg.visit();
}

/*********************************************************/
void GoodGay::visit01() {
	cout << "好基友类正在访问: " << building->m_sittingroom << endl;
	cout << "好基友类vist01函数正在访问: " << building->m_bedroom << endl;
}