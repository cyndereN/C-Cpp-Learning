// 静态多态：函数重载和运算符重载属于静态多态，复用函数名
// 动态多态：派生类和虚函数实现运行时多态

// 静态多台的函数地址早绑定 - 编译阶段确定
// 动态多态的函数地址晚绑定 - 运行阶段确定

// 动态多态满足条件：
// 1. 有继承关系
// 2. 子类重写父类虚函数

class Animal { // 不加虚函数，空类，大小是1字节。加了virtual关键字，变成了4字节（类内部多了个指向虚函数表的指针）
public:
	// 虚函数 地址晚绑定
	virtual void speak() {
		cout << "动物在说话" << endl;
	}
};

class Cat :public Animal {
public:
	// 重写 函数返回值类型 函数名 参数列表完全相同

	// 自身的虚函数表换掉 会替换成子类的虚函数地址
	void speak() {
		cout << "猫在说话" << endl;
	}
};

// 地址早绑定 在编译阶段确定函数地址 一定会打出"动物在说话"
// 如果想执行让猫说话，需要在运行阶段绑定，解决：在void speak()前加virtual
void doSpeak(Animal& animal) {
	animal.speak();
}

void test01() {
	Cat cat;
	// 当父类的指针或者引用指向子类对象的时候，发生多态
	// 从cat的虚函数表中找cat说话的函数
	doSpeak(cat);// Animal &animal = cat;

}