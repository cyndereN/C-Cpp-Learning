// 菱形继承会引发二义性，因为孙子的两个父类均继承了爷爷类，而只需一份就够

class Animal {
public:
	int m_Age;
};
class Sheep : virtual public Animal {

};
class Tuo : virtual public Animal {

};

class SheepTuo :public Sheep, public Tuo {

};

void test01() {
	SheepTuo st;
	// 当菱形继承，两个父类拥有相同数据，需要加以作用域区分
	st.Sheep::m_Age = 18;
	st.Tuo::m_Age = 28;
	// 这份数据我们知道有一份就可以，菱形继承导致有两份，资源浪费

	// 利用虚继承解决菱形继承的问题，继承时在父类的前面加virtual
}