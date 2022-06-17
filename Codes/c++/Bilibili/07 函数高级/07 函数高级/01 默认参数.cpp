int func(int a, int b = 20, int c = 30) {
	return a + b + c;
}

// 如果某个位置有了默认参数，那么从这个位置往后从左到右都得有默认值

// 如果函数声明有默认参数，函数实现就不能有默认参数（反之亦然，声明和实现只能有一个有默认参数）
int func2(int a, int b = 10);

func2(int a, int b) {
	return a + b;
}