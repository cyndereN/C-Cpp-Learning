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

## 2.7 Item11 Handle assignment to self in operator=

由Aliasing引起的自赋值问题
```cpp
class Base{...};
class Derived : public Base{...};               //同一个继承层级中

void doSomething(const Base& rb, Derived* pd);  //rb与pd就可能指向同一个对象

a[i] = a[j];       //如果i==j,那么这行代码也构成自赋值
*px = *py;         //如果px和py指向了同一个对象，这行代码也构成自赋值
```
如果你要手动管理资源而不使用资源管理类的话(resource managing class)，你的赋值操作符就可能不是自赋值安全的(self-assignment-safe):
```cpp
class Bitmap{...}
class Widget{
  ...
  private:
    Bitmap *bp;
};

Widget& Widget::operator=(const Widget& rhs){
  delete pb;
  pb = new Bitmap(*rhs.bp);
  return *this;
}
```

可能第一眼看着没什么问题，但如果传入的参数rhs是它本身呢？这就会导致delete语句把*this自己的资源释放掉，同时也释放掉了rhs的资源，最后返回的*this包含了一个损坏的数据，你不能访问不能修改，甚至不能通过delete来为其释放资源，等于说这段空间就凭空消失了，所以这段代码不是自赋值安全的。

1. 解决方法1：检查传入的参数是不是*this

```cpp
Widget& Widget::operator=(const Widget& rhs){

  if(this == &rhs)             //先做一个身份检测
    return *this;

  delete pb;                   //如果不是自己，再执行如下操作
  pb = new Bitmap(*this.pb);
  return *this;
}
```

这个解决方法照顾到了自赋值的情况，但仍然不是异常安全(exception-safe)的。试想如果执行过了delete语句，在执行下面的new语句时抛出了异常，例如内存不足，最后仍然会导致*this储存了一个损坏的数据。因此我们来看一个更好的解决方法:

2. 解决方法2：重新排列语句

```cpp
Widget& Widget::operator=(const Widget& rhs){
  Bitmap *pOrigin = pb;            //先保存一个原pb的备份
  pb = new Bitmap(*this.pb);       //拷贝过来rhs的pb
  delete pOrigin;                  //只删除备份
  return *this;
}
```
这条解决方法既对自赋值安全，对异常也是安全的。如果现在new的这行抛出了异常，指针pb也不会被提前删除。同时这样的语句排列省去了上一条解决方法身份检测的步骤，因为即使传入的rhs是*this本身，最后删除的也只是备份而不是*this自己的pb。

3. 解决方法3：先拷贝再调换(Copy and swap)

```cpp
class Widget{
   ...
  void swap(Widget& rhs);   //把rhs和*this的数据成员互相调换
  ...
};

Widget& widget::operator=(const Widget& rhs){
  Widget temp(rhs);       //拷贝rhs
  swap(temp);             //将*this的数据与这个拷贝的数据调换
  return *this;
}
```

利用解决方法2相似的思路，也是相当于生成一份拷贝，再把这份拷贝复制进*this中。还有另一种形式，巧妙利用了C++传值会自动生成一份本地拷贝的特性：

```cpp
Widget& Widget::operator=(Widget rhs){
    swap(rhs);
    return *this;
}
```

这样的代码虽然可能违反了函数要使用常量引用传递的惯例，但这样做确实能减少源代码和目标代码的长度，增加了效率。

## 2.8 Item12 Copy all parts of an object

```cpp
class PriorityCustomer : public Customer{
  public:
    ...
    PriorityCustomer(const PriorityCustomer& rhs);
    PriorityCustomer& operator=(const PriorityCustomer& rhs);
  private;
    int priority;
};

PriorityCustomer::PriorityCustomer(const PriorityCustomer& rhs)
  :priority(rhs.prority){           //使用初始化列表来构造该类的数据成员
  logCall("PriorityCustomer copy constructor");  
}

PriorityCustomer& PriorityCustomer::operator=(const PriorityCustomer& rhs){
  logCall("PriorityCustomer copy assignment operator");
  priority = rhs.priority;          //拷贝该类的数据成员
  return *this;
}
```

以上代码看起来像是拷贝了所有的数据成员，但是却忘记了它的基类部分！如果我们不传入基类对象作为子类构造函数的参数，当构造这个子类的时候，它的基类的默认构造函数将会被调用，结果就是，基类Customer的name等数据成员被设定为了默认值，那么全体VIP用户的数据就丢失了（人家充了钱反而号被你搞丢了）

我们再来看赋值操作符，赋值操作符同样没有把基类作为传进来的参数，因此当拷贝某对象时，它的基类部分也不会被拷贝进来，所以这样的代码同样会导致一个部分拷贝。

解决：
```cpp

PriorityCustomer::PriorityCustomer(const PriorityCustomer& rhs)
  : priority(rhs.prority), Customer(rhs){     //要把基类部分也添加进初始化列表
  logCall("PriorityCustomer copy constructor"); 
}

PriorityCustomer& PriorityCustomer::operator=(const PriorityCustomer& rhs){
  logCall("PriorityCustomer copy assignment operator");
  Customer::operator=(rhs);         //要使用基类的拷贝操作符
  priority = rhs.priority; 
  return *this;
}

```

可能大家也会发现，C++的这两种拷贝函数有相似的功能和代码，那么我们能不能避免代码重复，让其中一个拷贝函数调用另一个呢？答案是不能

使用拷贝赋值操作符调用拷贝构造函数，或者使用拷贝构造函数调用拷贝赋值操作符，都是没有意义的。拷贝赋值操作符适用于已经构造好的对象，而拷贝构造函数适用于还没有构造好的对象，所以这种做法在语义上是错误的。

如果我们真的想要节省代码，比如某个类有特别多的数据成员，我们可以写另一个函数用来给每个成员赋值，两个拷贝函数都可以调用，这个函数一般叫init()。