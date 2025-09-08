# 全特化与偏特化

## 模板

模板定义：模板就是实现代码重用机制的一种工具，它可以实现类型参数化，即把类型定义为参数， 从而实现了真正的代码可重用性。模版可以分为两类，一个是函数模版，另外一个是类模版。

大白话：C++是一门强类型语言，编写一段通用的逻辑，可以把任意类型的变量传进去处理，通过把通用逻辑设计为模板，摆脱了类型的限制，极大地提升了代码的可重用性。

模板实例化：模板定义本身不参与编译，而是编译器根据模板的用户使用模板时提供的类型参数生成代码，再进 行编译。用户提供不同的类型参数，就会实例化出不同的代码。

## 类模板

C++中模板分为函数模板和类模板

- 函数模板：是一种抽象函数定义，它代表一类同构函数。

- 类模板：是一种更高层次的抽象的类定义。

```cpp
#include <iostream>

using namespace std;

template<class T>
class Compare
{
public:
 bool equal(T a,T b);
};

template<class T>
bool Compare<T>::equal(T a, T b)
{
 return a == b;
}

int main()
{
 Compare<int>C;
 C.equal(1,2);
 return 0;
}
```

## 特化

所谓特化，就是将泛型的东东搞得具体化一些，从字面上来解释，就是为已有的模板参数进行一些使其特殊化的指定，使得以前不受任何约束的模板参数，或受到特定的修饰（例如const或者摇身一变成为了指针之类的东东，甚至是经过别的模板类包装之后的模板类型）或完全被指定了下来。

### 类模板全特化

所谓模板全特化限定死模板实现的具体类型；

比如上述这个例子，我们比较int类型这种还可以，但是比较float这种类型就不行，这时候就需要进行模板特化；

```cpp
#include <iostream>

using namespace std;

template<class T>
class Compare
{
public:
 bool equal(T a,T b);
};

template<class T>
bool Compare<T>::equal(T a, T b)
{
 return a == b;
}

//模板全特化
template<>
class Compare<float>
{
public:
 bool equal(float a, float b);
};

bool  Compare<float>::equal(float a, float b)
{
 return std::abs(a - b) < 10e-3;
}

int main()
{
 Compare<int>C;
 cout<<C.equal(1,2)<<endl;
 Compare<float>C2;
 cout<<C2.equal(1.001,1.001)<<endl;
 return 0;
}
```

全特化的标志：template <>然后是完全和模板类型没有一点关系的类实现或者函数定义。

template <>然后是完全和模板类型没有一点关系的类实现或者函数定义，如果你要说，都完全确定下来了，那还搞什么模板呀，直接定义不就完事了？

但是很多时候，我们既需要一个模板能应对各种情形，又需要它对于某个特定的类型（比如bool）有着特别的处理，这种情形下特化就是需要的了。

### 类模板偏特化

偏特化就是模板中的模板参数没有被全部确定，需要编译器在编译时进行确定。偏特化是指提供另一份template定义式，而其本身仍为templatized，这是针对于template参数更进一步的条件限制所设计出来的一个特化版本。也就是如果这个模板有多个类型，那么只限定其中的一部分;

```cpp
#include <iostream>

using namespace std;

template<class T1,class T2>
class Test
{
public:
 Test(T1 a, T2 b):_a(a),_b(b)
 {
  cout << "模板化" << endl;
 }
private:
 T1 _a;
 T2 _b;
};

//模板全特化
template<>
class Test<int,int>
{
public:
 Test(int a, int b) :_a(a), _b(b)
 {
  cout << "模板全特化" << endl;
 }
private:
 int _a;
 int _b;
};

//模板偏特化
template<class T>
class Test<int,T>
{
public:
 Test(int a, T b) :_a(a), _b(b)
 {
  cout << "模板偏特化" << endl;
 }
private:
 int _a;
 T _b;
};



int main()
{
 Test<double, double> t1(1.01, 1.01);
 Test<int, int> t2(1, 1);
 Test<int, char*> t3(1, "111");
 return 0;
}
```

### 函数模板特化

先看个毁三观的demo

```cpp
// first template
template <typename A, typename B>
void f(A a, B b) {
    std::cout << "Normal version." << std::endl;
}

// second template (overload)
template <typename A>
void f(A a, int b) {
    std::cout << "Partial version." << std::endl;
}

template<>
void f<int, int>(int a, int b) {
	std::cout << "Full Special version." << std::endl;
}

int main()
{
	int a = 10;
	double b = 12;	
	f(a, b);
	f(a, a);
}
// result
// Normal version.
// Partial version.

```

