## 3. 资源管理

### 3.1 Item13 Use objects to manage resources

解决方法1:

我们可以利用C++的对象析构函数自动调用机制，把资源封装在对象里面，这样当对象完成了它的使用周期，资源就会保证被释放。使用标准库的模板智能指针auto_ptr，它的析构函数会自动调用delete来释放它所指向的对象，十分方便。

```cpp
void f(){
  std::auto_ptr<Investment> pInv(createInvestment());
  ...   //使用
}       //无需手动释放
```

1. 获得资源后要立即传递给资源管理对象用来初始化。在这里我们通过createInvestment()函数获得的资源被传递给了auto_ptr的构造函数。这就是C++重要的RAII概念，Resource Acquisition Is Initialisation，意为"资源获取即初始化"。
2. 资源管理类要利用析构函数来释放资源。当对象超出了它的作用域(scope)时，它的析构函数会自动调用，所以用析构函数来释放资源是保证安全的。但如第8章所讲，我们要防止在对象析构过程中抛出异常。


解决方法2：

使用引用计数的智能指针(Reference-Counting Smart Pointer, RCSP)，它在运行时会统计有多少对象指向当前的资源，然后当没有任何对象指向当前资源时便会自动释放。C++标准库所追加TR1的shared_ptr就是这种智能指针的一个栗子:
```cpp
void f(){
  std::tr1::shared_ptr<Investment> pInv(createInvestment());
  ...
}  //同样无需手动释放
```
代码看起来和上面是差不多的，但shared_ptr可以在STL容器中使用，成为一个更好的选择，因为shared_ptr没有auto_ptr自动把原对象设为NULL的拷贝特性，也因为当使用容器的算法功能生成本地拷贝时，此时有两个对象指向了这个资源。即使拷贝的析构函数被调用了，原有的对象依然在指向这个资源，该资源便不会被提前释放。

```cpp
std::tr1::shared_ptr<Investment> pInv1(createInvestment());
std::tr1::shared_ptr<investment> pInv2(pInv1);  //pInv1保持不变
pInv1 = pInv2;                                  //pInv2保持不变
```

使用智能指针只是用对象管理资源的方法之一，而且也存在着局限性。例如我们不能使用标准库的智能指针来指向一个动态分配的数组，因为析构函数调用的是delete而不是delete []，虽然这样做依然可以通过编译。

```cpp
std::auto_ptr<std::string> aps(new std::string[10]);
std::tr1::shared_ptr<int> spi(new int[10]);
//析构函数并不会调用delete []
```


### 3.2 Item14 Think carefully about copying behavior in resource-managing classes

```cpp
Lock ml1(&m);  //m在ml1的构造过程中被锁住
Lock ml2(ml1); //把ml1拷贝进ml2，会发生什么?
```

在创建自己的RAII资源管理类时，我们必须要思考需要如何规定这个类的拷贝行为。对于这个问题，我们有如下选择:

1. 禁止拷贝 (可以把拷贝函数声明为私有来禁止掉拷贝)

2. 给资源引用计数

```cpp
class Lock{
  public:
    explicit Lock(Mutex* pm)
    :mutexPtr(pm, unlock)    //将unlock函数绑定到删除器
    {lock(mutexPtr.get());}
    //这里其实不需要定义析构函数
  private:
    std::shared_ptr<Mutex> mutexPtr; //使用shared_ptr，不使用裸指针
};
```

3. 深拷贝封装的资源

4. 转移所有权

### 3.3 Item15 Provide access to raw resources in resource managing classes

具体使用隐式转换还是显式转换还是要根据不同的需要来决定，要保证代码的正确性，显式转换的get()函数可能是更好的选择，如果想要代码自然易懂，隐式转换可能更好，两者各有优缺点。

### 3.4 Item16 Use the same form in corresponding uses of new and delete

```cpp
typedef std::string AddressLines[4]; //定义AddressLines类型为
                                     //一个包含4个字符串的数组
                                     //所以需要对其使用delete[]
std::string *pal = new AddressLines; //相当于new string[4]
...
delete pal;   //错误
delete[] pal; //正确
```

### 3.5 Item17 Store newed objects in smart pointers in standalone statements

```cpp
std::shared_ptr<Widget> pw(new Widget); //放在单独的语句里
processWidget(pw,priority());  //这样就不会泄露资源了
```