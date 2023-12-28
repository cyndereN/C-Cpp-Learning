# PIMPL

Pointer to implementation: Through a private member pointer, the internal implementation data of the class pointed to by the pointer is hidden.

Pimpl Benefit: 

- Reduce module coupling 减少耦合
- Reduce compilation dependencies 其一减少原类不必要的头文件的依赖，加速编译；其二对Impl类进行修改，无需重新编译原类
- Interface and implementation are separated to improve the stability of the interface (接口和实现的分离（隐藏了类的实现）)
- 可使用惰性分配技术 类的某部分实现可以写成按需分配或者实际使用时再分配，从而节省资源。
- Save resources (can be null, smaller stack)

Pimpl Drawback: 
- 每个类需要占用小小额外的指针内存。
- 每个类每次访问具体实现时都要多一个间接指针操作的开销
- 使用、阅读和调试上都可能有所不便。(Reduce readability)

e.g.,
```cpp
// 普通做法：
//x.h
class X
{
public:
    void Fun();
private:
    int i; //add int i;
};
 
//c.h
#include <x.h>
class C
{
public:
    void Fun();
private:
    X x; //与X的强耦合
};
 
// PIMPL做法：
//c.h
class X; //代替#include <x.h>
class C
{
public:
    void Fun();
private:
    X *pImpl; //pimpl
};
```
