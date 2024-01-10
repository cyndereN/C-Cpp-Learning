## 2. 构造/析构/赋值

### 2.1 Item05 Know what functions C++ silently writes and calls

1. C++会为类生成默认的关键函数

如果在C++的类中不声明任何成员，C++会自动为你生成默认的构造函数(constructor)，拷贝赋值运算符(copy assignment constructor，即 '=')，拷贝构造函数(copy constructor)以及析构函数(destructor)。

```cpp
class Empty {};             

//假定以下功能都会被调用，此定义等价于：
class Empty{
public:
    Empty(){....}                                //构造函数
    Empty(const Empty& empty){.....}             //拷贝构造函数
    ~Empty(){....}                               //析构函数
    Empty& operator=(const Empty& empty){....}   //拷贝赋值运算符
};
```

2. 但是这样的生成是有条件的

赋值运算符是为了将一个对象的成员数据拷贝进另一个对象中。对于赋值运算符，只有当代码合法而且有意义时，编译器才会自动生成。如下代码就不满足该条件：

```cpp
template<typename T>
class A{
public:
    A(std::string& _name, const T& value);
private:
    std::string& name;
    const T value;
};
```

对于如上的类，现在执行如下操作：

```cpp
std::string s1("hello");
std::string s2("hi");

A<int> a1(s1,3);
A<int> a2(s2,6);
a1=a2;
```

现在有问题了！C++规定引用是专一的，不允许引用被初始化后再指向另一个对象。而这样的操作就相当于：

```cpp
int a = 3;
int& b = a;
int c = 7;
int& d = c;
b=d;           //编译器在此当然会报错
```
因此给a1对象的成员name的再赋值会导致编译出错。同样，C++也不允许为常量再赋值，因此对成员value赋值也会编译出错。

解决方法：定义自己的赋值运算符！

此外，当基类有将赋值运算符声明为私有时，编译器也会拒绝为它的子类生成赋值运算符，因为在子类赋值过程中，它所包含的基类也应当被赋值。但是既然被声明为基类的私有成员，子类将不能调用。

### 2.2 Item06 Explicitly disallow the use of compiler-generated functions you do not want

解决方法：因为编译器为类自动生成的函数都是共有(public)的，我们就可以把这些函数声明为私有(private)，这样它的对象就无权调用。其次，只声明不定义，因为如果有定义，本类和友元函数(friend functions)还是可以调用它们。

```cpp
class House{
  public:
    ....
  private:
    House(const House&);               //只有声明，不要定义
    House& operator=(const House&);    //因为不会被用到，就不必再给参数想一个名字了
};
```
这样，当你在代码中试图拷贝对象，编译器就会报错。如果你不小心在该类的成员或者友元函数中调用了，因为找不到定义，链接器则会出错。但把所有报错提前到编译器不是更好吗？

更好的解决方案：上一章也讲到过，当一个父类将拷贝函数声明为私有时，编译器会拒绝为它的子类生成拷贝函数。因此我们可以专门使用一个父类，在其中声明拷贝操作为私有，并让我们的类继承自它。

```cpp
    class Uncopyable{
    protected:
        Uncopyable();
        ~Uncopyable();
    private:
        Uncopyable(const Uncopyable&);               //将拷贝函数转移至此
        Uncopyable& operator=(const Uncopyable&);
    };

    class House:public Uncopyable{...};              //公有继承
```

### 2.3 Item07 Declare destructors virtual in polymorphic base classes

```cpp
    class TimeKeeper{                              //计时器类，用来当做基类
    public:
        TimeKeeper();                              //这是构造函数
        ~TimeKeeper();                             //这是析构函数
    ......
    };

    class AtomicClock : public TimeKeeper{...};   //原子钟是一种计时器
    class WaterClock : public TimeKeeper{...};    //水钟也是一种计时器

    TimeKeeper* getTimeKeeper(){...}              //用来返回一个动态分配的基类对象
    TimeKeeper* ptk = getTimeKeeper();            
    .....                                         //使用这个指针操作它的子类
    delete ptk;                                   //使用完毕，释放资源
```

