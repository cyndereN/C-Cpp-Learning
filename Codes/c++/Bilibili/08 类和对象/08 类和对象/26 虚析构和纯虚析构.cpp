// 可以解决父类指针释放子类对象
// 需要有具体函数实现
// 如果是纯虚析构，该类属于抽象类，无法实例化

class Animal {
public:
	Animal() {
		cout << "Animal构造函数调用" << endl;
	}

	//virtual ~Animal() {
	//	// 虚析构 可以解决父类指针释放子类对象时不干净的问题
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