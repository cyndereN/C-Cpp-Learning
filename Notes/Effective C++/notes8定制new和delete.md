## 8 Customizing new and delete

### 8.1 Item49 Understand the behavior of new-handler

用 std::nothrow 修饰 new 操作符，可以使内存分配阶段不会抛异常，失败了就返回 null 指针（但不能保证new 一个对象时，后续的构造函数不抛异常，比如构造函数中又new了一些内存）

```cpp
int *p = new (std::nothrow) int[0x1fffffff];		// p为NULL
```

而当用户使用std::set_new_handler函数为new操作符指定一个new_handler函数时，operator new 无法满足某个内存分配需求，则会不断调用new_handler函数，直到找到足够的内存。

```cpp
// 函数原型

namespace std {
	typedef void (*new_handler)();						// typedef 函数指针
    // throw()表示不会抛出异常，现在已经使用noexcept代替
    // 输入参数为新的handler函数，返回原handler函数
    new_handler set_new_handler(new_handler p) throw();	
}
```

```cpp
void OutOfMem() {
    std::cerr << "Unable to satisfy request for memory\n";
    std::abort();		// 终止程序，若VS Debug模式会有弹窗提示
}

int main() {
    std::set_new_handler(OutOfMem);
    int *p = new int[0x1fffffff];
    return 0;
}
```

e.g.,

```cpp
void OutOfMem() {
    std::cerr << "Unable to satisfy request for memory\n";
    std::abort();		// 终止程序，若VS Debug模式会有弹窗提示
}

int main() {
    std::set_new_handler(OutOfMem);
    int *p = new int[0x1fffffff];
    return 0;
}
```


### 8.2 Item50 Understand when it makes sense to replace new and delete

- 用来检测运用上的错误。自定义的new/delete可以比较容易地检测到内存越界行为，比如在new时超额申请内存，在真正使用的内存区块前后的额外空间中写入特定的数值，即内存签名，在delete时检查这些内存签名是否被改写，以监测越界写行为。
- 为了强化效能。编译器提供的new/delete为了适用于各种各样的内存分配场景，在内存碎片、额外空间开销和时间性能上都是保持中庸的水平。对于特定的需求和场景，使用定制化的内存管理会有更好的性能表现。
- 为了收集使用上的统计数据。例如，内存分配的时空分布，内存块的申请和归还的次序（FIFO、LIFO或随机），内存峰值等。
- 为了弥补缺省分配器中的非最佳对齐。例如，在X86体系结构下，double类型在内存地址8-byte齐位的情况访问最快。如果编译器自带的operator new不保证动态分配的double类型采用8-byte齐位，则可以自行实现一个，以提高程序效率。
- 为了将相关对象成簇集中。比如已知某个数据结构往往一起使用，那么分配的时候应该尽量让所有数据的内存集中一些，避免频繁触发换页中断（page faults） ，提升访问效率。
- 为了获得非传统的行为。比如当希望分配和归还共享内存（shared memory）内的区块，但能够管理该内存的只有C API（shmget等），那么可以自行实现定制版的new/delete，为C API 封装一层C++接口。


### 8.3 Item51 Adhere to convention when writing new and delete

- 正确处理申请内存失败的情况。当有足够内存用于申请时，new就返回一个指针指向那块内存；如果申请失败，若new-handler函数不为null，就会调用new-handler函数（以期其能解决当前内存不足的问题，如释放某些内存出来），并再次尝试分配内存；若new-handler函数为null，则会抛出std::bad_alloc异常。
- 正确处理申请0-bytes的情况。即使用户申请0-bytes的内存，我们也要为其返回一个合法的指针。常用的方法就是申请1-bytes的内存并返回。
- 正确理解operator new内含的无穷循环。退出循环的办法有：内存被成功分配；new-handler函数做了条款49中描述的事：让更多的内存可用、安装另一个new-handler、卸载new-handler、抛出std::bad_alloc异常或其派生、承认失败，调用std::abort()或std::exit()。
- 正确处理基类的operator new被派生类继承的情况。若需要实现特定类的operator new成员函数，需要考虑通常情况下，派生类对象要比基类对象大，因此派生类调用基类的operator new会有问题
- 正确处理operator delete删除null指针的情况。
- 同样考虑派生类继承operator delete的问题。

### 8.4 Item52 Write placement delete if you write placement new

所谓 placement new/delete，是指除固定的size_t参数以外，还接受其他额外参数的特殊operator new/delete。

其中，接受一个指针指定对象该被构造的内存地址的placement new是最早/最常用的一个，已经被纳入C++标准库（`#include <new>`），而且是placement new命名的由来：即一个特定位置上的new。具体形式如下：

```cpp
void *operator new(std::size_t, void*) throw();
```
当然，我们也可以自定义一个placement new，如接受一个ostream用来log分配信息，如下：

```cpp
class Widget {
public:
	...
	// placement new 成员函数
    static void* operator new(std::size_t size, std::ostream& logStream) throw(std::bad_alloc);	
    // 普通operator delete 成员函数
    static void operator delete(void* pMemory, std::size_t size);
};

// 用户代码
Widget* pw = new(std::cerr) Widget;		// 调用placement new，存在潜在的内存泄漏风险
```

对于new对象的过程，可以分为以下两个步骤：

1. operator new分配对象所需的内存空间；
2. 在该内存空间上执行对应的构造函数；

当步骤1成功，步骤2抛出异常时，已经申请的内存空间需要被回收，已防止内存泄漏。这在使用普通的operator new时是可以做到的，因为运行期系统知道与其对应的operator delete，并自动调用。然而，当使用placement new时，系统会尝试寻找并调用与placement new额外参数个数与类型均一致的operator delete，若没有找到，则系统什么都不会做，从而造成了内存泄漏。

所以规则很简单：当我们自定义一个placement new时，也要提供一个带相同额外参数的placement delete，以规避可能的内存泄漏

## 9 Miscellany

### 9.1 Item53 Pay attention to compiler warnings

- 严肃对待编译器发出的警告信息。
我们经常会忽略编译器给出的警告信息，但是no-warning是值得被推崇的，除非你清楚的了解warning信息确实无伤大雅。

- 但也不要过度依赖编译器的报警能力。
不同的编译器之间可能存在差异，一旦移植到另一个编译器上，原本依赖的警告信息有可能就消失。

### 9.2 Item54 Familiarize yourself with the standard library, including TR1

C++ TR1（Technical Report 1）并非标准，而是一份对C++98标准补充新特性的草稿文件。TR1详细阐述了14个新组件，放在std::tr1命名空间下，其中绝大部分已经定版，收录到了C++11标准中。

https://no5-aaron-wu.github.io/2022/11/01/EffectiveC-7-ReadNote07/

### 9.3 Item55 Familiarize yourself with Boost

Boost是一个C++开发者集结的社群，也是个可自由下载的程序库集，网址是 http://boost.org。

其特殊性：和C++标准委员会有着独一无二的密切关系，且具有很深影响力；接纳程序库非常严谨，需要一次以上的同行专家评审。

Boost 程序库集可处理的场景有许多（且囊括了TR1的实现），可区分出数十个类别，并且还在持续增加。