C++的new与delete可以说是非常的令人头疼，稍不注意就会内存泄漏(memory leak)。而且其实并不像课里教的一样，只要new与delete配对就没问题。上面的问题new与delete配对了，但依然会造成内存泄漏。

如上代码的问题在于，当你通过基类指针使用子类，使用完毕后却只从基类删除。同时这个基类的析构函数并不是虚函数(virtual)，也就是不允许子类有自己版本的析构函数，这样就只能删除子类中基类的部分，而子类衍生出来的变量和函数所占用的资源并没有被释放，这就造成了这个对象只被释放了一部分资源的现象，依然会导致内存泄漏。

解决方法: 给基类一个虚的析构函数，这样子类就允许拥有自己的析构函数，就能保证被占用的所有资源都会被释放。

```cpp
    class TimeKeeper{
    public:
        virtual ~TimeKeeper();
    ....
    };
```
一般来讲，我们使用基类都是为了实现多态，那么这些基类就需要虚的析构函数，比如我们的TimeKeeper类，就可以通过TimeKeeper的指针来操作例如AtomicClock这样的子类。

但并不是所有的基类都是被用来实现多态的，比如我们在上一章讲过的Uncopyable类，单纯只是为了实现某个功能，而不是希望通过它的指针来操作某个对象，那么就不需要将析构函数声明为虚函数。以及某些类就不是用来当做基类的，比如标准库的string类和STL容器类，也不需要将析构函数声明为虚函数。

## 2.4 Item08 Prevent exceptions from leaving destructors

```cpp
class Widget{
  public:
    ...
    ~Widget(){...}        //假设此析构函数可能会抛出异常
};

void doSomething(){
  std::vector<Widget> v;
}                         //在这一行调用了v的析构函数，资源被释放
```

当v被调用析构函数，它包含的所有Widget对象也都会被调用析构函数。又因为v是一个容器，如果在释放第一个元素时触发了异常，它也只能继续释放别的元素，否则会导致其它元素的资源泄露。如果在释放第二个元素的时候又触发了异常，那么程序同样会导致崩溃。

不仅仅是std::vector，所有STL容器的类甚至包括数组也都会像这样因为析构函数抛出异常而崩溃程序，所以在C++中，不要让析构函数抛出异常！

但是如果析构函数所使用的代码可能无法避免抛出异常呢？

1. 消化掉这个异常

    ```cpp
    DBConn::~DBConn(){
        try{ 
            db.close();
        }catch(...){
            //记录访问历史
        }
    }
    ```

2. 主动关闭程序

    ```cpp
    DBConn::~DBConn(){
        try{ 
            db.close();
        }catch(...){
            //记录访问历史
            std::abort();
        }
    }
    ```

3. 把可能抛出异常的代码移出析构函数

    ```cpp
    class DBConn{
    public:
        ...
        ~DBConn();
        void close();        //当要关闭连接时，手动调用此函数
    private:
        ...
        closed = true;       //显示连接是否被手动关闭
    };

    void DBConn::close(){    //当需要关闭连接，手动调用此函数
    db.close();
    closed = true;
    }

    DBConn::~DBcon(){
    if(!closed)            //析构函数虽然还是要留有备用，但不用每次都承担风险了
        try{
        db.close();
        }catch(...){
        //记录访问历史
        //消化异常或者主动关闭
        }
    }
    ```
    通过以上的做法，当关闭连接时，我们先手动调用close()方法，这样就算抛出了异常，我们也可以事先处理，然后再调用析构函数。当然析构函数还是要检查是否被手动关闭并留有备用方案。如果没有被手动关闭，析构函数还是需要在消化掉异常和终止程序中做出选择。

## 2.5 Item09 Never call virtual functions during construction or destruction

```cpp
//---父类

class Transaction{                              //股市交易的基类
  public:
    Transaction();
    virtual void logTransaction() const =0;     //该函数用来记录交易历史，是一个纯虚函数
    ....
};

Transaction::Transaction(){
  ...
  logTransaction();                             //在基类的构造函数中调用了这个纯虚函数
}

//---子类

class BuyTransaction : public Transaction{
  public:
    virtual void logTransaction() const;
  ...
};

class SellTransaction : public Transaction{
  public:
    virtual void logTransaction() const;
  ...
};

// 某处买进类对象b

BuyTransaction b;
```

