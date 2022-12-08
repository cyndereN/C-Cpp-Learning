# Resource Acquisition Is Initialization
e.g.,
ifstream input("hamlet.txt"); // should not call close(), because if exception throwed may not close

lock_guard<mutex>(databaseLock);

- unique_ptr: Uniquely owns its resource and delete it when obj is destroyed. cannot be copied!
（by deleting the copy constructor and copy assignment）

std::unique_ptr<Node> n(new Node);
std::unique_ptr<Node> n = std::make_unique<Node>(); // always use this


- shared_ptr: Resources can be stored by any number of shared_ptrs. Delete when none of them points to it
{
    std::shared_ptr<int> p1(new int);
    // Use p1
    {
        std::shared_ptr<int> p2 = p1;   // Only works if new ptrs are made through copying
        // Use p1 and p2
    }
    // Use p1 
}
// Freed

- weak_ptr: Similar to shared_ptr, but doesn't contribute to the reference count. Used to deal with circular references with shared_ptr.
# Scope Based Memory Management 
In modern C++, we pretty much never use new and delete!
# Constructor Acquires, Destructor Realeases

# PIMPL

Pointer to implementation: Through a private member pointer, the internal implementation data of the class pointed to by the pointer is hidden.

Pimpl Benefit: 

- Reduce module coupling 减少耦合
- Reduce compilation dependencies 其一减少原类不必要的头文件的依赖，加速编译；其二对Impl类进行修改，无需重新编译原类
- Interface and implementation are separated to improve the stability of the interface (接口和实现的分离（隐藏了类的实现）)
- 可使用惰性分配技术 类的某部分实现可以写成按需分配或者实际使用时再分配，从而节省资源。

Pimpl Drawback: 
- 每个类需要占用小小额外的指针内存。
- 每个类每次访问具体实现时都要多一个间接指针操作的开销，并且再使用、阅读和调试上都可能有所不便。

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


# Auto memory management is not always a good thing

