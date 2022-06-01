// 作用：函数名可以相同，提高复用性

// 满足条件：
// · 同一个作用域下
// · 函数名称相同
// · 函数参数类型不同，或者个数不同或者顺序不同
// 返回值不能作为重载的条件

//int func() {
//	cout << "this is func" << endl;
//}

void func() {
	cout << "this is func" << endl;
}

void func(int a) {
	cout << "this is func (int a)" << endl;
}
func(10)

void func(double a) {
	cout << "this is func (double a)" << endl;
}
func(3.14)

void func(double a, int b) {
	cout << "this is func (double a int b)" << endl;
}
func(3.14,10)

// 注意事项

// 1. 引用作为重载条件
void func(int& a) {
	cout << "func(int &a)调用" << endl;
}
int a = 10;
func(a);

void func(const int& a) {
	cout << "func(cosnt int &a)调用" << endl;
}
func(10);

// 2.函数重载遇到默认参数，出现二义性，报错，尽量避免