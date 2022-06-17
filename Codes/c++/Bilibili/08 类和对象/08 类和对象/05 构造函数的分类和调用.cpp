// 两种分类：
// 按参数：有参无参
// 按类型：普通构造和拷贝构造


class Person {
public:

	Person() {
		cout << "Person 无参构造函数的调用" << endl;
	}

	Person(int a) {
		age = a;
		cout << "Person 有参构造函数的调用" << endl;
	}

	Person(const Person& p) {
		// 将传入的人身上所有的属性，拷贝到我身上
		age = p.age;
		cout << "Person 拷贝构造函数的调用" << endl;
	}
	// 拷贝构造函数的调用时机
	// · 使用一个已经创建完毕的对象来初始化一个新对象
	// · 值传递的方式给函数参数传值
	//  void test02(){ 
	//     Person p; 
	//     doWork1(p); 
	//  }
	//  void doWork1(Person p){ 
	//      // 在这里改动p不会影响外面的p
	//  }
	// · 以值方式返回局部对象
	// void test03(){ 
	//     Person p = doWork2();
	//	   cout << (int*)&p << endl; 
	//  }
	//  Person doWork2(){ 
	//      Person p1;
	// 	   cout << (int*)&p1 << endl; 
	// 	    return p1;
	//  }

	// 默认情况，c++编译器至少给一个类添加三个函数： 默认构造（无参），默认析构，默认拷贝构造
	// 如果用户定义有参构造，c++不再提供无参构造，但是会提供默认拷贝构造
	// 如果用户定义拷贝构造，c++不会再提供其他构造函数
};

// 2. 调用
void test01() {
	// 括号法
	Person p;   // 默认构造函数调用，不加()，如果加了编译器会认为是一个函数声明
	Person p2(10);  // 有参
	Person p3(p2); // 拷贝构造函数

	// 显示法
	Person p1;
	Person p2 = Person(10); // 有参构造  Person(10) 叫匿名对象(特点：当前行执行结束后，系统会立即回收掉）
	Person p3 = Person(p2); // 拷贝构造 不要利用拷贝构造函数初始化匿名对象

	// 隐式转换法
	Person p4 = 10; // 相当于写了Person p4 = Person(10) 有参构造
	Person p5 = p4; // 拷贝构造
}