上面的代码可以看到，函数在调用时候顺序是：

1. 有匹配的no-template函数就优先调用，没有再进行下一步
2. 先找合适的模板，在本demo中，合适的模板就是second template (理论上全特化更合适，但是目前不去找了)
3. 找到模板后，在模板的实例化函数中找一个最合适的
4. 如果该模板没有最合适的函数，那么就由编译器根据该模板自己实例化一个

所以：函数并不需要偏特化，因为只要重载一个模板就可以实现偏特化的效果。切记，C++函数没有偏特化，下面的写法会报错，简单说不允许特化的时候template后面<>还有值存在。

```cpp
template <typename A>
int compare<const char*>(A* left, const char* right)
{
    std::cout <<"in special template< >..." <<std::endl;

    return strcmp(left, right);
}
```

但是下面是可以的：

```cpp
// 全特化
template < >
int compare<const char*>(const char* left, const char* right)
{
    std::cout <<"in special template< >..." <<std::endl;

    return strcmp(left, right);
}
```

```cpp
// 全特化
template < >
int compare(const char* left, const char* right)
{
    std::cout <<"in special template< >..." <<std::endl;

    return strcmp(left, right);
}
```

```cpp
// 函数模板重载
template <typename A>
int compare(A left, const char* right)
{
    std::cout <<"in partial template< >..." <<std::endl;

    return strcmp(left, right);
}
```

我们可以用到enable_if (函数模板重载 + SFINAE)

```cpp
#include <iostream>
#include <type_traits>

template<typename T1, typename T2>
typename std::enable_if_t<std::is_same_v<T2, int>>
show(T1 a, T2 b)
{
    std::cout << "Partial T2 = int" << std::endl; 
}

template<typename T1, typename T2>
typename std::enable_if_t<std::is_same_v<T2, float>>
show(T1 a, T2 b)
{
    std::cout << "Partial T2 = float" << std::endl; 
}

int main()
{
	int a = 10;
	float b = 12;	
	show<int, float>(a, b);
	show<int, int>(a, b);
	show<int, float>(a, a);
	show<int>(a, a);
	
}
// result
// partial T2 = float
// partial T2 = int
// partial T2 = float
// partial T2 = int

```

## 例子

```cpp
// specialize for any template class type
template <class T1> 
struct SpecializedType
{
    T1 x1;
    T1 x2;
};
template <class T>
class Compare<SpecializedType<T> >
{
public:
    static bool IsEqual(const SpecializedType<T>& lh, const SpecializedType<T>& rh)
    {
        return Compare<T>::IsEqual(lh.x1 + lh.x2, rh.x1 + rh.x2);
    }
};
```

```cpp
// int
int i1 = 10;
int i2 = 10;
bool r1 = Compare<int>::IsEqual(i1, i2);

// float
float f1 = 10;
float f2 = 10;
bool r2 = Compare<float>::IsEqual(f1, f2);

// double
double d1 = 10;
double d2 = 10;
bool r3 = Compare<double>::IsEqual(d1, d2);

// pointer
int* p1 = &i1;
int* p2 = &i2;
bool r4 = Compare<int*>::IsEqual(p1, p2);

// vector<T>
vector<int> v1;
v1.push_back(1);
v1.push_back(2);

vector<int> v2;
v2.push_back(1);
v2.push_back(2);
bool r5 = Compare<vector<int> >::IsEqual(v1, v2);

// custom template class 
SpecializedType<float> s1 = {10.1f,10.2f};
SpecializedType<float> s2 = {10.3f,10.0f};
bool r6 = Compare<SpecializedType<float> >::IsEqual(s1, s2);
```



## 总结

1. 函数模板只有特化，没有偏特化；

2. 模板、模板的特化和模板的偏特化都存在的情况下，编译器在编译阶段进行匹配，优先特殊的；

3. 模板函数不能是虚函数；因为每个包含虚函数的类具有一个virtual table,包含该类的所有虚函数的地址，因此vtable的大小是确定的。模板只有被使用时才会被实例化，将其声明为虚函数会使vtable的大小不确定。所以，成员函数模板不能为虚函数。