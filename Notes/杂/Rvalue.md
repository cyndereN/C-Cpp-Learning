左值(left value，也被叫做locator value，可寻址的数据)
右值(right value，也被叫做read value, 用来读的数据)。

从字面意义上说，最简单的说来，左值就是有地址的数据，右值就是没有地址的数据。

以下是例子：

```cpp
int i = 1; //i是左值，1是右值
std::string str1 = "Hello"; //str1是左值，"Hello"是右值
```

那么什么是左值引用和右值引用呢？

一言以蔽之，我们平时用的引用，都是左值引用。举例：

```cpp
int a = 1;
int& b = a; //b是左值引用
```

右值引用是C++11引入的新特性，我们知道，在学习引用的时候，我们常说“引用”就是“别名”，既然是别名，那么也就是可寻址的。那么不可寻址（只读）的值才是右值，如何变成可寻址的右值引用呢？语法其实就是两个&，如下：

```cpp
void function1(int& v)
{
    std::cout<<"v = "<<v<<std::endl;    
}
//形参v必须是左值引用

void function2(int&& v)
{
    std::cout<<"v = "<<v<<std::endl;    
}
//形参v必须是右值引用


int main()
{
    int a =1;
    int& b = a;
    int&& c = 1;

    function1(b); //若传c进去则报错
    function2(c); //若传b进去则报错

    return 0;  
}

```

```cpp
int &&rr1 = 42; //正确：字面常量的右值
int &&rr2 = rr1; //错误：表达式rr1是左值
```

为了能避免此类错误，标准库引入std::move()

```cpp
int &&rr2 = std::move(rr1); //正确
```

那么什么是移动语义呢？其实就是std::move()的用法，一句话就可以概括：它能把一个任意值（包括左值、有值、左值引用），转换成右值引用。仅此而已。

我们来举一个例子，右值引用是如何帮我们“偷”资源的。

```cpp
class String
{
public:
String(const char* str)
{
    str_size = strlen(str);
    str_data = new char[str_size];
    memcpy(str_data, str, str_size);
}

String(const String& other):
{
    std::cout<<"Copied"<<std::end;
    str_size = other.str_size;
    str_data = new char[str_size];
    memcpy(str_data, other.str_data,str_size);    //这里可以被称作“深拷贝”
}

~String()
{
    delete str_data;
}
private:
    int str_size;
    char * str_data;
};

class Entity
{
public:
Enity(const String & name)
    :m_name(name){}
private:
    String m_name;
};

int main()
{
    Entity entity(String("My Name")); //这里会打印出"Copied"，尽管我们只想把“My Name”创建给entity对象，但却发生了一次复制。

    return 0;
}
```

如果我们想避免这次复制，直接把资源移动（或者说“偷”）给entity对象，则需要增加以下函数：

```cpp
class String
{
public:
    ....
    ....
String(String&& other) noexcept
{
    std::cout<<"Moved"<<std::endl;
    str_size = other.str_size;
    str_data = other.str_data;

    other.std_size = 0; //需要删掉“被偷”的对象的数据
    other.str_data = nullptr; //需要删掉“被偷”的对象的数据
    // 这里可以被称作“浅拷贝”
}
    ....
    ....
};

class Entity
{
    ....
    ....
Entity(String&& name)
    :m_name(std::move(name)){}
//这里尤其要注意，String&& name， name是右值引用，本质上是一个左值，所以需要std::move(name)转一下，才能进入到“偷资源”的函数里
//否则根据传入的形参类型，又调用到"Copied"函数了。
};

int main()
{
    Entity entity("My Name"); //这样修改就避免了复制
}
```

1. 我们有时看到有些函数接受const引用作为形参，这里是为了兼容左值和右值都可以被传入：
```cpp
String(const String& other)
{
    ....
}
```

2. 如果要实现“偷”/“移动”资源，类和使用该类里都需要增加对应的重载函数。

