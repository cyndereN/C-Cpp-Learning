## 6 Inheritance and OOD

### 6.1 Item32 Make sure public inheritance models "is-a"


设计模式五大原则（SOLID）：

- Single Responsibility Principle：单一职责原则

- Open Closed Principle：开闭原则

- Liskov Substitution Principle：里氏替换原则

- Interface Segregation Principle：接口隔离原则

- Dependence Inversion Principle：依赖倒置原则

场景1：不是所有bird都fly

场景2：数学概念中我们认为正方形是一种矩形，所以想当然地在C++代码中做如下继承设计class Square: public Rectangle，但实际上适用于矩形的属性修改规则，并不适用于正方形。所以这种public继承关系并不正确。比如：

```cpp
class Rectangle {
public:
	virtual void setHeight(int newHeight);
    virtual void setWidth(int newWidth);			// 可以单独设置长和宽
    virtual int height() const;
    virtual int width() const;
	...
};
class Square: public Rectangle {
    virtual void setHeight(int newHeight) override;
    virtual void setWidth(int newWidth) override;	// 长和宽要同时变
};

void makeBigger(Rectangle& r) {
    int oldHeight = r.height();
    r.setWidth(r.width() + 10);
    assert(r.height() == oldHeight);				// 对矩形成立，但对正方形不成立
}
```

*Note: 不同于public继承是表示子类与基类之间的’is-a’关系，private并不象征着类之间的’is-a’关系。

private继承意味着“子类根据基类的实现而得到”。(implemented-in-terms-of,根据基类实现出子类)

由于private继承将基类的所有public都改为private，因此，可以将private继承视为继承子类的实现而略去子类的接口(因为子类的接口由于private的原因不能再被调用者调用，相当于接口被取消),接口指一个class内的public方法。

由于private就是将一个类(基类)作为另一个类(子类)的一部分实现内容，即用基类来实现子类，它与对象之间的复合/包含关系很像，因此需要明确它们的异同点并考虑替代。
复合/聚合关系：即一个类包含另一个类，如在class Foo中定义一个成员，其类型是另一个类，这两个类之间就是复合关系。

使用private继承来代替复合的情况

- 存在protected成员的时候，使用private继承和使用复合的结果是不同的：复合后一个类仍然不能使用另一个类的protected成员；而private继承可以。
- 存在virtual成员的时候：复合与private继承的结果也不同。

**尽量使用复合而必要的时候才使用private继承。**

### 6.2 Item33 Avoid hiding inherited names

- 使用using声明式可以让Derived忽略名称遮掩，看到Base作用域内的函数。
```cpp
... 							// 基类不变

class Derived: public Base {
    using Base::mf1;
    using Base::mf3;
    virtual void mf1();			// 纯虚函数重写
    void mf3();					// 
};

// 用户代码
Derived d;
int x;
double y;
...
d.mf1();		// 没问题，调用Derived::mf1
d.mf1(x);		// 现在没问题，调用Base::mf1
d.mf2();		// 没问题，调用Base::mf2
d.mf3();		// 没问题，调用Derived::mf3
d.mf3(y);		// 现在没问题，调用Base::mf3
```

- 转发函数(forwarding function)

在private继承中，强调继承实现而不是继承接口。因此，有时候我们只希望继承一部分函数实现，而不是所有函数。此时可以用转发函数实现。

```cpp

class Base {
public:
    virtual void mf1() = 0;
    virtual void mf1(int) = 0;

    ... 							// 基类不变
}


class Derived: private Base {	// 注意是private继承
    virtual void mf1() {		// 转发函数
        Base::mf1();			// 调用基类的实现，暗自改为inline
    }			
    ...
};

// 用户代码
Derived d;
int x;
...
d.mf1();		// 没问题，调用Derived::mf1
d.mf1(x);		// 编译错误，Base::mf1被Derived::mf1遮掩
```

### 6.3 Item34 Differentiate between inheritance of interface and inheritance of implementation

public继承下，成员函数继承由两部分组成：函数接口继承和函数实现继承。我们在设计类时，一定要清楚我们希望的，到底是继承接口还是继承实现，还是两个都要。那么有以下几点规则可供参考：

- 对于public继承，成员函数（无论是非虚函数，虚函数还是纯虚函数）的接口总是会被继承。

- 声明纯虚函数的目的是为了让派生类只继承函数接口。

