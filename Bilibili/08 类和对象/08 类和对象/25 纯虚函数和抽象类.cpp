// 在多态中，通常父类中的虚函数实现是毫无意义的，主要都是调用子类重写的内容
// 因此可以将虚函数改为纯虚函数
// 当有了春旭函数，这个类也称为抽象类

// 抽象类特点：
// · 无法实例化对象
// · 子类必须重写抽象类中的纯虚函数，否则也属于抽象类

class Base {
public:
	// 纯虚函数
	virtual void func() = 0;
};

class Son :public Base {
public:
	// 必须重写否则无法实例化
	void func() {
		cout << "func函数的调用" << endl;
	}
};


void test01() {
	Base* base = new Son;
	base->func();
}