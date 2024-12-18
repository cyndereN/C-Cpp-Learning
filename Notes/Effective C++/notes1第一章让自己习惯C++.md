# Effective C++

## 0.导读

### 0.1 Terminology

**Declaration**: 告诉编译器某个东西的名称和类型，略去细节

```cpp
extern int x; // object declaration

std::size_t numDigits(int number); // function declaration

class Widget; // class declaration

template<typename T> // template declaration

class GraphNode; // (see Item 42 for info on the use of "typename")
```


size_t 仅仅是供 C++ 对某物计数时使用的某些 unsigned 类型的 typedef（例如，一个 char*-based string（基于 char* 的 string）中字符的个数，一个 STL container（容器）中元素的个数，等等）

```cpp
int i;//定义一个int类型的变量i
size_t size = sizeof(i);//用sizeof操作得到变量i的类型的大小
//这是一个size_t类型的值
//可以用来对一个size_t类型的变量做初始化
i = (int)size;//size_t类型的值可以转化为int类型的值
char c = 'a';//c保存了字符a，占一个字节
wchar_t wc = L'a';//wc保存了宽字符a，占两个字节
//注意'a'表示字符a，L'a'表示宽字符a
int arr[] = {1,2,3,4,5};//定义一个数组
int *p1 = &arr[0];//取得数组中元素的地址，赋值给指针
int *p2 = &arr[3];
ptrdiff_t diff = p2-p1;//指针的减法可以计算两个指针之间相隔的元素个数
//所得结果是一个ptrdiff_t类型
i = (int)diff;//ptrdiff_t类型的值可以转化为int类型的值
```

**Definition**: 为编译器提供在 declaration（声明）时被省略的细节。对于一个 function（函数）或一个 function template（函数模板），definition（定义）提供代码本体。对于一个 class（类）或一个 class template（类模板），definition（定义）列出了 members（成员）

```cpp

int x; // object definition

std::size_t numDigits(int number) // function definition.

{                               // (This function returns

	std::size_t digitsSoFar = 1; // the number of digits

	                            // in its parameter.)

	while ((number /= 10) != 0) ++digitsSoFar;

	return digitsSoFar;

}

class Widget
{ // class definition

public:

	Widget();

	~Widget();

	...

};

template<typename T> // template definition

class GraphNode
{

public:

	GraphNode();

	~GraphNode();

	...

};
```

**Initialization**: 给予对象初值的过程。对于 user-defined types（用户定义类型）的 objects（对象），initialization（初始化）通过 constructors（构造函数）完成。

```cpp
class A
{

public:

	A(); // default constructor

};

class B
{

public:

	explicit B(int x = 0, bool b = true); // default constructor; see below

}; // for info on "explicit"

class C
{

public:

	explicit C(int x); // not a default constructor

};
```

这里 classes B 和 C 的 constructors（构造函数）都被声明为 explicit（显式）。这是为了防止它们被用来执行 implicit type conversions（隐式类型转换），虽然他们还可以被用于 explicit type conversions（显示类型转换）：

```cpp
void doSomething(B bObject); // a function taking an object of type B

B bObj1; // an object of type B

doSomething(bObj1); // fine, passes a B to doSomething

B bObj2(28); // fine, creates a B from the int 28 (the bool defaults to true)

doSomething(28); // error! doSomething takes a B, not an int, and there is no implicit conversion from int to B

doSomething(B(28)); // fine, uses the B constructor to explicitly convert (i.e., cast) the int to a B for this call. (See Item 27 for info on casting.)
```

**copy**构造函数被用来“以同型对象初始化自我对象”

**copy assignment**操作符被用来“从另一个同型对象中拷贝其值到自我对象啊”

```cpp
class Widget
{

public:

	Widget(); // default constructor

	Widget(const Widget& rhs); // copy constructor

	Widget& operator=(const Widget& rhs); // copy assignment operator

	...

};

Widget w1; // invoke default constructor

Widget w2(w1); // invoke copy constructor

w1 = w2; // invoke copy assignment operator

Widget w3 = w2; // invoke copy constructor!
```

如果一个新的 object被定义（就象上面那行代码中的 w3），一个 constructor必须被调用；它不可能是一个 assignment。如果没有新的 object被定义（就象上面那行 "w1 = w2" 代码中），没有 constructor能被调用，所以它就是一个 assignment。

copy constructor是一个特别重要的函数，因为它定义一个 object如何 passed by value (往往是坏主意)。

