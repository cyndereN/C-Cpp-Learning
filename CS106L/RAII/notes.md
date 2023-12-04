# Resource Acquisition Is Initialization
智能指针是在 <memory> 头文件中的 std 命名空间中定义的。 它们对 RAII 或“获取资源即初始化”编程惯用法至关重要。 此习惯用法的主要目的是确保资源获取与对象初始化同时发生，从而能够创建该对象的所有资源并在某行代码中准备就绪。
大多数情况下，当初始化原始指针或资源句柄以指向实际资源时，会立即将指针传递给智能指针。这样做的好处是，当智能指针被销毁时，它会自动释放资源。这样，我们就不必担心在函数退出时忘记释放资源，也不必担心在函数退出时发生异常而导致资源泄漏。这种方法被称为资源获取即初始化（Resource Acquisition Is Initialization，RAII）。
通常具有释放指针所有权的重置成员函数(.reset())；通常提供直接访问其原始指针的方法(.get())。
e.g.,
ifstream input("hamlet.txt"); // should not call close(), because if exception throwed may not close

lock_guard<mutex>(databaseLock);


- unique_ptr: Uniquely owns its resource and delete it when obj is destroyed. cannot be copied!
（by deleting the copy constructor and copy assignment）

std::unique_ptr<Node> n(new Node);

std::unique_ptr<Node> n = std::make_unique<Node>(); // always use this


```cpp
// Create a unique_ptr to an array of 5 integers.
auto p = make_unique<int[]>(5);

// Initialize the array.
for (int i = 0; i < 5; ++i)
{
    p[i] = i;
    wcout << p[i] << endl;
}
```

- shared_ptr: Resources can be stored by any number of shared_ptrs. Delete when none of them points to it

```cpp
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
```

- weak_ptr: Similar to shared_ptr, but doesn't contribute to the reference count. Used to deal with circular references with shared_ptr.

```cpp
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Controller
{
public:
   int Num;
   wstring Status;
   vector<weak_ptr<Controller>> others;
   explicit Controller(int i) : Num(i), Status(L"On")
   {
      wcout << L"Creating Controller" << Num << endl;
   }

   ~Controller()
   {
      wcout << L"Destroying Controller" << Num << endl;
   }

   // Demonstrates how to test whether the
   // pointed-to memory still exists or not.
   void CheckStatuses() const
   {
      for_each(others.begin(), others.end(), [](weak_ptr<Controller> wp) {
         auto p = wp.lock();
         if (p)
         {
            wcout << L"Status of " << p->Num << " = " << p->Status << endl;
         }
         else
         {
            wcout << L"Null object" << endl;
         }
      });
   }
};

void RunTest()
{
   vector<shared_ptr<Controller>> v{
       make_shared<Controller>(0),
       make_shared<Controller>(1),
       make_shared<Controller>(2),
       make_shared<Controller>(3),
       make_shared<Controller>(4),
   };

   // Each controller depends on all others not being deleted.
   // Give each controller a pointer to all the others.
   for (int i = 0; i < v.size(); ++i)
   {
      for_each(v.begin(), v.end(), [&v, i](shared_ptr<Controller> p) {
         if (p->Num != i)
         {
            v[i]->others.push_back(weak_ptr<Controller>(p));
            wcout << L"push_back to v[" << i << "]: " << p->Num << endl;
         }
      });
   }

   for_each(v.begin(), v.end(), [](shared_ptr<Controller> &p) {
      wcout << L"use_count = " << p.use_count() << endl;
      p->CheckStatuses();
   });
}

int main()
{
   RunTest();
   wcout << L"Press any key" << endl;
   char ch;
   cin.getline(&ch, 1);
}
```


# Scope Based Memory Management 
In modern C++, we pretty much never use new and delete!

# Constructor Acquires, Destructor Realeases

# Auto memory management is not always a good thing

