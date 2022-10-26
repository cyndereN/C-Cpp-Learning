// 可以输出自定义数据类型
class Person {
	friend ostream& operator<<(ostream& out, Person& p);

	// 利用成员函数重载左移运算符
	// p.operator<<(cout) 简化版本 p<<cout
	// 一般不会利用成员函数重载（因为无法实现cout在左侧）
private:
	int m_A;
	int m_B;

public:
	Person(int a, int b) {
		m_A = a;  m_B = b;
	}

};

// 只能利用全局函数重载左移运算符
ostream& operator<<(ostream& out, Person& p) {
	// out是cout的别名
	out << "m_A = " << p.m_A << " m_B = " << p.m_B;
	return out;
}