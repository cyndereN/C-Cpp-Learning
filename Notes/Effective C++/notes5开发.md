## 5 Implementations

### 5.1 Item26 Postpone variable definitions as long as possible

### 5.2 Item27 Minimizing casting

- static_cast
    
    static_cast是最常用最好理解的C++风格类型转换，其实就相当于C++风格的显式转换，例如把int转为double，把无类型(void)指针转换为有类型指针，继承层次中的转换，把non-const对象转为const，但是不可以把const对象转为non-const(这是const_cast的功能)，也不能转换两个完全不兼容的类型:

    ```cpp
    //double转为int:
    double d = 1.3;
    int a = (int)d; //C风格转换
    int b = static_cast<int> d; //C++风格转换

    //non-const转为const:
    int a = 3;
    const int b = (const int)a; //C风格转换
    const int c = static_cast<const int>(a); //C++风格转换
    ```

- dynamic_cast

    名字里带个"dynamic"，就说明它是动态的，发生在运行时，而上面静态的static_cast则发生在编译时。像动态绑定(dynamic binding)一样，dynamic_cast需要RTTI(runtime type identification)信息做出运行时类型检测，所以它是最吃性能的cast。功能上不同于static_cast的是，它只能用在继承层级中，而且只支持指向多态类型的指针或引用，即继承层次的子类或有虚函数的基类。

    ```cpp
    class Animal{
    public:
        virtual void doSomething(); //要作为多态基类
    };
    class Dog : public Animal{...}; //继承类
    ...
    Dog* dog = new Dog();
    Aminal* animal = new Animal();

    //向上转型，转为父类
    Animal* newAnimal = dynamic_cast<Animal*>(dog); //编译通过
    //↑但要注意如果基类没有虚函数，目标类型就不是多态类型，就不能通过编译

    //向下转型，转为子类
    Dog* newDog = dynamic_cast<Dog*>(animal); //编译通过，但是返回空指针
    ```

    dynamic_cast的一大用途就是检测当前指针指向的是父类还是子类。如果返回了空指针，当前指针就指向父类，如果返回了有效的指针，指向的就是子类

- const_cast

    用来抹除对象的常量性(constness)，即去掉const限定符，它是唯一能去掉变量限定符的cast，也可以用来去掉volatile限定符。不过既然一个变量被定义为了const，我们当然不希望改变它，因此这种cast最有用的地方体现在函数传值里：

    ```cpp
    //需要非常量参数
    void doSomething(int* n){
    ...
    }
    ...
    const int a = 22;
    doSomething(&a); //报错，不能把const int转为int
    doSomething(const_cast<int*>(&a)); //正确
    ```

- reinterpret_cast

    用来把指针转换为任何类型的指针。既然叫"reinterpret"，它的用途就是把相同的内存数据以不同的方式表示出来，因此不生成任何额外的CPU代码，常见于底层的应用。同时它也是一个十分危险的cast，再加上比较特殊的用途，所以比较少用


---

- 类型转换会带来更多的机器码，以及意外结果（如改变拷贝对象）
- 如果可以就要避免类型转换，尤其是在侧重性能代码中的dynamic_cast。如果有些设计需要类型转换，尽量用其它方案代替
- 如果类型转换是必要的，就把它隐藏在函数里。这样用户就只能调用接口而自己的代码里就不会出现类型转换
- 要多用C++风格的类型转换，少用C风格类型转换。它们更容易被发现，各自服务的功能也更具体

### 5.3 Item28 Avoid returning 'handles' to object internals

避免返回指向内部成员的"句柄"，包括指针，引用，迭代器。不返回"句柄"能增强封装性，让const函数真正const，也能减少"野句柄"。

### 5.4 Item29 Strive for exception-safe code

```cpp
struct PMImpl{ //PrettyMenuImplementation
  std::shared_ptr<Image> bgImage;
  int imgChange;
};

class PrettyMenu{
  ...
  private:
    Mutex mutex;
    std::shared_ptr<PMImpl> pImpl;
};

void PrettyMenu::changeBackground(std::istream& imgSrc){
  using std::swap;   //这句见第25章
  Lock ml(&mutex);   //使用第14章安全管理mutex的Lock类，上锁
  std::shared_ptr<PMImpl> pNew(new PMImpl(*pImpl)); //生成数据的临时拷贝
  pNew->bgImg.reset(new Image(imgSrc)); //在拷贝上执行操作，用std::shared_ptr::reset替换图片
  ++pNew->imgChange;
  swap(pImpl,pNew); //调换回去
}//解锁
```

