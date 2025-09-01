# Trivial, standard-layout, POD, and literal types

https://learn.microsoft.com/en-us/cpp/cpp/trivial-standard-layout-and-pod-types?view=msvc-160

## 关于layout

The term layout refers to how the members of an object of class, struct or union type are arranged in memory. In some cases, the layout is well-defined by the language specification. But when a class or struct contains certain C++ language features such as virtual base classes, virtual functions, members with different access control, then the compiler is free to choose a layout. That layout may vary depending on what optimizations are being performed and in many cases the object might not even occupy a contiguous area of memory. For example, if a class has virtual functions, all the instances of that class might share a single virtual function table. Such types are very useful, but they also have limitations. Because the layout is undefined they cannot be passed to programs written in other languages, such as C, and because they might be non-contiguous they cannot be reliably copied with fast low-level functions such as memcopy, or serialized over a network.

To enable compilers as well as C++ programs and metaprograms to reason about the suitability of any given type for operations that depend on a particular memory layout, C++14 introduced three categories of simple classes and structs: trivial, standard-layout, and POD or Plain Old Data. The Standard Library has the function templates is_trivial<T>, is_standard_layout<T>, is_pod<T>(C++20开始废弃) and is_literal<T>(C++17废弃，C++20移除) that determine whether a given type belongs to a given category.

## Trivial Type

When a class or struct in C++ has compiler-provided or explicitly defaulted special member functions, then it is a trivial type. Trivial types have a trivial default constructor, trivial copy constructor, trivial copy assignment operator and trivial destructor.

那么如何判断一个函数是否为trivial函数呢，trivial函数需要满足以下几点：

- 函数是编译器自动生成的
- 只可以是六种类型的函数：default ctor、copy ctor、dtor、copy assignment operator、move ctor和move assignment operator
- 函数所在的类里没有虚函数或虚基类
- 如果函数所在类继承于一个基类，该基类相关的函数也必须是trivial函数
- 函数所在的类的类成员，也需要是trivial类

总结来说，如果一个类的上述四个函数都是编译器自动生成的，而且该类对应的基类和所有的成员都是trivial类型，且没有虚函数，则该类为trivial type。

```cpp
#include<type_traits>
struct Trivial
{
	int i;
private:
	int j;// 注意，i和j的access不同，所以类Trivial是Trivial类，但不是standard layout类
};

// The following examples show trivial types. In Trivial2, the presence of the Trivial2(int a, int b) constructor requires that you provide a default constructor. For the type to qualify as trivial, you must explicitly default that constructor.
struct Trivial2
{
	int i;
	Trivial2(int a, int b) : i(a), j(b) {}
	Trivial2() = default;
private:
	int j;   // Different access control
};

struct NotTrivial
{
	int a;
	NotTrivial() :a(0) {};// 自定义ctor会让编译器不再生成default ctor
};

struct NotTrivial2
{
	int a;
	virtual void Func() {}
};
int main()
{
	cout << std::is_trivial<Trivial>() << endl;		// print 1
	cout << std::is_trivial<Trivial2>() << endl;	// print 1
	cout << std::is_trivial<NotTrivial>() << endl;	// print 0
	cout << std::is_trivial<NotTrivial2>() << endl;	// print 0
}

```

trivial函数会影响以下方面(出自C++ Concurrency In Action(Second Edition) P361)：

1. 对于principle of three里的三个函数: 只有copy ctor、copy assignment operator和dtor都为trivial函数的类对应的对象，才可以用memcpy或memmove来进行对象的复制
2. 用于constexpr函数的Literal Types，需要有trivial copy ctor、trivial copy assignment operator和trivial dtor函数
3. 如果一个类，其default ctor、copy assignment operator、copy ctor和dtor都为trivial函数，则该class can be used in a union with a user-defined ctor and dtor
4. 如果一个类，定义了trivial copy assignment operator，则该类可以用于std::atomic<>从而提供a vlue of that type with atomic operations

## Standard Layout
如果一个类是Standard Layout类，那么该类的对象在内存上的分配是连续的。

standard layout类应该具有以下特点：

