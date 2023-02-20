// 成员函数加const后成这个函数为常函数
// 常函数内不可以修改成员属性
// 加了关键字mutable依然可以修改


// 注意：const 关键字不能与 static 关键字同时使用，因为 static 关键字修饰静态成员函数，静态成员函数不含有 this 指针，即不能实例化，const 成员函数必须具体到某一实例。

// 2.常对象
// 声明对象前加const称该对象为常对象
// 常对象只能访问被const修饰的成员（包括const 成员变量和const 成员函数）
// 常对象可以修改静态变量的值

class Person {
public:
	void showPerson() const
	{
		m_A = 100; // !此时不可以修改了
		// this 指针的本质是指针常量 指针指向不可修改
		// 而加了const，变成const Person* const this 指向和指向的值都不能改
		this->m_B = 100;
	}

	void func() {

	}

	int m_A;
	mutable int m_B; // 特殊变量，即使在常函数中，也可修改
};


void test02() {
	const Person p;  // 常对象
	p.m_A = 100; // !错误，不能改
	p.m_B = 100; // 常对象下也可以修改

	p.func(); //!不允许
	p.showPerson(); // 允许，常对象只能调用常函数
}