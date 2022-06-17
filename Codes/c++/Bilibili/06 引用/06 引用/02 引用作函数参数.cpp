
// 地址传递
void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

swap(&a, &b);


// 引用传递
void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

swap(a, b);