我们经常看到有些人用了move，但是却没有实现“移动”资源，是因为他们以为std::move()就是移动资源，其实不是的。std::move()只能把左值或者左值引用转换为右值引用，仅此而已。偷的动作需要对应类和使用该类里都需要写对应的重载函数。

我们之所以有些时候调用STL库的时候，用了std::move()可以实现“移动”/“偷”资源，是因为对应的STL容器和类里已经实现了对应的重载函数。比如：

```cpp
int main()
{
    std::string str3 = "Hello!";
    std::vector<std::string> str_list;
    str_list.push_back(std::move(str3));
    std::cout << "str3 is : " <<str3 << std::endl; //str3打印出来是空的,偷了str3的内容
    std::string&& str4 = "I'm rvalue reference";
    std::move(str4);
    std::cout << "str4 is : " << str4 << std::endl; //str4打印出来有值

    std::string str5 = "I'm lvalue reference";
    std::move(str5);
    std::cout << "str5 is : " << str5 << std::endl; //str5打印出来有值
}
```


3. 已经有指针了，为什么还要用引用?

引用其实就是通过指针实现的，引用可以看作一个常量指针(即指针自己是个常量，指向不能变)之所以有时要用引用，而不用指针，最主要的原因是为了重载运算符。指针之间的加减已经有了自己的含义，比如1个数组中的2个元素指针相减，得到的是中间相差元素的个数。如果我们想实现类似于两个字符串相加这样的操作，就无法直接用指针运算符（指针运算符已经有了自己的含义），只能通过重载引用之间的运算符实现。

引用是指针的一个语法糖，能用引用实现的功能基本上都能用引用实现。引用可以让代码更简洁，我们的使用原则是，如果可以用引用，那就用引用，不能用引用的地方才用指针。

另外就是一些小的区别了，比如指针可能为空(nullptr)，而引用不会；指针可以变，而引用不能。


---

另一个例子

```cpp
#include <string>
#include <vector>
#include <iostream>
#include <variant>
using namespace std;

class A {
public:
	int x;
	A(int x) : x(x)
	{
		cout << "Constructor" << endl;
	}
	A(A& a) : x(a.x)
	{
		cout << "Copy Constructor" << endl;
	}
	A& operator=(A& a)
	{
		x = a.x;
		cout << "Copy Assignment operator" << endl;
		return *this;
	}
	A(A&& a) : x(a.x)
	{
		//这里没有做a.x = 0;操作，不是很规范，具体看下一段代码
		cout << "Move Constructor" << endl;
	}
	A& operator=(A&& a)
	{
		x = a.x;
		cout << "Move Assignment operator" << endl;
		return *this;
	}
};

int main()
{
	A a(1);//调用构造
	A e(2);//调用构造
	e = A(a);//先调用拷贝构造 在调用移动赋值运算符 
	A d = move(e);//这等价于A d(move(e)); 调用Move Constructor 
	system("pause");
	return 0;
}

/*
Constructor
Constructor
Copy Constructor
Move Assignment operator
Move Constructor
*/
```

例子2
```cpp
#include <string>
#include <vector>
#include <iostream>
#include <variant>
using namespace std;

class A {
public:
	int x;
	A(int x) : x(x)
	{
		cout << "Constructor" << endl;
	}
	A(A& a) : x(a.x)
	{
		cout << "Copy Constructor" << endl;
	}
	A& operator=(A& a)
	{
		x = a.x;
		cout << "Copy Assignment operator" << endl;
		return *this;
	}
	A(A&& a) : x(a.x)
	{
		a.x = 0;
		cout << "Move Constructor" << endl;
	}
	A& operator=(A&& a)
	{
		x = a.x;
		cout << "Move Assignment operator" << endl;
		return *this;
	}
};

int main()
{
	A* a = new A(1);
	A* b = new A(1);
	A* c = new A(1);

	shared_ptr<A> p1(a);
	shared_ptr<A> p2(b);
	shared_ptr<A> p3(c);


	
	cout << "before move " << p1.get() << endl;
	A res1 = std::move(*p1);
	cout << "after move " << p1.get() << endl;

	// shared_ptr&& res2 = std::move(p2);执行后，res2本身是一个右值，当你赋值的时候，res2本身就是p2的别名。
	cout << "before move " << p2.get() << endl;
	shared_ptr<A>&& res2 = std::move(p2);
	cout << "after move " << p2.get() << endl;

    // shared_ptr res3= std::move(p3);执行后，res3以右值构造函数接收参数，所以stl根据右值规则，拿走了p3的值，并且制空p3. 这个置空 是因为这个智能指针类在右值构造函数自己实现了资源的转移操作 所以才置空的。
	cout << "before move " << p3.get() << endl;
	shared_ptr<A> res3= std::move(p3);
	cout << "after move " << p3.get() << endl;
	
	system("pause");
	return 0;

}

/*
Constructor
Constructor
Constructor
before move 009ED6B0
Move Constructor
after move 009ED6B0
before move 009ED7C8
after move 009ED7C8
before move 009ED7F8
after move 00000000

*/
```

