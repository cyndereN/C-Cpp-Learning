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