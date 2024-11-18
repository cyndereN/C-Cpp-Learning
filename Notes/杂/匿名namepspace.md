# 匿名 namespace

## 命名空间的概念

命名空间是C++中用于避免命名冲突的一种机制。它可以将代码中的函数、变量、类型等分组，并为它们指定一个命名空间名称。这样做的好处是可以避免不同的代码模块之间的名称冲突。

不同cpp文件间定义和使用namespace:

在文件1中定义的变量和函数是可以在另一个文件2中被使用的，关键是如何在文件2中声明。规范的方法应该是同时写一个test1.hpp，即头文件，在头文件中写入命名空间以及命名空间内的函数声明，在.cpp文件中写函数的实现，然后在调用该函数的源文件中包含该头文件。

```cpp
#ifndef TEST1_H
#define TEST1_H

namespace test1
{
	void func_1();
};

#endif

```

```cpp
#include"test1.hpp"
#include<iostream>

void test1::func_1()
{
	std::cout<<"this is test1 func1"<<std::endl;
}

```

```cpp
#include"test1.hpp"

using namespace test1;

int main(int argc,char**argv)
{
	func_1();
	return 0;
}

```

```shell
g++ test2.cpp test1.cpp 
```

## static

项目使用static封装一个symbol(variable或function)，只在文件内部（严格来说是编译单元内部，也就是经 过预处理之后得到的源文件）可用；编译单元之外，static varible变量不可见。如果编译时遇到了两个不同编译单元中有，1. 具有相同命名的，2. 且均为编译单元外可见的变量，则会有链接错误。

```cpp
// var.cpp
// 编译 gcc -c var.cpp 
// 查看symbol nm var.o
// 0000000000000000 d _ZL10var
// 编译单元之外不可见
static int var;
```

```cpp
// var.cpp
// 编译 gcc -c var.cpp 
// 查看symbol nm var.o
// 0000000000000000 D var
// 编译单元之外可见
int var;
```

## 默认namespace

默认命名空间也叫全局命名空间，所有没有置于某一具体命名空间下的代码即在默认命名空间下


## 匿名namespace

在C++中有一种推荐的等效static做法——匿名的名字空间。
匿名namespace是一种特殊的命名空间，它没有名称，只是使用关键字namespace进行定义。在匿名namespace中定义的函数、变量等的作用域仅限于当前文件中，其他文件无法访问。

```cpp
namespace
{
    int my_variable = 0;
    
    void my_function()
    {
        // code goes here
    }
}

int main()
{
    my_function();
    my_variable = 1;
    return 0;
}

```

## 优势

1. static的这个关键词的用途过多，比如你还可以用它声明静态成员，用它声明函数内 部的静态变量。

2. static没有办法修饰一个类型，所以下面的代码不合法

```cpp
static struct Widget {}; // 不合法
```

但是匿名命名空间可以：

```cpp
namespace {
struct Widget {};   // 合法
}   // namespace
```

3. 某些模板的参数必须具有外部链接熟悉，比如下面的代码是不合法的

```cpp
template <typename T, const int& N>
struct Array {
    T data[N];
};

static const int kMaxSize = 10;

Array<int, kMaxSize> data;   // 不合法，报错说 kMaxSize 没有外部的链接属性
```

## 本质区别

static：

C和C++中每一个源文件（.c, .cpp）都可以单独编译成一个目标文件(.o)，之后通过链 接器把这些目标文件链接起来，形成最后的可执行文件或者库文件。也就是说某个源文件 a.cpp中用到的符号s（函数，全局变量等）可能是在另一个源文件b.cpp中定义的，在 a.cpp中只要给出相应的声明就可以了。为了让链接器可以找到符号s的定义，b.o 必须提供它定义的所有可链接的符号。b.o只会提供具有外部链接熟悉的符号给链接器使用，如果一个符号在声明中加了static 关键字，那么它的链接属性变成了内部链接，也就不会暴露给链接器进行链接，这样一来它也就只能被文件内部看见了。

匿名名字空间：

匿名名字空间并不是真的没有名字，只不过这个名字只有编译器知道而已。

```cpp
namespace some_unique_name_compiler_generated {}    // 编译器生成一个唯一的名字
using namespace some_unique_name_compiler_generated;

namespace some_unique_name_compiler_generated {
    struct Widget {};
}
```

所以实际上 Widget 类完整的修饰应该是：
```cpp
some_unique_name_compiler_generated::Widget;

```
因为它没有 static 的修饰，所以它具有外部连接，但是因为命名空间的名字是编译器生成的，外部无从知晓，所以Widget这个符号只有编译单元的内部才能看见。

从实现的结果上来讲上static和匿名namespace造成的结果，都给声明的变量赋予了编译单元外不可见的属性，相对而言，一个具名的namespace是有external linkage属性的。从具体实现来讲，有的blog说匿名的namespace和static都是internal linakge，有的是说匿名的namespace是external linkage，只是用了变名称的方式(这和重载的原理是类似的)，根据我的实验，具体与C++的版本有关