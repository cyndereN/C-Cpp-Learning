
```cpp
auto lambda = [capture-values](arguments) -> return-value{}

// [=] 值传递方式捕获
// [&] 引用形式捕获
// [&, x] x以值传递，其余变量引用
// [=, &x] x引用方式传递，其余值传递
```

```cpp
// e.g.
int main()
{
    int x = 10;
    
    auto add_x = [x](int a) mutable { x *= 2; return a + x; };  // 复制捕捉x
    
    cout << add_x(5) << endl; // 输出 25
    cout << x << endl; // 输出 10
    return 0;

    // 引用捕获方式，无论是否标记mutable，都可以在lambda表达式中修改捕获的值
}
```