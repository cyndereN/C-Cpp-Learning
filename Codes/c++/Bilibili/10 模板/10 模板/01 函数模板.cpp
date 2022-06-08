// C++��һ�ֱ��˼���Ϊ���ͱ�̣���Ҫ����ģ��
// ��Ϊ���֣�����ģ�����ģ��
// ���ã�����һ��ͨ�ú������亯������ֵ���ͺ��β����Ϳ��Բ������ƶ�����һ�����������������

// �﷨��template<typename T>
// ������������

template<typename T> 
void mySwap(T& a, T& b) {
	T temp = a;
	a = b;
	b = temp;
}

// �÷� 
// 1. �Զ������Ƶ������ᷢ����ʽ����ת����
mySwap(a, b);
// 2. ��ʾָ�����ͣ����Է�����ʽ����ת����
mySwap<int>(a, b);

// ���� ʵ��ͨ�ö������������ĺ���
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
	// ����char
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

// �������ģ�����ͨ���������Ե��ã����ȵ�����ͨ����
// ����ͨ����ģ������б�ǿ�Ƶ���ģ�庯��
// ����ģ����Է�����������
// �������ģ����Բ������õ�ƥ�䣬���ȵ��ú���ģ��

// ���þ��廯Person�İ汾ʵ�ִ��룬���廯���ȵ���
template<> bool myCompare(Person& a, Person& b) {
	if (a.Name == b.name) {
		return true;
	}
	return false;
}