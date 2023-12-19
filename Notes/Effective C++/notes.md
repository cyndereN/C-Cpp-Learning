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

- 或者说，尽量多用编译器，少用预处理器 "Prefer the compiler to the preprocessor"

	尽量减少 preprocessor（预处理器）（特别是 #define）的使用，但还不能完全消除。#include 依然是基本要素，而 #ifdef/#ifndef 也继续扮演着重要的角色。现在还不是让 preprocessor（预处理器）完全退休的时间，但你应该给它漫长而频繁的假期。

	```cpp
	#define A 1.653   
	```
	在上面这个语句中，字符串'A'是不会被编译器看到的，而编译器看到的是'1.653'，这就会导致在调试过程中，编译器的错误信息只显示'1.653'而不是'A'，让你不知从何下手。

	解决方法：定义全局常量

- 当定义或声明全局变量时，常数指针和类的常数需要另加考虑
	
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