```cpp
bool hasAcceptableQuality(Widget w);

...

Widget aWidget;

if (hasAcceptableQuality(aWidget)) ...
```

练习: 

Foo foo{10} 是 定义 和 初始化。

声明：只是规定了变量的类型和名字，而没有进行内存分配。
定义：不仅规定了变量的类型和名字，而且进行了内存分配，也可能会对量进行初始化。
初始化：在创建变量时赋予一个初始值。




## 1. 让自己更习惯C++

### 1.1 Item 01: 视C++为一个语言联邦

- C语言：C++的基础，区块、语句、预处理器、内置数据类型、数组和指针等特性都来自C；
- Object-Oriented C++：面向对象编程的特性，主要包括类、封装、继承、多态和virtual函数（动态绑定）等；
- Template C++：泛型编程（generic programing）的特性，带来了模板元编程（template metaprogramming，TMP）
- STL（Standard Template Library，标准模板库）：template程序库，其封装了容器（containers）、迭代器（iterators）、算法（algorithms）和函数对象（function objects）等


### 1.2 Item02：尽量以const，enum，inline替换 #define

1. 或者说，尽量多用编译器，少用预处理器 "Prefer the compiler to the preprocessor"

	尽量减少 preprocessor（预处理器）（特别是 #define）的使用，但还不能完全消除。#include 依然是基本要素，而 #ifdef/#ifndef 也继续扮演着重要的角色。现在还不是让 preprocessor（预处理器）完全退休的时间，但你应该给它漫长而频繁的假期。

	```cpp
	#define A 1.653   
	```
	在上面这个语句中，字符串'A'是不会被编译器看到的，而编译器看到的是'1.653'，这就会导致在调试过程中，编译器的错误信息只显示'1.653'而不是'A'，让你不知从何下手。

	解决方法：定义全局常量

2. 当定义或声明全局变量时，常数指针和类的常数需要另加考虑
	
	- 对于指针

		`const char* const myWord = "Hello";`  =>  `const std::string myWord("Hello");`

	
	- 对于类的常数

		声明为类的私有静态成员，这样既保证变量只能被这个类的对象接触到，又不会生成多个拷贝

		```cpp
		class Player{
		private:
			static const int NumTurns = 5;      // constant declaration
			int scores[NumTurns];               // use of constant
		}
		```

		因为此处是类的成员声明范围内，所以上面只是变量的声明和初始化，而并非定义，因此如果想获取变量的地址，需要在别处另加定义。这个定义不能有任何赋值语句，因为在类内已经规定为const:

		```const int Player::NumTurns;```

	- 枚举技巧(the enum hack)

		试想当你在一个类内声明某变量，但你的编译器不允许在声明时赋值初始化，同时接下来的某个语句却需要用到这个变量的具体数值，例如:

		```cpp
		int noPlayer;
		int scores[noPlayer];
		```

		此时编译器便会报错，需要在编译期间noPlayer有具体数值，这个时候就需要使用如下技巧:

		```cpp
		enum {noPlayer = 5};
		int scores[noPlayer];
		```

		这样编译器就能顺利通过，因为enum可以被当成int类型来使用

		但注意enum类型在内存中没有实体，无法取得enum类型的地址，因此这个方法更相当于取一个本地的#define数值

	- 对于#define的宏函数，尽量使用inline修饰的函数来代替#define

		```cpp
		#define CALL_MAX(a,b) f((a) > (b) ? (a) : (b))

		int a=5, b=0;
		CALL_MAX(++a, b);              //a增加了2次
		CALL_MAX(++a, b+10);           //a增加了1次 
		```

		解决方法：

		```cpp
		template<typename T>
		inline void callMax(const T& a, const T& b){
			f(a>b ? a:b);
		}
		```

### 1.3 Item03: Use const whenever possible

1. 指针常量、常量指针

2. 迭代器与const

	迭代器在功能上相当于指向某类型T的指针 T*。因此，如果想定义某迭代器指向一个常数，使用const iterator是不可以的，这样只相当于定义一个迭代器为一个常量(T* const)，例如:

	```cpp
	const std::vector<int>::iterator it = v.begin(); //注意，此声明只表示迭代器本身是常量        
	*it = 10;                                        //编译通过，迭代器是常量，但数据可以被修改
	++it;                                            //编译失败！因为const迭代器不允许被改变！
	```

	解决方法，使用const_iterator:

	```cpp
	std::vector<int>::const_iterator it = v.begin();  //使用了const_iterator类型
	*it = 10;                                         //编译失败，数据不允许被改变！
	++it;                                             //编译通过，迭代器本身可以被改变
	```

