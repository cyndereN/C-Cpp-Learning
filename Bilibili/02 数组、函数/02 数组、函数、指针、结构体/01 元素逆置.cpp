#include <iostream>

using namespace std;

//int main() {
//	int arr[5] = { 1,3, 2, 5, 4 };
//
//	// 记录起始下标位置
//	// 记录结束下标位置
//	// 起始下标与结束下标元素互换
//	// 起始位置++ 结束位置--
//	// 循环执行，直到起始位置 >= 结束位置
//
//	int start = 0;
//	int end = sizeof(arr) / sizeof(arr[0]) - 1;
//
//	while (start < end) {
//		int temp = arr[start];
//		arr[start] = arr[end];
//		arr[end] = temp;
//
//		start++;
//		end--;
//	}
//
//	cout << "数组元素逆置后" << endl;
//
//	for (int i = 0; i < 5; i++) {
//		cout << arr[i] << endl;
//	}
//
//	system("pause");
//
//	return 0;
//}