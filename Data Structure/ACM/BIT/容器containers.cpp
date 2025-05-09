/*STL(Standard Template Library)的六大组件：
  容器(containers)、迭代器(iterators)、空间配置器(allocator)、配接器(adapters)、算法(algorithms)、仿函数(functors)六个部分。
  其交互关系：容器通过空间配置器取得数据存储空间，
  空间配置器通过迭代器存取容器的内容，
  仿函数可以协助空间配置器完成不同的策略变化，
  配接器可以修饰或套接仿函数。
*/

// C++中的容器类包括“顺序存储结构”和“关联存储结构”，前者包括vector，list，deque等；后者包括set，map，
// multiset，multimap等。若需要存储的元素数在编译器间就可以确定，可以使用数组来存储，否则，就需要用到容器类了
// stack，queue，prioroty_queue都属于容器配接器，是由容器按照特殊的逻辑实现的


// 分类:
//STL容器分类
// 1，顺序容器 sequence containers
// array
// vector
// deque
// list
// forward-list 
// 2，关联容器 associative containers（红黑树实现）
// set
// multiset
// map
// multimap
// 3，无序容器 unordered containers （hash表实现）（非标准，也可以划分到关联容器）
// hash_set
// hash_multiset
// hash_map
// hash_multimap

// 解决哈希冲突的方法一般有：
// 开放定址法、链地址法（拉链法）、再哈希法、建立公共溢出区等方法。

// 1、vector

//     连续存储结构，每个元素在内存上是连续的；

//     支持高效的随机访问和在尾端插入/删除操作，但其他位置的插入/删除操作效率低下；

// 2、deque

//     连续存储结构，即其每个元素在内存上也是连续的，类似于vector，不同之处在于，deque提供了两级数组结构，第一级完全类似于vector，代表实际容器；另一级维护容器的首位地址。

//     这样，deque除了具有vector的所有功能外，还支持高效的首端插入/删除操作。

// 3、list

//     非连续存储结构，具有双链表结构，每个元素维护一对前向和后向指针，因此支持前向/后向遍历。

//     支持高效的随机插入/删除操作，但随机访问效率低下，且由于需要额外维护指针，开销也比较大。

// 4、vector V.S. list V.S. deque：

//     a、若需要随机访问操作，则选择vector；

//     b、若已经知道需要存储元素的数目， 则选择vector；

//     c、若需要随机插入/删除（不仅仅在两端），则选择list

//     d、只有需要在首端进行插入/删除操作的时候，才选择deque，否则都选择vector。

//     e、若既需要随机插入/删除，又需要随机访问，则需要在vector与list间做个折中。

//     f、当要存储的是大型负责类对象时，list要优于vector；当然这时候也可以用vector来存储指向对象的指针，同样会取得较高的效率，但是指针的维护非常容易出错，因此不推荐使用。

// 5、capacity V.S size

//     a、capacity是容器需要增长之前，能够盛的元素总数；只有连续存储的容器才有capacity的概念（例如vector，deque，string），list不需要capacity。

//     b、size是容器当前存储的元素的数目。

//     c、vector默认的容量初始值，以及增长规则是依赖于编译器的。

// 6、用vector存储自定义类对象时，自定义类对象须满足：

//     a、有可供调用的无参构造函数（默认的或自定义的）；

//     b、有可用的拷贝赋值函数（默认的或自定义的）

// 7、迭代器iterator

//     a、vector与deque的迭代器支持算术运算，list的迭代器只能进行++/--操作，不支持普通的算术运算。

// 8.序列类容器

// (1)vector向量相当于一个数组

//     在内存中分配一块连续的内存空间进行存储。支持不指定vector大小的存储。STL内部实现时，首先分配一个非常大的内存空间预备进行存储，即capacity（）函数返回的大小，当超过此分配的空间时再整体重新放分配一块内存存储，这给人以vector可以不指定vector即一个连续内存的大小的感觉。通常此默认的内存分配能完成大部分情况下的存储。

//    优点：(1) 不指定一块内存大小的数组的连续存储，即可以像数组一样操作，但可以对此数组进行动态操作。通常体现在push_back() pop_back()

//          (2) 随机访问方便，即支持[ ]操作符和vector.at()

//          (3) 节省空间。

//    缺点：(1) 在内部进行插入删除操作效率低。

//          (2) 只能在vector的最后进行push和pop，不能在vector的头进行push和pop。

//          (3) 当动态添加的数据超过vector默认分配的大小时要进行整体的重新分配、拷贝与释放

// (2)list 双向链表

//     每一个结点都包括一个信息快Info、一个前驱指针Pre、一个后驱指针Post。可以不分配必须的内存大小方便的进行添加和删除操作。使用的是非连续的内存空间进行存储。

//    优点：(1) 不使用连续内存完成动态操作。

//         (2) 在内部方便的进行插入和删除操作

//         (3) 可在两端进行push、pop

//    缺点：(1) 不能进行内部的随机访问，即不支持[ ]操作符和vector.at()

//          (2) 相对于verctor占用内存多

// (3) deque   双端队列 double-end queue

//    deque是在功能上合并了vector和list。

//    优点：(1) 随机访问方便，即支持[ ]操作符和vector.at()

//          (2) 在内部方便的进行插入和删除操作

//          (3) 可在两端进行push、pop

//    缺点：(1) 占用内存多

// 使用区别：

//      1）如果你需要高效的随即存取，而不在乎插入和删除的效率，使用vector

//      2）如果你需要大量的插入和删除，而不关心随机存取，则应使用list

//      3）如果你需要随机存取，而且关心两端数据的插入和删除，则应使用deque

//      4）如果打算存储数据字典，并且要求方便地根据key找到value，一对一的情况使用map，一对多的情况使用multimap。

//      5）如果打算查找一个元素是否存在于某集合中，唯一存在的情况使用set，不唯一存在的情况使用multiset。