// C++中，构造函数不可以是虚函数，而析构函数可以且常常是虚函数。

// 虚函数表是由编译器自动生成与维护的，virtual成员函数会被编译器放入虚函数表中，当存在虚函数时，每个对象都有一个指向虚函数的指针（vptr指针）。
// 在实现多态的过程中，父类和派生类都有vptr指针。
// vptr的初始化：当对象在创建时，由编译器对vptr指针进行初始化。在定义子类对象时，vptr先指向父类的虚函数表，在父类构造完成之后，子类的vptr才指向自己的虚函数表。
// 如果构造函数时虚函数，那么调用构造函数就需要去找vptr，而此时vptr还没有初始化。
// 因此，构造函数不可以是虚函数。

// 可以解决父类指针释放子类对象时，只有基类会被释放，而子类没有释放，存在内存泄漏的隐患问题。
// 需要有具体函数实现
// 如果是纯虚析构，该类属于抽象类，无法实例化

class Animal {
public:
	Animal() {
		cout << "Animal构造函数调用" << endl;
	}

	//virtual ~Animal() {
	// 虚析构 可以解决父类指针释放子类对象时不干净的问题
	//	cout << "Animal虚析构函数调用" << endl;
	//}

	// 纯虚析构，需要代码实现
	// 有了纯虚析构之后，这个类也属于抽象类，无法实例化对象
	virtual ~Animal() = 0;

	// 纯虚函数
	virtual void speak() = 0;
};
Animal::~Animal() {
	cout << "Animal纯虚析构函数调用" << endl;
}

class Cat : public Animal {
public:
	Cat(string name) {
		cout << "Cat 构造函数调用" << endl;
		m_name = new string(name); // 开辟到堆区，需要用到子类中的析构
	}
	void speak() {
		cout << *m_name << "猫在说话" << endl;
	}

	~Cat() {
		if (m_name != NULL) {
			cout << "Cat 析构函数调用" << endl;
			delete m_name;
			m_name = NULL;
		}
	}
	string* m_name;
};

void test01() {
	Animal* animal = new Cat('Tom');
	animal->speak();
	// 父类指针在析构时候不会调用子类中析构函数
	// 导致子类如果有堆区属性，出现内存泄漏
	delete animal;
}