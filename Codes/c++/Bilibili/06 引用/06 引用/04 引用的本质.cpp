// 引用的本质在c++的内部实现是一个指针常量
// 指向不可更改，指向的值可以更改

// 发现是引用，转化为int* const ref = &a 
void func(int& ref) {
	ref = 100;  // ref 是引用，转换为*ref = 100
}

int main() {
	int a = 10;

	// 自动转换为int* const ref = &a; 指针常量是指针指向不可改，也说明为什么引用不可改
	int& ref = a;
	ref = 20; // 内部发现是引用，自动转换： *ref = 20, 找到它指向的那块内存的数据，将其改成20

	func(a);

	return 0;
}