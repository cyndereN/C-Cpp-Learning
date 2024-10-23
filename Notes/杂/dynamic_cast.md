# dynamic_cast

dynamic_cast提供类型安全检查，类型之间转换如果不兼容返回null，有时候我们需要在运行时判断一个对象的多态类型，就可以使用dynamic_cast，与Java的instanceof一样，被叫做Capability Query。

多态类型之间的转换包括：

- 子类向父类的向上转换(Up Cast)
- 父类向子类的向下转换(Down Cast)
- 横向转换(Cross Cast)

```cpp
/*
 A - B
 | / |
 C   D
*/
class A {
public:
    A() {}
    ~A() {}
};
class B {
public:
    B() {}
    ~B() {}
};
class C : public A, public B {
public:
    C() {}
    ~C() {}
};
class D : public B {
public:
    D() {}
    ~D() {}
};
int main() {
    B* p1 = new D();
    A* p2 = dynamic_cast<A*>(p1); // p2 == null
    
    B* p3 = new C();
    A* p4 = dynamic_cast<A*>(p3); // p2 != null
    return 0;
}
```

注意：
- static_cast: performs conversions between compatible types，类型不兼容编译器会报错
- reinterpret_cast: reinterpret_cast-“重新诠释的转型”
- reinterpret_cast 运算符并不会改变括号中运算对象的值，而是对该对象从位模式上进行重新解释，It will simply perform a binary copy of the data without altering the underlying bit pattern.
- const_cast: add or remove the const modifier of a variable.
- dynamic_cast: convert object pointers and object references into other pointer or reference types in the inheritance hierarchy.

最好不要手工通过dynamic_cast判断具体类型，应该通过interface的方式实现多态调用