- 没有虚函数或者虚基类
- 所有的非static的data members都是相同的访问级别
- 所有的非static的data members都是standard layout类的对象
- 如果有基类，基类也是standard layout
- has no base classes of the same type as the first non-static data member.
- 满足以下两个条件之一：
（一）派生类没有非static成员，基类有，但又不可以同时继承于多个拥有non-static数据成员的基类
（二）如果继承于一个基类，则该基类不可有非static的data members

```cpp
struct SL
{
   // All members have same access:
   int i;
   int j;
   SL(int a, int b) : i(a), j(b) {} // User-defined constructor OK
};
```

当继承的基类也有非static数据成员时，该类不是standard layout类：
```cpp
struct Base
{
   int i;
   int j;
};

// Derived类不是standard layout类, std::is_standard_layout<<Derived> == false!
struct Derived : public Base
{
   int x;
   int y;
};

struct Base2
{
   void Foo() {}
};

// std::is_standard_layout<<Derived2> == true
struct Derived2 : public Base2
{
   int x;
   int y;
};

// Derived would also be standard-layout if Base had the data members and Derived had only member functions.
```

## POD types

When a class or struct is both trivial and standard-layout, it is a POD (Plain Old Data) type. The memory layout of POD types is therefore contiguous and each member has a higher address than the member that was declared before it, so that byte for byte copies and binary I/O can be performed on these types. Scalar types such as int are also POD types. POD types that are classes can have only POD types as non-static data members.

如果一个class或stuct，既是trivial类，也是standard layout类，那么该类是POD类。

POD类是老版的C语言对类型的形容，实际上，它可以分为两个部分，trivial和standard layout，所以新的C++版本把POD进行了进一步细分，在C++20开始，废弃了is_pod<T>对应的trait

```cpp
#include <type_traits>
#include <iostream>

using namespace std;

struct B
{
protected:
   virtual void Foo() {}
};

// Neither trivial nor standard-layout
struct A : B
{
   int a;
   int b;
   void Foo() override {} // Virtual function
};

// Trivial but not standard-layout
struct C
{
   int a;
private:
   int b;   // Different access control
};

// Standard-layout but not trivial
struct D
{
   int a;
   int b;
   D() {} //User-defined constructor
};

struct POD
{
   int a;
   int b;
};

int main()
{
   cout << boolalpha;
   cout << "A is trivial is " << is_trivial<A>() << endl; // false
   cout << "A is standard-layout is " << is_standard_layout<A>() << endl;  // false

   cout << "C is trivial is " << is_trivial<C>() << endl; // true
   cout << "C is standard-layout is " << is_standard_layout<C>() << endl;  // false

   cout << "D is trivial is " << is_trivial<D>() << endl;  // false
   cout << "D is standard-layout is " << is_standard_layout<D>() << endl; // true

   cout << "POD is trivial is " << is_trivial<POD>() << endl; // true
   cout << "POD is standard-layout is " << is_standard_layout<POD>() << endl; // true

   return 0;
}
```

## Literal types

A literal type is one whose layout can be determined at compile time. The following are the literal types:

- void
- scalar types, 比如int, double等
- references
- Arrays of void, scalar types or references
- A class that has a trivial destructor, and one or more constexpr constructors that are not move or copy constructors. Additionally, all its non-static data members and base classes must be literal types and not volatile.

## 判断一个类的对象是否可以用memcpy来复制

根据前面的介绍，应该是需要该类为standard layout类，而查阅资料后发现，其实只要is_trivially_copyable<T>::value返回true，即可，即使不满足standard layout，也可以使用memcpy，比如下面的类：

```cpp
struct T {
  int i;
private:
  int j;
};
```

也就是说，不用满足standard layout的类，也可以使用memcpy和memcopy，在C++ Concurrency In Action(Second Edition)里提到：

Objects with trivial copy constructors, trivial copy assignment operators, and trivial destructors can be copied with memcpy or memmove

至于std::is_standard_layout，则一般用于保证C++与其他语言（比如C语言）的内存分布一致。

std::is_standard_layou is useful for communicating with other languages (for creating language bindings to native C++ libraries e.g.), and that’s why a standard-layout class has the same memory layout of the equivalent C struct or union.