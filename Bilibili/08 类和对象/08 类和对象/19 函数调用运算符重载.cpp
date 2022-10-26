// 函数调用运算符()也可以重载
// 重载后使用方式非常像函数的调用，因此称为仿函数
// 仿函数没有固定写法，非常灵活

class MyPrint {
public:
	void operator()(string test) {
		cout << test << endl;
	}
};

void test01() {
	MyPrint mp;
	mp("Hello World");
}

class MyAdd {
public:

	int operator()(int num1, int num2) {
		return num1 + num2;
	}
};

void test02() {
	MyAdd ma;
	int ret = ma(100, 100);
	cout << "ret = " << ret << endl;

	// 匿名函数对象
	cout << MyAdd()(100, 100) << endl;
}