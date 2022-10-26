// 1. struct 是值类型，class 是对象类型

// 2. 默认的继承访问权。
// class默认的是private，struct默认的是public。
// **即class默认继承方式是private继承，而struct是public继承。
// struct可以继承class，同样class也可以继承struct
// 默认的继承访问属性取决于子类而不是基类

// e.g. struct A{};
// class B : A {};	//默认为private继承
// struct C : B {};	//默认为public继承

// 所以我们在写代码的时候，为了不引起歧义，最好指明继承的方式
// class B : public A{}；
// struct B : public A {}；

// 3. 默认权限。struct 默认权限是 公共 public， class 默认权限是 私有 private

// 4. class这个关键字还可用于定义模板参数，就像typename。但是strcut不用与定义模板参数

// 5. {}赋初值 
// 因为C++是对C的扩充，那么它就兼容过去C中struct的特性，例如
// struct A
//{
//char 	c1；
//int		i2;
//double	db3;
//};
//
//A a = { 'p', 7, 451.154 }; //定义时赋初值，在struct时没问题，在class时出错

// * 6. struct总是有默认的构造函数，即使是重载默认构造函数仍然会保留。
// 这是因为Struct的构造函数是由编译器自动生成的，但是如果重载构造函数，
// 必需对struct中的变量全部初始化。并且Struct的用途是那些描述轻量级的对象，
// 例如Line,Point等，并且效率比较高。
// class在没有重载构造函数时有默认的无参数构造函数，
// 但是一被重载些默认构造函数将被覆盖。

// ** 7.struct的new和class的new是不同的。
// struct的new就是执行一下构造函数创建一个新实例再对所有的字段进行Copy。
// 而class则是在堆上分配一块内存然后再执行构造函数，
// struct的内存并不是在new的时候分配的，而是在定义的时候分配


//注意:
//struct能包含成员函数吗？ 能！
//struct能继承吗？ 能！！
//struct能实现多态吗？ 能！！！