- 派生类可以同时继承基类的（非纯）虚函数的接口和缺省实现。


    ```cpp
    class Airport { ... };		// 机场类
    class Airplane {
    public:
        virtual void fly(const Airport& destination);
        ...
    };

    void Airplane::fly(const Airport& destination) {
        ...						// 缺省实现
    }

    class ModelA: public Airplane { ... };	// A类飞机	
    class ModelB: public Airplane { ... };	// B类飞机 都可以使用缺省的fly方法
    class ModelC: public Airplane { ... };	// C类飞机 也未重写fly 但飞行方式不同 有问题！！ 
    ```

    1. 将fly函数改为纯虚函数，只提供飞行接口。飞行的缺省实现也会在Airplane中提供，但放在一个独立的非虚的defaultFly函数中。若派生类希望使用缺省实现，则可在Fly函数的重写中调用defaultFly，若不想，则可自定义Fly函数。

    ```cpp
    class Airport { ... };		// 机场类
    class Airplane {
    public:
        virtual void fly(const Airport& destination) = 0;
        ...
    protected:					// 与private相比，可以被派生类继承
        void defaultFly(const Airport& destination);	// 
    };

    void defaultFly(const Airport& destination) {
        ...						// 缺省实现
    }

    class ModelA: public Airplane {
    public:
        virtual void fly(const Airport& destination) {
            defaultFly(destination);
        }
        ...
    };

    class ModelB: public Airplane {
    public:
        virtual void fly(const Airport& destination) {
            defaultFly(destination);
        }
        ...
    };

    class ModelC: public Airplane {
    public:
        virtual void fly(const Airport& destination);
        ...
    };

    void ModelC::fly(const Airport& destination) {
        ...						// 重写实现
    }
    ```

    2. 将fly函数改为纯虚函数，并在Airplane中给出其缺省实现。

    ```cpp
    class Airport { ... };		// 机场类
    class Airplane {
    public:
        virtual void fly(const Airport& destination) = 0;
        ...
    };

    void Airplane::fly(const Airport& destination) {	// 纯虚函数的实现
        ...						// 缺省实现
    }

    class ModelA: public Airplane {
    public:
        virtual void fly(const Airport& destination) {
            Airplane::fly(destination);
        }
        ...
    };

    class ModelB: public Airplane {
    public:
        virtual void fly(const Airport& destination) {
            Airplane::fly(destination);
        }
        ...
    };

    class ModelC: public Airplane {
    public:
        virtual void fly(const Airport& destination);
        ...
    };

    void ModelC::fly(const Airport& destination) {
        ...						// 重写实现
    }
    ```
- 声明非虚函数的目的是为了令派生类继承函数的接口和强制实现。


### 6.4 Item35 Consider alternatives to virtual functions

1. 藉由 Non-Virtual Interface（NVI）手法实现 Template Method 模式

```cpp
class GameCharacter {
public:
    int healthValue() const {			// 不会被派生类重写
        ...								// 事前工作
        int retVal = doHealthValue();	// 真正的工作
        ...								// 事后工作
		return retVal;
    }
    ...
private:
    virtual int doHealthValue() const {	// 会被派生类重写
        ...								// 缺省实现，虽说是inline，但不是有意为之
    }
};
```

NVI手法的优点是可以给真正的工作提供一些必要的事前准备工作和事后清理工作：事前准备工作包括锁定互斥器（locking a mutex），制造运转日志记录项（log entry），验证类约束条件，验证函数先决条件等；事后清理工作包括互斥器解除锁定（unlocking a mutex），验证函数的的事后条件，再次验证类的约束条件等。

NVI手法也有一些反直觉的地方，即在派生类中重写了private virtual函数，但这些重写函数却不会被派生类调用。但其实这并不矛盾，重写virtual，赋予了派生类“如何实现机制”的控制能力，但基类保留了诉说“函数何时被调用”的权利。



2. 藉由 Function Pointers（函数指针）实现 Strategy 模式

主要思想是增加一个函数指针作为private成员变量，该函数通过外部传入，从而实现不同的计算健康值的行为。

```cpp
class GameCharacter;										// 前置声明
int defaultHealthCalc(const GameCharacter& gc);				// 计算健康值的缺省实现
class GameCharacter {
public:
    typedef int (*HealthCalcFunc)(const GameCharacter&);	// 函数指针定义
    explicit GameCharacter(HealthCalcFunc hcf = defaultHealthCalc)
        : healthFunc(hcf) {}
    int healthValue() const {
        return healthFunc(*this);
    }
    ...
private:
    HealthCalcFunc healthFunc;
};
```

优点：
    
- 提供设计弹性，同一人物的不同实体可以有不同的健康计算函数。如下：

    ```cpp
    class EvilBadGuy: public GameCharacter {
    public:
        explicit EvilBadGuy(HealthCalcFunc hcf = defaultHealthCalc)
            : GameCharacter(hcf) { ... }
        ...
    };

    int loseHealthQuickly(const GameCharacter&);		// 健康值计算函数1
    int loseHealthSlowly(const GameCharacter&);			// 健康值计算函数2

    EvilBadGuy ebg1(loseHealthQuickly);
    EvilBadGuy ebg2(loseHealthSlowly);		// 相同的人物类型搭配不同的健康值计算方式
    ```

