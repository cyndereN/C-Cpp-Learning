# RTTI

## 前言

RTTI是”Runtime Type Information”的缩写，意思是运行时类型信息，它提供了运行时确定对象类型的方法。RTTI并不是什么新的东西，很早就有了这个技术，但是，在实际应用中使用的比较少而已。

## typeid函数

typeid的主要作用就是让用户知道当前的变量是什么类型的，比如以下代码：

```cpp

#include <iostream>
#include <typeinfo>
using namespace std;
 
int main()
{
     short s = 2;
     unsigned ui = 10;
     int i = 10;
     char ch = 'a';
     wchar_t wch = L'b';
     float f = 1.0f;
     double d = 2;
 
     cout<<typeid(s).name()<<endl; // short
     cout<<typeid(ui).name()<<endl; // unsigned int
     cout<<typeid(i).name()<<endl; // int
     cout<<typeid(ch).name()<<endl; // char
     cout<<typeid(wch).name()<<endl; // wchar_t
     cout<<typeid(f).name()<<endl; // float
     cout<<typeid(d).name()<<endl; // double
 
     return 0;
}
```

对于C++支持的内建类型，typeid能完全支持，我们通过调用typeid函数，我们就能知道变量的信息。对于我们自定义的结构体，类呢？

```cpp
#include <iostream>
#include <typeinfo>
using namespace std;
 
class A
{
public:
     void Print() { cout<<"This is class A."<<endl; }
};
 
class B : public A
{
public:
     void Print() { cout<<"This is class B."<<endl; }
};
 
struct C
{
     void Print() { cout<<"This is struct C."<<endl; }
};
 
int main()
{
     A *pA1 = new A();
     A a2;
 
     cout<<typeid(pA1).name()<<endl; // class A *
     cout<<typeid(a2).name()<<endl; // class A
 
     B *pB1 = new B();
     cout<<typeid(pB1).name()<<endl; // class B *
 
     C *pC1 = new C();
     C c2;
 
     cout<<typeid(pC1).name()<<endl; // struct C *
     cout<<typeid(c2).name()<<endl; // struct C
 
     return 0;
}
```

对于我们自定义的结构体和类，tpyeid都能支持。在上面的代码中，在调用完typeid之后，都会接着调用name()函数，可以看出typeid函数返回的是一个结构体或者类，然后，再调用这个返回的结构体或类的name成员函数；其实，typeid是一个返回类型为type_info类型的函数。那么，我们就有必要对这个type_info类进行总结一下，毕竟它实际上存放着类型信息。

## type_info

去掉那些该死的宏，在Visual Studio 2012中查看type_info类的定义如下：

```cpp
class type_info
{
public:
    virtual ~type_info();
    bool operator==(const type_info& _Rhs) const; // 用于比较两个对象的类型是否相等
    bool operator!=(const type_info& _Rhs) const; // 用于比较两个对象的类型是否不相等
    bool before(const type_info& _Rhs) const;
 
    // 返回对象的类型名字，这个函数用的很多
    const char* name(__type_info_node* __ptype_info_node = &__type_info_root_node) const;
    const char* raw_name() const;
private:
    void *_M_data;
    char _M_d_name[1];
    type_info(const type_info& _Rhs);
 type_info& operator=(const type_info& _Rhs);
    static const char * _Name_base(const type_info *,__type_info_node* __ptype_info_node);
    static void _Type_info_dtor(type_info *);
};
```

在type_info类中，复制构造函数和赋值运算符都是私有的，同时也没有默认的构造函数；所以，我们没有办法创建type_info类的变量，例如type_info A;这样是错误的。那么typeid函数是如何返回一个type_info类的对象的引用的呢？我在这里不进行讨论，思路就是类的友元函数。

## typeid函数的使用

1. 使用type_info类中的name()函数返回对象的类型名称

注意以下：

```cpp
#include <iostream>
#include <typeinfo>
using namespace std;
 
class A
{
public:
     void Print() { cout<<"This is class A."<<endl; }
};
 
class B : public A
{
public:
     void Print() { cout<<"This is class B."<<endl; }
};
 
int main()
{
     A *pA = new B(); // 将子类指针赋予父类之后，是不能够访问到子类自己的成员函数的：
     cout<<typeid(pA).name()<<endl; // class A *
     cout<<typeid(*pA).name()<<endl; // class A
     return 0;
}

```

使用了两次typeid，但是两次的参数是不一样的；输出结果也是不一样的；当我指定为pA时，由于pA是一个A类型的指针，所以输出就为class A *；当我指定*pA时，它表示的是pA所指向的对象的类型，所以输出的是class A；所以需要区分typeid(*pA)和typeid(pA)的区别，它们两个不是同一个东西；但是，这里又有问题了，明明pA实际指向的是B，为什么得到的却是class A呢？我们在看下一段代码：