3. 尽量使用const可以帮助调试

	```cpp
	class Rational{....};
	Rational operator*(const Rational& lhs, const Rational& rhs){...}
	```

	在某处使用此乘法操作符时，误把比较操作符"=="打成了赋值操作符"="：

	```cpp
	Rational a,b,c;
	if(a*b = c){......}      
	```

	但编译器在此并不会报错，因为只有当a,b,c是C++自有类型(比如int)才会报错，对于用户自定义的类，编译器会认为此操作是将一个Rational赋值给另一个Rational

	这就会导致不正确的结果却没有任何编译器错误信息，给调试增加麻烦

	解决方法: 将该操作符定义为返回const，这样对其赋值将会是非法操作

	```cpp
	const Rational operator*(const Rational& lhs, const Rational& rhs){...}
	```

4. 类的成员函数与const

	用const修饰的对象只能调用const修饰的成员函数

	```cpp
	const char& operator[](size_t pos) const;
	char& operator[](size_t pos);

	Text t("Hello");
	const Text ct("Hello");

	std::cout<<t[0];            //调用了不加const修饰的索引操作符
	std::cout<<ct[0];           //调用了const版本, 但如果只有不加const的操作符，将会报错discard qualifier
	t[0] = 'x';                 //成立，但注意此索引操作符必须声明为引用才可以支持赋值操作
	ct[0] = 'x';                //错误！常量不能被修改

	```

5. 成员变量的常量性

	bitwise constness v.s. logical constness

	```cpp
	const Text ct("Hello");        //构造某常量对象
	char* pc = &ct[0];             //取其指针
	*pc = 'K';                     //通过指针修改常量对象，编译不会报错，结果为"Kello"
	```

	bitwise constness还有另一个局限性，例如:

	```cpp
	class Text{
	public:
		std::sizt_t length() const;
	private:
		char* pText;
		std::size_t length;
		bool lengthValid;
	....
	};

	std::size_t Text::length() const{
	if(!lengthValid){                      //做某些错误检测
		length = std::strlen(pText);         
		lengthValid = true;                   
	}

	return length;                         //这行才是代码核心
	}
	```

	在这段代码中，length()函数要做某些错误检测，因此可能会修改成员数据。即使真正的功能核心只是返回字符长度，编译器依然认为你可能会修改某些成员数据而报错。

	因此，更好的方法是逻辑常量性(Logical constness)，即允许某些数据被修改，只要这些改动不会反映在外，例如，以上问题可以用mutable关键字来解决:

	```cpp
	mutable std::size_t length;
	mutable bool lengthValid;
	```

	即使编译器使用数据常量性的标准，我们编程的时候应该采用逻辑常量性，对相关不可避免更改的成员数据加上mutable关键字来修饰。

6. 在定义常量与非常量成员函数时，避免代码重复

	既然两个版本的成员函数都要有，为什么又要避免重复?

	其实在这里指的是函数的实现要避免重复。试想某函数既要检查边界范围，又要记录读取历史，还要检查数据完整性，这样的代码复制一遍，既不显得美观，又增加了代码维护的难度和编译时间。因此，我们可以使用非常量的函数来调用常量函数。

	```cpp
	const char& operator[](std::size_t pos) const{
		....
		return text[position];
	};

	char& operator[](std::size_t pos){
	return
		const_cast<char&>(                              //const_cast去掉const关键字，并转换为char&
			static_cast<const Text&>(*this)[position];    //给当前变量加上const关键字，才可以调用const操作符
		);
	}
	```

### 1.4 Item04: Make sure objects are initialized before used

1. 自有类型(built-in type)的初始化

	C++的自有类型继承于C，因此不能保证此类型的变量在定义时被初始化。使用未初始化的数据可能会导致程序不正常运作，因此在定义变量的时候，需要对其进行初始化，例如将如下代码:

	```cpp
	int x;
	double d;

	// 改为:

	int x=0;
	double d;
	std::cin>>d;
	```

