
// ��ַ����
void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

swap(&a, &b);


// ���ô���
void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

swap(a, b);