```cpp
#include <iostream>
#include <typeinfo>
using namespace std;
 
class A
{
public:
     virtual void Print() { cout<<"This is class A."<<endl; }
};
 
class B : public A
{
public:
     void Print() { cout<<"This is class B."<<endl; }
};
 
int main()
{
     A *pA = new B();
     cout<<typeid(pA).name()<<endl; // class A *
     cout<<typeid(*pA).name()<<endl; // class B
     return 0;
}
```

好了，我将Print函数变成了虚函数，输出结果就不一样了，这说明什么？这就是RTTI在捣鬼了，当类中不存在虚函数时，typeid是编译时期的事情，也就是静态类型，就如上面的`cout<<typeid(*pA).name()<<endl;`输出class A一样；当类中存在虚函数时，typeid是运行时期的事情，也就是动态类型，就如上面的`cout<<typeid(*pA).name()<<endl;`输出class B一样，关于这一点，我们在实际编程中，经常会出错，一定要谨记。


2. 使用type_info类中重载的==和!=比较两个对象的类型是否相等

这个会经常用到，通常用于比较两个带有虚函数的类的对象是否相等，例如以下代码：

```cpp
#include <iostream>
#include <typeinfo>
using namespace std;
 
class A
{
public:
     virtual void Print() { cout<<"This is class A."<<endl; }
};
 
class B : public A
{
public:
     void Print() { cout<<"This is class B."<<endl; }
};
 
class C : public A
{
public:
     void Print() { cout<<"This is class C."<<endl; }
};
 
void Handle(A *a)
{
     if (typeid(*a) == typeid(A))
     {
          cout<<"I am a A truly."<<endl;
 }
     else if (typeid(*a) == typeid(B))
     {
          cout<<"I am a B truly."<<endl;
     }
     else if (typeid(*a) == typeid(C))
     {
          cout<<"I am a C truly."<<endl;
     }
     else
     {
          cout<<"I am alone."<<endl;
     }
}
 
int main()
{
     A *pA = new B();
     Handle(pA);
     delete pA;
     pA = new C();
     Handle(pA);
     return 0;
}
```

## dynamic_cast 内幕

```cpp
#include <iostream>
#include <typeinfo>
using namespace std;
 
class A
{
public:
     virtual void Print() { cout<<"This is class A."<<endl; }
};
 
class B
{
public:
     virtual void Print() { cout<<"This is class B."<<endl; }
};
class C : public A, public B
{
public:
     void Print() { cout<<"This is class C."<<endl; }
};
 
int main()
{
     A *pA = new C;
     //C *pC = pA; // Wrong
     C *pC = dynamic_cast<C *>(pA);
     if (pC != NULL)
     {
          pC->Print();
     }
     delete pA;
}
```
在上面代码中，如果我们直接将pA赋值给pC，这样编译器就会提示错误，而当我们加上了dynamic_cast之后，一切就ok了。那么dynamic_cast在后面干了什么呢?

dynamic_cast主要用于在多态的时候，它允许在运行时刻进行类型转换，从而使程序能够在一个类层次结构中安全地转换类型，把基类指针（引用）转换为派生类指针（引用）。当类中存在虚函数时，编译器就会在类的成员变量中添加一个指向虚函数表的vptr指针，每一个class所关联的type_info object也经由virtual table被指出来，通常这个type_info object放在表格的第一个slot。当我们进行dynamic_cast时，编译器会帮我们进行语法检查。如果指针的静态类型和目标类型相同，那么就什么事情都不做；否则，首先对指针进行调整，使得它指向vftable，并将其和调整之后的指针、调整的偏移量、静态类型以及目标类型传递给内部函数。其中最后一个参数指明转换的是指针还是引用。两者唯一的区别是，如果转换失败，前者返回NULL，后者抛出bad_cast异常。对于在typeid函数的使用中所示例的程序，我使用dynamic_cast进行更改，代码如下：

```cpp
#include <iostream>
#include <typeinfo>
using namespace std;
 
class A
{
public:
     virtual void Print() { cout<<"This is class A."<<endl; }
};
 
class B : public A
{
public:
     void Print() { cout<<"This is class B."<<endl; }
};
 
class C : public A
{
public:
     void Print() { cout<<"This is class C."<<endl; }
};
 
void Handle(A *a)
{
     if (dynamic_cast<B*>(a))
     {
          cout<<"I am a B truly."<<endl;
     }
     else if (dynamic_cast<C*>(a))
     {
          cout<<"I am a C truly."<<endl;
     }
     else
     {
          cout<<"I am alone."<<endl;
     }
}
 
int main()
{
     A *pA = new B();
     Handle(pA);
     delete pA;
     pA = new C();
     Handle(pA);
     return 0;
}
```

https://oldpan.me/archives/c-knowledge-base-pointer-dynamic-cast