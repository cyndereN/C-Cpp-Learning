// 继承方式有三种：公共，保护，私有

// 先构造父类，再构造子类
// 析构顺序和构造顺序相反

class A {
public:
	int a;
protected: // 只有友元，类自身和派生类能访问
	int b;
private:   // 也会继承，只不过被隐藏
	int c;
};

// 公有继承
class B : public A {
public:
	int a;
protected:
	int b;
不可访问:
	int c;
};

// 保护继承
class B : protected A {
protected:
	int a;
	int b;
不可访问：
	int c;
};

// 私有继承
class B : private A {
private:
	int a;
	int b;
不可访问:
	int c;
};

class BasePage {
public:
	void header() {
		cout << "Header" << endl;
	}

	void footer() {
		cout << "footer" << endl;
	}
};

class Java : public BasePage {
public:
	void content() {
		cout << "Java content" << endl;
	}
};

class CPP : public BasePage {
public:
	void content() {
		cout << "C++ content" << endl;
	}
};