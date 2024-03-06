## 7 Templates and Generic Programming

### 7.1 Item41 Understand implicit interfaces and compile-time polymorphism

classes和templates都支持接口（interfaces）和多态（polymorphism）。

对于classes而言，接口是显式的，多态是通过virtual函数实现的运行期多态：

- 显式接口由函数签名式（函数名称、参数类型、返回类型）构成，在源码中是明确可见的；
- 运行期多态基于virtual函数实现，具体调用哪一个virtual函数的重写，将在运行期根据对象的动态类型决定；

对于Templates而言，接口时隐式的，多态则是通过template具现化和函数重载解析（function overloading resolution）实现的编译期多态：

- 隐式接口由有效表达式构成，模板类型不定，且考虑上运算符重载等特性，隐式接口的自由度很大；
- 编译期多态，在调用template函数是传入不同的类型T，会得到不同的函数，这被称为template具现化，发生在编译期；

### 7.2 Item42 Understanding the two meanings of typename

1. 从属名称（dependent names）：template内出现的名称, 相依于某个模板参数, 如T t;；

2. 嵌套从属名称（nested dependent names）：从属名称在嵌套在模板参数所代表的类内，如T::const_iterator ci;； 可能存在歧义

3. 嵌套从属类型名称（nested dependent type names）：嵌套从属名称指涉的为某类型； typename只能用来标识嵌套从属名称，而不能用于其他名称。使用范围除了函数内部，还可以用于函数入参。

```cpp
template <typename T>
void f(const T& container,				// 不允许使用typename
      typename T::iterator iter);		// 一定要使用typename
```

4. 非从属名称（non-dependent names）：template中不依赖于任何模板参数的名称，如int a;；

### 7.3 Item43 Know how to access names in templatized base classes

所谓模板化基类，即定义某模板类时，继承于另一模板类Base`<T>`，这个Base`<T>`就是模板化基类。

```cpp
class CompanyA {								// 公司A
public:
    ...
	void sendClearText(const std::string& msg);	// 发送明文消息
    void sendEncrypted(const std::string& msg);	// 发送加密消息
    ...
};
class CompanyB {								// 公司B
public:
    ...
	void sendClearText(const std::string& msg);	// 发送明文消息
    void sendEncrypted(const std::string& msg);	// 发送加密消息
    ...
};
...												// 其他公司
class MsgInfo { ... };							// 保存信息，用于产生发送消息

template <typename Company>						// 模板化基类
class MsgSender {
    ...											// 构造函数，析构函数等
	void sendClear(const MsgInfo& info) {
        std::string msg;
        ...										// 根据info生成消息
		Company c;
        c.sendClearText(msg);
    }
    void sendSecret(const MsgInfo& info) {
        ...										// 与上类似，但调用c.sendEncrypted
    }
};

template <typename Company>
class LoggingMsgSender: public MsgSender<Company> {
public:
    ...											// 构造函数，析构函数等
	void sendClearMsg(const MsgInfo& info) {
        ...										// 消息发送前的log
		sendClear(info);						// 编译报错！！！
        ...										// 消息发送后的log
    }
    ...
};
```

### 7.4 Item44 Factor parameter-independent code out of templates

```cpp
template <typename T, 			// 正方矩阵元素类型为T
			std::size_t n>		// 正方矩阵尺寸为n x n
class SquareMatrix {
public:
    ...
	void transpose();			// 支持转置操作
};
```

```cpp
SquareMatrix<double, 5> sm1;
...
sm1.transpose();

SquareMatrix<double, 10> sm2;
...
sm2.transpose();
```

模板类被具现化成两个类，同时其成员函数transpose也被具现化成两份，虽然这两份函数实现不完全相同，却也只有矩阵尺寸n的差异，还是存在代码重复。想要规避这无谓的代码膨胀，和非模板代码中的考虑类似，我要将与参数无关的代码抽离。

```cpp
template <typename T>
class SquareMatrixBase {
protected:
    SquareMatrixBase(std::size_t n, T* dataPtr) : n_(n), dataPtr_(dataPtr) {
    }
    void baseTranspose();
    void setDataPtr(T* dataPtr) {
        dataPtr_ = dataPtr;
    }
    void basePrint() {
        for (int i = 0; i < n_; ++i) {
            for (int j = 0; j < n_; ++j) {
                std::cout << dataPtr_[i * n_ + j] << ",";
            }
            std::cout << std::endl;
        }
    }

private:
    std::size_t n_;
    T* dataPtr_;
};

template <typename T>
void SquareMatrixBase<T>::baseTranspose() {
    std::cout << "do transpose: pData = " << dataPtr_ << " , size = " << n_ << std::endl;
    for (int i = 0; i < n_; ++i) {
        for (int j = 0; j < i; ++j) {
            std::swap(dataPtr_[i * n_ + j], dataPtr_[j * n_ + i]);
        }
    }
}

template <typename T, std::size_t n>
class SquareMatrix : private SquareMatrixBase<T> {
public:
    SquareMatrix() 
        : SquareMatrixBase<T>(n, nullptr), 
    	  pData_(std::shared_ptr<T>(new T[n * n])) {
        this->setDataPtr(pData_.get());
    }
    void transpose() {
        this->baseTranspose();
    }
    void setData(T* data) {
        memcpy(pData_.get(), data, n * n * sizeof(T));
    }
    void print() {
        this->basePrint();
    }

private:
    std::shared_ptr<T> pData_ = nullptr;
};

int main() {
    SquareMatrix<int, 3> sm1;
    int mat[3 * 3] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    sm1.setData(mat);
    sm1.print();
    sm1.transpose();
    sm1.print();

    return 0;
}
```