"BuyTransaction"的构造函数。但因为在C++中，当子类开始构造时，它所包含的父类的部分要先完成构造，所以率先调用的构造函数是它的父类"Transaction"的构造函数。现在问题来了，因为父类的构造函数调用了一个纯虚函数，这就会导致即使你创建的是它的子类对象，这个虚函数也不会绑定到子类的版本上，而是使用的父类版本。

这就"有悖常理"了，虚函数不是会自动绑定到继承层级里对应的一个类吗？其实C++这样做是有一个很好的原因的。我们在Item04讲过，使用未初始化的数据可能会给程序带来风险。因为在创建一个子类对象时，它的父类部分会先被创建。当父类的构造函数刚刚调用完成时，我们只能保证父类部分的数据被初始化，而不能保证衍生部分的被初始化。如果现在让这个虚函数去对应子类的版本，就可能会因为使用未初始化的数据而导致程序运行时错误。

事实上，正是由于这个原因，当一个子类对象在完成它自己全部成员的构造之前，C++只会把它当成父类，除了虚函数还包括typeid，dynamic_cast等，都会把当前对象当做父类，用来规避使用未初始化数据可能带来的风险。

同样的原理，我们也不要让析构函数调用虚函数。我们在第7章讲过，析构函数的调用顺序是从子类到父类，与构造函数的调用顺序是相反的。当子类部分的成员数据被删除时，C++同样会把当前的对象认为是父类，如果这时调用了虚函数，也会导致错误版本的虚函数被调用。

实际上这样在构造函数或者析构函数里直接调用虚函数，在某些编译器中是会发出警告的。不过即使无视掉这些警告，因为调用的是一个纯虚函数，通常是不会有定义的，所以在之后的链接过程中，链接器也会报错。

就算logTransaction()函数是一个有定义的"普通的"虚函数，即没有"=0"关键字来修饰，程序虽然不会因为缺少定义而闪退，但却一样会在子类的构造过程中调用错误版本的虚函数。所以万全的解决方法就是，不管是纯虚的还是普通的，就不要在构造或者析构函数中调用虚函数。

但如果一定想要对象在初始化的时候完成某些任务呢？那我们就需要在父类Transaction中，把虚函数logTransaction去掉virtual关键字，变成普通的函数，然后在子类构造过程中，把某些信息传递到父类的构造函数中。

```cpp
class Transaction {
 public:
    explicit Transaction(const std::string& info);      //explicit关键字用来防止隐式转换
    void logTransaction(const std::string& info) const; //增加一个传递参数，就可以从子类获得信息了
    ...
};

Transaction::Transaction(const std::string& info){
  ...
  logTransaction(info);  
}
```
在子类对象中如下定义构造函数了，这样就能把子类的信息传递到父类中，让父类构造函数去完成子类构造函数想做的事：
```cpp
class BuyTransaction : public Transaction{
  public:
    BuyTransaction(...) : Transaction(createLog(...)) { ...}
    ...
  private:
    static std::string createLog(...);
};
```

这里createLog()就是一个辅助函数(helper function)，用来将某函数的一部分功能封装成另一个小函数，减少代码的复杂性，使代码更加可读。此外，因为这是一个子类的私有成员，父类构造函数被调用时不能保证它被初始化，所以使用static关键字可以避免意外使用了未初始化的成员数据。


## 2.6 Item10 Have assignment operator return a reference to *this

C++的赋值操作符(assignment operator)有一个有趣的用：链式赋值 (Chained assignment)
```cpp
int x, y, z;
x = y = z = 15;   

//以上代码会被编译器从最右边开始解析 (right-associative):

x = (y = (z = 15)));
//15先被赋值到z，z又被赋值到y，最后y被赋值到x
```

对于自定义的类，赋值操作符应遵循如下两点规则:
- 返回类型是一个当前类的引用
- 要返回*this给左边的变量