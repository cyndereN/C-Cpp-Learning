constexpr修饰函数时其实只是告诉编译器该函数可以按常量值的表达式去优化，但是如果函数本身不是常量值的表达式的话依然能够编译通过。

C++20新增了consteval关键字，用来修饰函数时常量值的表达式，而且是强制性的。如果函数本身不是常量值的表达式的话则会编译失败。

```cpp
constexpr int add100_constexpr(int n) {
  return n + 100;
}
 
consteval int add100_consteval(int n) {
  return n + 100;
}
 
void test() {
    constexpr int c_constexpr = add100_consteval(200);
    int x = 200;
    // int d_consteval = add100_consteval(x);   // 编译失败
    int d_constexpr = add100_constexpr(x);      //编译成功，constexpr并非强制限定为常量表达式
}
```