2. 类的初始化

	赋值 v.s. 初始化

	对于用户自定义的类，我们需要构造函数（constructor）来完成类的初始化，例如：

	```cpp
	class Coordinate{
	private:
		int x;
		double y;
		const std::list<double>& num;

	public:
		Coordinate(const int& _x, const int& _y, const std::list<double>& _num);
	};

	//以下构造函数为成员x, y, num赋值来完成对象的初始化
	Coordinate::Coordinate(const int& _x, const int& _y, const std::list<double>& _num){
		x = _x;
		y = _y;
		num = _num;
	}
	```

	此构造函数并没有真正完成“初始化”，只不过是做了“赋值”的操作。而C++规定，在进入构造函数之前，如果用户没有规定初始化过程，C++将自动调用各成员对应类型的默认构造函数。

	这样一来，此构造函数就相当于先调用了C++的默认构造函数，又做了一次赋值操作覆盖掉了先前的结果，造成了浪费。

	解决方法：使用初始化列表(initialization list)，C++就不必额外调用默认构造函数了

	```cpp
	Coordinate::Coordinate(const int& _x, const int& _y, const std::list<double>& _num):
	x(_x), y(_y), num(_num) {}
	```

	构造函数是可以被重载(overload)的，对于这个我们自己定义的类，还需要一个没有参数输入的默认构造函数，因此我们可以定义:
	
	```cpp
	Coordinate::Coordinate():x(0), y(0), num() {}
	//num()调用了std::list<double>类型的默认构造函数
	```

3. 某些初始化语法是必要的

	例如在定义引用(reference)和常量(const)时，不将其初始化会导致编译器报错

	```cpp
	const int a;                //报错，需要初始化！
	int& b;                     //报错，需要初始化！

	//现在对其进行初始化：

	const int a = 3;            //编译通过

	int c = 3;
	int& b = c;                 //编译通过！
	```

4. 数据初始化的顺序

	在继承关系中，基类(base class)总是先被初始化。

	在同一类中，成员数据的初始化顺序与其声明顺序是一致的，而不是初始化列表的顺序。因此，为了代码一致性，要保证初始化列表的顺序与成员数据声明的顺序是一样的。

	```cpp
	class myClass{
	private:
		int a;
		int b;
		int c;
	public:
		myClass(int _a, int _b, int _c);
	};

	//注意，即使初始化列表是c->b->a的顺序，真正的初始化顺序还是按照a->b->c
	myClass::myClass(int _a, int _b, int _c): c(_c), a(_a), b(_b) {}
	```

5. 初始化非本地静态对象

	还有一种特殊情况，尤其是在大型项目中比较普遍：在两个编译单元中，分别包含至少一个非本地静态对象，当这些对象发生互动时，它们的初始化顺序是不确定的，所以直接使用这些变量，就会给程序的运行带来风险。

	先简要解释一下概念，

	编译单元(translation unit): 可以让编译器生成代码的基本单元，一般一个源代码文件就是一个编译单元。

	非本地静态对象(non-local static object): 静态对象可以是在全局范围定义的变量，在名空间范围定义的变量，函数范围内定义为static的变量，类的范围内定义为static的变量，而除了函数中的静态对象是本地的，其他都是非本地的。

	此外注意，静态对象存在于程序的开始到结束，所以它不是基于堆(heap)或者栈(stack)的。初始化的静态对象存在于.data中，未初始化的则存在于.bss中。

	回到问题，现有以下服务器代码:

	```cpp
	class Server{...};     
	extern Server server;                 //在全局范围声明外部对象server，供外部使用
	```

	又有某客户端：
	```cpp
	class Client{...};
	Client::Client(...){
		number = server.number;
	}

	Client client;                       //在全局范围定义client对象，自动调用了Client类的构造函数
	```

	以上问题在于，定义对象client自动调用了Client类的构造函数，此时需要读取对象server的数据，但全局变量的不可控性让我们不能保证对象server在此时被读取时是初始化的。试想如果还有对象client1, client2等等不同的用户读写，我们不能保证当前server的数据是我们想要的。

	解决方法: 将全局变量变为本地静态变量

	使用一个函数，只用来定义一个本地静态变量并返回它的引用。因为C++规定在本地范围(函数范围)内定义某静态对象时，当此函数被调用，该静态变量一定会被初始化。

	```cpp
	class Server{...};

	Server& server(){                         //将直接的声明改为一个函数
		static Server server;
		return server;
	}
	```

	```cpp
	class Client{...};

	Client::client(){                        //客户端构造函数通过函数访问服务器数据
		number = server().number;
	}

	Client& client(){                        //同样将客户端的声明改为一个函数
		static Client client;
		return client;
	}
	```