### 7.5 Item45 Use member function templates to accpet "all compatible types"

用户自定的智能指针类如不增加额外的配置是不支持这样的隐式转换的，因为同一个template类对基类和派生类的具现化本身并不带有继承关系。所谓额外的配置就是实现成员（构造）函数模板，接受所有兼容类型的泛化copy构造和泛化copy赋值（之所以使用函数模板，是因为继承体系未来有可能扩充，我们不可能对每一对继承关系都实现出一组构造函数）。

```cpp
#include <typeinfo>

class Top {};
class Middle : public Top {};
class Bottom : public Middle {};

template <typename T>
class SmartPtr {
public:
    explicit SmartPtr(T* rawPtr) : rawPtr_(rawPtr) {  	// 普通构造，以裸指针初始化
        std::cout << "constructor: " << typeid(rawPtr).name() << std::endl;
    }

    SmartPtr(const SmartPtr& sp) : rawPtr_(sp.get()) {  // 普通copy构造，简单演示，浅拷贝
        std::cout << "copy constructor: " << typeid(sp).name() << " to " << typeid(*this).name() << std::endl;
    }

    SmartPtr& operator=(const SmartPtr& sp) {  	// 普通copy赋值操作符，简单演示，浅拷贝
        std::cout << "copy assignment operator: " << typeid(sp).name() << " to " << typeid(*this).name() << std::endl;
        rawPtr_ = sp.get();
        return *this;
    }

    template <typename U>  						// 泛化copy构造，简单演示，浅拷贝
    SmartPtr(const SmartPtr<U>& other) : rawPtr_(other.get()) {
        std::cout << "generic copy constructor: " << typeid(other).name() << " to " << typeid(*this).name() << std::endl;
    }

    template <typename U>  						// 泛化赋值操作符，简单演示，浅拷贝
    SmartPtr& operator=(const SmartPtr<U>& other) {
        std::cout << "generic copy assignment operator: " << typeid(other).name() << " to " << typeid(*this).name() << std::endl;
        rawPtr_ = other.get();
        return *this;
    }

    T* get() const {
        return rawPtr_;
    }
    ~SmartPtr() {
    }

private:
    T* rawPtr_ = nullptr;
};

int main() {
    // 1. 
    // structor: class Middle * __ptr64
    // generic copy constructor: class SmartPtr<class Middle> to class SmartPtr<class Top>
    SmartPtr<Top> pt1 = SmartPtr<Middle>(new Middle); 
    
    // 2. 
    // structor: class Bottom * __ptr64
	// eric copy constructor: class SmartPtr<class Bottom> to class SmartPtr<class Top>
    SmartPtr<Top> pt2 = SmartPtr<Bottom>(new Bottom);
    
    // 3. 
    // generic copy constructor: class SmartPtr<class Top> to class SmartPtr<class Top const >
    SmartPtr<const Top> cpt3 = pt1;
    
    // 4. 
    // 编译不通过
    // SmartPtr<Middle> pt4 = SmartPtr<Top>(new Top); 
    
    // 5. 
    // constructor: class Top * __ptr64
    SmartPtr<Top> pt4(new Top);
    // copy constructor: class SmartPtr<class Top> to class SmartPtr<class Top>
    SmartPtr<Top> pt5(pt4);

    delete pt1.get();	// 浅拷贝未约定所有权是否转移，由外部管理释放
    delete pt2.get();
    delete pt5.get();

    return 0;
}
```


### 7.6 Item46 Define non-member functions inside templates when type conversion are desired

### 7.7 Item47 Use traits classes for information about types

C++ 中通常把 Traits 称为类型萃取技术，即：在 template 编程中，获取模板参数的类型信息，并在编译阶段针对不同的类型响应不同的处理。

https://no5-aaron-wu.github.io/2022/09/25/EffectiveC-6-ReadNote06/

总结一下，对traits class 的使用方法如下：
- 建立一组重载函数或重载函数模板（身份像劳工，doAdvance），将卷标结构对象作为一个参数用于区别不同的重载函数，并令每个函数的实现码与接受的卷标结构对象相适应；
- 建立一个控制函数或函数模板（身份像工头，advance），调用上述的”劳工函数“，并传递由traits获取的类型对象；

### 7.8 Item48 Beaware of TMP

TMP有两大优势：

- 可以完成非 TMP 的常规编程做不到的事情，比如代码生成，类型适配等；
- 可以将某些工作从运行期转移到编译期，可以将运行期的错误提前暴露在编译期，可以获得更小的可执行文件，更快地运行，更少地内存需求，缺点是明显增加编译时间。

TMP 已被证明是个“图灵完备”的机器，意思是它强大到可以计算任何事物。使用 TMP 可以声明变量、执行循环、编写及调用函数等。但是TMP实现上述功能的方式不同于常规的C++程序，在条款47中，我们利用了重载实现编译期的 if…else 条件分支，接下来将通过编译期计算阶乘的实现，展示TMP通过递归模板具现化来是实现循环逻辑：

```cpp
template <unsigned n>
struct Factorial {  // 递归的形式体现: f(n) = n * f(n -1)
    enum { value = n * Factorial<n - 1>::value };
};
template <>
struct Factorial<0> {  // 模板全特化: 实际是初始化 f(0) = 1
    enum { value = 1 };
};

int main() {
    std::cout << Factorial<5>::value << std::endl; 		// 5! = 120
    std::cout << Factorial<10>::value << std::endl;		// 10! = 3628800
}
```