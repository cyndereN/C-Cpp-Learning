// 当子类继承的父类是一个类模板时，子类在声明时要指定出父类中T的类型
// 若不指定 编译器无法给子类分配内存
// 如果想灵活指定出父类T的类型，子类也需变成类模板

template<class T>
class Base {
	T m;
};
class Son :public Base<int> {

};
// classic Son:public Base // 错误
template<class T1, class T2>
class Son2 :public Base<T2> {
	T1 obj;
};

void test02() {
	
}


// 构造函数的类外实现

template<class T1, class T2>
class Person {
	Person(T1 name, T2 age);/*{
		m_Name = name;
		m_Age = age;
	}*/

public:
	T1 m_Name;
	T2 m_Age;
};

template<class T1, class T2>
Person<T1, T2>::Person(T1 name, T2 age) {
	this->m_Name = name;
	this->m_Age = age;
}