// 成员函数加const后成这个函数为常函数
// 常函数内不可以修改成员属性
// 加了关键字mutable依然可以修改

// 2.常对象
// 声明对象前加const称该对象为常对象
// 常对象只能调用常函数
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