- 某已知人物之健康值计算函数可以在运行期变更。只需给GameCharacter提供一个setHealthCalculator函数，用来替换当前的健康值计算函数指针。


3. 藉由std::function完成 Strategy 模式

将上述的函数指针的成员变量替换为std::function对象，std::function对象可以持有任何可调用物（函数指针，函数对象或成员函数指针），相当于一个更加泛化的函数指针，从而使得设计更具弹性。

```cpp
class GameCharacter;										// 前置声明
int defaultHealthCalc(const GameCharacter& gc);				// 计算健康值的缺省实现

class GameCharacter {
public:
    typedef std::function<int (const GameCharacter&)> HealthCalcFunc;	// 
    explicit GameCharacter(HealthCalcFunc hcf = defaultHealthCalc)
        : healthFunc(hcf) {}
    int healthValue() const {
        return healthFunc(*this);
    }
    ...
    
private:
    HealthCalcFunc healthFunc;
};
```

这里，由std::function类型（即我们typedef的HealthCalcFunc类型）产生的对象可以持有任何与签名式（int (const GameCharacter&)）兼容的可调用物，所谓兼容，即为可调用物的参数可以被隐式转换为const GameCharacter&，而其返回类型可被隐式转换为int。e.g., 函数指针, 函数对象（仿函数）, lambda , 成员函数指针（std::bind）

```cpp
EvilBadGuy ebg5([&](const GameCharacter& gc) {
    ...		// 省略实现
});

ebg5.healthValue();
```

4. 古典的 Strategy 模式

传统的 Strategy 模式做法会将健康值计算函数做成一个分离的继承体系中的virtual成员函数。

```cpp
class GameCharacter;			// 前置声明
class HealthCalcFunc {
public:
    ...
    virtual int calc(const GameCharacter& gc) const {
        ...
    }
    ...
};

class SlowHealthLoser: public HealthCalcFunc {
public:
    ...
    virtual int calc(const GameCharacter& gc) const override;
	...
};

int SlowHealthLoser::calc(const GameCharacter& gc) const{
    ...
}

HealthCalcFunc defaultHealthCalc;

class GameCharacter {
public:
    explicit GameCharacter(HealthCalcFunc* phcf = &defaultHealthCalc)
        : pHealthCalc(phcf) {}
    int healthValue() const {
        return pHealthCalc->calc(*this);
    }
    ...
private:
    HealthCalcFunc* pHealthCalc;
};

SlowHealthLoser shl;
GameCharacter gc1(&shl);
```


### 6.5 Item36 Never redefine an inherited non-virtual function

### 6.6 Item37 Never redefine a function's inherited default parameter value

```cpp
enum class ShapeColor 
{ 
    Red = 0,
 	Green,
 	Blue
};

class Shape {
public:
    void draw(ShapeColor color = ShapeColor::Red) const {	// non-virtual，不可重新定义
        doDraw();	// 调用一个virtual
    }
    ...
private:
    virtual void doDraw(ShapeColor color) const = 0;	// 可被重新定义
};

class Rectangle: public Shape {
public:
    ...
private:
    virtual void doDraw(ShapeColor color) const;		// 注意，不须指定缺省参数值
};
```

### 6.7 Item38 Model "has-a" or "is-implemented-in-terms-of through composition

- has-a（有一个） 关系：

    对象属于应用域（application domain），即对象相当于塑造现实世界中的某些事物。例如Person类有Address、PhoneNumber等类型的成员变量。

- is-implemented-in-terms-of（根据某物实现出）关系：

    对象属于实现域（implementation domain），即其他对象纯粹是实现细节的人工设计。例如缓冲区（Buffers）、互斥器（Mutexes）等。

### 6.8 Item39 Use private inheritance judiciously

首先需要明确的是private继承的两个规则：

1. 如果类之间的继承关系是private，则编译器不会自动地将一个派生类对象隐式转换成一个基类对象；
2. 由private继承而来的所有成员，在派生类中都会变成private属性；


### 6.9 Item40 Use multiple inheritance(MI) judiciously

```cpp
class B1 {
public:
    void foo() {
        std::cout << "B1" << std::endl;
    }
};

class B2 {
public:
    void foo() {
        std::cout << "B2" << std::endl;
    }
};

class D:public B1, public B2 {
};

int main() {
    D d;
    d.foo();			// 编译报错，无法判断要调用哪个foo
  	d.B1::foo();	// 指定B1
    d.B2::foo();	// 指定B2
}
```