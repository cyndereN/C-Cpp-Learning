// 静态成员变量	
// · 所有对象共享同一份数据
// · 在编译阶段分配内存 （全局区）
// · 类内声明，类外初始化

class Person {
	// public:
private:
	static int m_a;  // 有访问权限

public:
	static void func() {  // 有访问权限
		m_a = 0;
		cout << "static void func 调用" << endl;
	}
};

int Person::m_a = 100;

// 访问方式：对象，类名


// 静态成员函数
// 所有对象共享同一个函数
// 静态成员函数只能访问静态成员变量