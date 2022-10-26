// 引用必须引用一块合法的内存空间
const int& ref = 10;  // 编译器优化： int temp = 10; const int &ref = temp; 
ref = 20;   // 加入const之后变为只读，不可以修改

// 使用场景：修饰形参 防止误操作