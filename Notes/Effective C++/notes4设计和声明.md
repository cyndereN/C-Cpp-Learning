## 4 Design and Declaration

### 4.1 Item18 Make interfaces easy to use correctly and hard to use incorrectly

- 考虑用户可能犯的各种错误
- 要把接口设计得一致
- 任何要求用户记住东西的接口都更容易造成误用

    第13章引入了一个工厂函数(factory function):

    ```
    Investment* createInvestment();
    ```

    为了防止资源泄漏，这个动态分配的资源必须在使用完后删除，但要求用户这样做可能会产生两种情景:

    用户忘记了删除
    多次删除同一个指针
    第13章的解决方法是使用智能指针自动管理资源，但如果用户忘记把这个函数的返回值封装在智能指针内呢?所以我们最好让这个函数直接返回一个智能指针对象:
    ```cpp
    std::shared_ptr<Investment> createInvestment();

    // 避免了DLL交叉问题(cross-DLL problem)。这个问题是当一个对象从一个DLL中生成，在另一个DLL中释放时，在许多平台上就会导致运行时的问题，因为不同DLL的new和delete可能会被链接到不同代码。shared_ptr的删除器则是固定绑定在创建它的DLL中，这就例如，我们有Stock类继承自Investment:
    std::shared_ptr<Investment> createInvestment(){
        return std::shared_ptr<Investment>(new Stock);
    }
    ```

    工厂函数返回的Stock类型智能指针就能在各个DLL中传递，智能指针会在构造时就固定好当引用计数为零时调用哪一个DLL的删除器，因此不必担心DLL交叉问题。

### 4.2 Item19 Treat class design as type design

- How should objects of your new type be created and destroyed?
- How should object initialisation differ from object assignment?
- What does it mean for objects of your new type to be passed by value?
- What are the restrictions on legal values for your new type?
- Does your new type fit into an inheritance graph?
- What kind of type conversions are allowed for your new type?
- What operators and functions make sense for the new type?
- What standard functions should be disallowed?
- Who should have access to the members of your new type?
- What is the 'undeclared interface' of your new type?
- How general is your new type?
- Is a new type what you really want?

### 4.3 Item20 Prefer pass-by-reference-to-const to pass-by-value

### 4.4 Item21 Don't return a reference when you must return an object

### 4.5 Item22 Declare data members private

### 4.6 Item23 Prefer non-member non-friend functions to member functions

```cpp
//webbrowser.h 包含浏览器的核心功能
namespace WebBrowserStuff{
  class WebBrowser{...};
  ...
}

//webbrowserbookmarks.h 包含收藏夹相关功能
namespace WebBrowserStuff{
  ...
}

//webbrowsercookies.h 包含cookies相关功能
namespace WebBrowserStuff{
  ...
}
//以上头文件的代码全部纳入同一名空间
```
非成员函数cleanBrowser()是更好的选择，因为它其实比成员函数cleanEverything()提供了更好的封装。此外，当相同的功能可以同时被成员函数和非成员函数实现时，选择非成员函数也能给WebBrowser类相关的功能提供更大的包装弹性，减少编译依赖，增加类的可扩展性。


### 4.7 Item24 Declare non-member fuctions when type conversions should apply to all parameters

Whenever you can avoid friend function, you should, much as in real life, friends are often more trouble than they worth

### 4.8 Item25 Consider support for a non-throwing swap

当默认的std::swap可能会拉低你自己的类的效率时，在自己的类里写一个swap成员函数，而且要保证它不会抛出异常

写了swap成员函数，按照编程惯例还要写一个非成员swap函数，放在类或者类模板的名空间下，用它来调用成员swap函数。对于类(非模板)，还要特殊化std::swap

在调用swap时，要加上一句using std::swap，然后调用时不需要再加任何名空间资格限制

为了自定义的类而完全特殊化std模板是没问题的，但千万不要给std里添加任何东西。
