# Pimpl idiom

Offers a technique to "hide" the implementation from the client code - whenever that may be needed.

- Isolating the rebuild when class details change (they are hidden)
- Minimising required or conflicting header inclusions
- A general build time reduction
- Minimal export requirements (although abstract classes could be used for this purpose as well)
- Easier control over implementation detail that varies over multiple targets or platforms

```cpp
// my_class.h
class my_class
{
     //  ... all public and protected stuff goes here ...
private:
     class impl;             ///< 类内前向声明
    unique_ptr<impl> pimpl;  // opaque type here 智能指针
};
```

```cpp
// my_class.cpp
class my_class::impl     // defined privately here 内嵌类定义
{
     // ... all private data and functions: all of these
     //     can now change without recompiling callers ...
};
my_class::my_class(): pimpl (  new impl  )
{
     // ... set impl values ...
}
```

# 前向声明和#include头文件

ps: 前向声明可以在类内声明~


## 前向声明(forward declaration)概念

在程序中引入了类类型的B。在声明之后，定义之前，类B是一个不完全类型(incompete type)，即已知B是一个类型，但不知道包含哪些成员。不完全类型只能以有限方式使用，不能定义该类型的对象，不完全类型只能用于定义指向该类型的指针及引用，或者用于声明(而不是定义)使用该类型作为形参类型或返回类型的函数。

## 前向声明应用场景

当你需要定义两个类或者结构，例如A和B，而这两个类需要互相引用，这时候在定义A的时候，B还没有定义，那怎么引用它呢，这时候就需要前向声明(forward declaration)了，前向声明格式如下：class B; 当你在定义类A之前声明了B，那么就会在程序中引入了类类型的B，编译器知道你会在后面的某个地方定义类B，所以允许你在类A中引用类B。但是，在声明之后，定义之前，类B是一个不完全类型(incompete type)，即已知B是一个类型，但不知道这个类型的一些性质(比如包含哪些成员和操作)。

## 我们可以用它做些什么事情吗？

在C++中，如果要编写一个新类的头文件，一般是要#include一堆依赖的头文件，但利用前向声明和c++编译器的特性，可以减少这里的工作量。

因为C++编译器做的事情主要是：1.扫描符号；2.确定对象大小。

利用这个特性，当我们编写一个新类的头文件时，就可以用前向声明，减少大量的#include，减少编译的工作量。

例如：

1. B类用到A类，操作如下，就不需要加A.h了，减少编译工作量

2. 在声明成员函数的形参或者返回类型时，也可以用前向声明

    即使我们没有定义一个foo类，也可以用，因为成员函数不占类对象的大小，编译器可以确定对象大小，前向声明的作用在于告诉编译器这个一个在别的地方定义的类型。这样编译器就能生成正确的符号表了。

    ```cpp
    //Sample.h
    class foo;
    class Sample
    {
    private:
        foo foo_test(foo &);
    };
    ```

    常犯错误：

    ```cpp
    #ifndef RESOURCE_H
    #define RESOURCE_H
    class mybitmap;
    class resource
    {
    public:
        resource();
        ~resource();
    private:
        mybitmap* 
        m_pBitmap;
    };
    #endif

    resource::~resource()
    {
        if (NULL != m_pBitmap)
        {
            delete m_pBitmap;
        }
    }
    ```

    程序编译时，会有一个警告，deletion of pointer to incomplete type 'mybitmap'; no destructor called（没有实践）

    原因就在于#include和class的区别：class如上面所说，而#include是包括一个类的所有定义、成员和方法等信息。
    class A 声明仅仅告诉程序有这样一个类，你可以在这里声明类A的一个指针，但是此处并不能获得类A的具体信息，如果定义类A的一个指针是可以的，但定义一个类A的对象，则程序是错误的，因为不知道A的具体信息，故无法生成一个对象。原因是程序中用class声明的mybitmap类，在执行delete m_pBitmap时，因为它不知道mybitmap类的具体信息，所以无法调用它的析构函数，故内存并没有释放，造成内存泄漏。

## 关于不完全类型

- What you can do with an incomplete type:

    - Declare a member to be a pointer or a reference to the incomplete type:

        ```cpp
        class Foo {
            X *pt;
            X &pt;
        };
        ```

    - Declare functions or methods which accept/return incomplete types:

        ```cpp
        void f1(X);
        X    f2();  
        ```

    - Define functions or methods which accept/return pointers/references to the incomplete type (but without using its members):

        ```cpp
        void f3(X*, X&) {}
        X&   f4()       {}
        X*   f5()       {}
        ```
        
- What you cannot do with an incomplete type:
 
    - Use it as a base class
        ```cpp
        class Foo : X {} // compiler error!
        ```

    - Use it to declare a member:

        ```cpp
        class Foo {
            X m; // compiler error!
        };
        ```
    
    - Define functions or methods using this type:

        ```cpp
        void f1(X x) {} // compiler error!
        X    f2()    {} // compiler error!
        ```

    - Use its methods or fields, in fact trying to dereference a variable with incomplete type

        ```cpp
        class Foo {
            X *m;            
            void method()            
            {
                m->someMethod();      // compiler error!
                int i = m->someField; // compiler error!
            }
        };
        ```