- 异常安全的函数即使在抛出异常时也不会泄露资源，损坏数据结构。这种安全性有三种级别，基本保证，强保证和不抛出保证

- copy and swap是实现强保证的有效方法，但给所有的函数加上强保证显然也不是实际的选择

- 函数的异常安全性遵循木桶原理，函数的最强安全性取决于它所调用操作的最弱安全性

### 5.5 Item30 Understand the ins and outs of inlining

inline函数，即内联函数会在函数调用处展开代码，直接将函数体插入函数调用处，从而省去了函数调用的开销。但相应地，代价就是会导致函数无法被复用，从而导致代码膨胀，（过度的inlining）进而可能会导致额外的换页行为（paging），降低指令cache的命中率，反而降低了代码效率。

关于inline，还有如下几点需要注意：

- inline只是对编译器的申请
- inline和template并无必然联系
- 不适合（编译器拒绝）进行inline的函数类型
    - 复杂函数
    - 虚函数
    - 构造/析构函数
    - 通过函数指针调用的函数

### 5.6 Item31 Minimize compilation dependencies between files

C++并没有把将接口从实现中分离这件事做的很好。即（头文件中）类定义式中不仅包含了接口，而且可以有实现。

前向声明。

- Handle Class（pimpl 手法）

```cpp
// person.h
#include <string>	// std::string 定义
#include <memory>	// std::shared_ptr 定义

// 用 前置声明 替代 #include
class PersonImpl;	// Person实现类的前置声明
class Date;
class Address;

class Person {
public:
    // 接口 只声明，实现部分放到cpp中
    Person(const std::string& name, const Date& birthday, const Address& addr);
    std::string name() const;
    std::string birthDate() const;
    std::string address() const;
    ...
private:
    std::shared_ptr<PersonImpl> pImpl;	// 指针指向Person实现类
};

// person.cpp
#include "person.h"
#include "person_impl.h"
#include "date.h"
#include "address.h"

Person::Person(const std::string& name, const Date& birthday, const Address& addr)
    : pImpl(new PersonImpl(name, birthday, addr)) {}

std::string Person::name() const {
    return pImpl->name();
}

...
```

Person类的使用者（#include "person.h"）完全不用关心Person类接口及其实现类PersonImpl的实现细节（PersonImpl与Person有着完全相同的成员函数，两者接口完全相同），也不需要关心其他关联类Date和Address的实现细节。这些类的实现的任何修改也不需要使用者代码的重新编译，真正实现了接口与实现分离！像Person这样使用pimpl手法的类通常称为Handle class。

- Interface class

```cpp
// person.h
class Person {
public:
    virtual ~Person();
    virtual std::string name() const = 0;
    virtual std::string birthDate() const = 0;
    virtual std::string address() const = 0;
    static std::shared_ptr<Person> create(const std::string& name, 
                                          const Date& birthday, 
                                          const Address& addr);
};

// person.cpp
std::shared_ptr<Person> Person::create(const std::string& name, 
                                       const Date& birthday, 
                                       const Address& addr) {
    return std::shared_ptr<Person>(new RealPerson(name, birthday, addr));
}

Person::~Person() {}

// real_person.h
class RealPerson: public Person {
public:
    RealPerson(const std::string& name, const Date& birthday, 
               const Address& addr)
        : theName(name), theBirthDate(birthday), theAddress(addr) {}
    
    virtual ~RealPerson() {}
    std::string name() const;
    std::string birthDate() const;
    std::string address() const;
    
private:
    std::string theName;
    Date theBirthDate;
    Address theAddress;  
};

// 用户代码
std::string name;
Date dateOfBirth;
Address address;
...
std::shared_ptr<Person> pp(Person::create(name, dateOfBirth, address));
...
std::cout << pp->name() << " was born on " << pp->birthDate()
    << " and now lives at " << pp->address();
```