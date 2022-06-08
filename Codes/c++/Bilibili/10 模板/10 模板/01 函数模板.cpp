// C++另一种编程思想称为泛型编程，主要利用模板
// 分为两种：函数模板和类模板
// 作用：建立一个通用函数，其函数返回值类型和形参类型可以不具体制定，用一个虚拟的类型来代表

// 语法：template<typename T>
// 函数声明或定义

template<typename T> 
void mySwap(T& a, T& b) {
	T temp = a;
	a = b;
	b = temp;
}

// 用法 
// 1. 自动类型推导（不会发生隐式类型转换）
mySwap(a, b);
// 2. 显示指定类型（可以发生隐式类型转换）
mySwap<int>(a, b);

// 案例 实现通用对数组进行排序的函数
template<typename T>
void mySort(T arr[], int len) {
	for (int i = 0; i < len; i++) {
		int max = i;
		for (int j = i + 1; j < len; j++) {
			if (arr[max] < arr[j]) {
				max = j;
			}
		}

		if (max != i) {
			mySwap(arr[max], arr[i]);
		}
	}
}

void test01() {
	// 测试char
	char charArr[] = "bacfe";
	int len = sizeof(charArr) / sizeof(char);
	mySort(charArr, len);
	printArray(charArr, len);
}

template <class T>
void printArray(T arr[], int len) {
	for (int i = 0; i < len; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

// 如果函数模板和普通函数都可以调用，优先调用普通函数
// 可以通过空模板参数列表强制调用模板函数
// 函数模板可以发生函数重载
// 如果函数模板可以产生更好的匹配，优先调用函数模板

// 利用具体化Person的版本实现代码，具体化优先调用
template<> bool myCompare(Person& a, Person& b) {
	if (a.Name == b.name) {
		return true;
	}
	return false;
}