例子3
```cpp
#include <iostream>
#include <string>
#include <cstring>
using namespace std;
 
class String
{
public:
	char* str;
	String() : str(new char[1])
	{
		str[0] = 0;
	}
 
	// 构造函数
	String(const char* s)
	{
		cout << "调用构造函数" << endl;
		int len = strlen(s) + 1;
		str = new char[len];
		strcpy_s(str, len, s);
	}
 
	// 复制构造函数
	String(const String & s)
	{
		cout << "调用复制构造函数" << endl;
		int len = strlen(s.str) + 1;
		str = new char[len];
		strcpy_s(str, len, s.str);
	}
 
	// 复制赋值运算符
	String & operator = (const String & s)
	{
		cout << "调用复制赋值运算符" << endl;
		if (str != s.str)
		{
			delete[] str;
			int len = strlen(s.str) + 1;
			str = new char[len];
			strcpy_s(str, len, s.str);
		}
		return *this;
	}
 
	// 移动构造函数
	// 和复制构造函数的区别在于，其参数是右值引用
	String(String && s) : str(s.str)
	{
		cout << "调用移动构造函数" << endl;
		s.str = new char[1];
		s.str[0] = 0;
	}
 
	// 移动赋值运算符
	// 和复制赋值运算符的区别在于，其参数是右值引用
	String & operator = (String && s)
	{
		cout << "调用移动赋值运算符" << endl;
		if (str != s.str)
		{
			// 在移动赋值运算符函数中没有执行深复制操作，
			// 而是直接将对象的 str 指向了参数 s 的成员变量 str 指向的地方，
			// 然后修改 s.str 让它指向别处，以免 s.str 原来指向的空间被释放两次。
			str = s.str;
			s.str = new char[1];
			s.str[0] = 0;
		}
		return *this;
	}
 
	// 析构函数
	~String()
	{
		delete[] str;
	}
};
 
template <class T>
void MoveSwap(T & a, T & b)
{
	T tmp = move(a);  //std::move(a) 为右值，这里会调用移动构造函数
	a = move(b);  //move(b) 为右值，因此这里会调用移动赋值运算符
	b = move(tmp);  //move(tmp) 为右值，因此这里会调用移动赋值运算符
}
 
template <class T>
void Swap(T & a, T & b) 
{
	T tmp = a;  //调用复制构造函数
	a = b;  //调用复制赋值运算符
	b = tmp;  //调用复制赋值运算符
}
 
int main()
{
	String s;
	// 如果没有定义移动赋值运算符，则会导致复制赋值运算符被调用，引发深复制操作。
	s = String("this");  //调用移动赋值运算符
	cout << "print " << s.str << endl;
	String s1 = "hello", s2 = "world";
	//MoveSwap(s1, s2);  //调用一次移动构造函数和两次移动赋值运算符
	Swap(s1, s2);//调用一次复制构造函数，两次复制赋值运算符
	cout << "print " << s2.str << endl;
 
	system("pause");
	return 0;
}

```