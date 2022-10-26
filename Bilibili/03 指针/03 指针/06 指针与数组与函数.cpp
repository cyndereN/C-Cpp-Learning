#include <iostream>
using namespace std;

void bubbleSort(int* arr, int len) {  // int arr[]
	for (int i = 0; i < len - 1; i++) {
		for (int j = 0; j < len - 1 - i; j++) {
			int temp = arr[j];
			arr[j] = arr[j + 1];
			arr[j + 1] = temp;
		}
	}
}

int main() {
	int arr[10] = { 4,3,6,9,1,2,10,8,7,5 };

	int len = sizeof(arr) / sizeof(arr[0]);

	bubbleSort(arr, len);


	system("pause");
	return 0;
}


// 创建数组并初始化

int **Array = (int**)malloc(ArrayRow * sizeof(int *));		// 先行
for (int i = 0; i < ArrayRow; i++)
{
    Array[i] = (int*)malloc(ArrayCol * sizeof(int));		// 后列
    memset(Array[i], 0, ArrayCol * sizeof(int));			// 初始化 0
}

for (int i = 0; i < 3; i++)									// 释放内存
{
	free(Array[i]);
}
free(Array);									

// ---

int **Array = new int *[ArrayRow];
for (int i = 0; i < ArrayRow; i++)
{
	Array[i] = new int[ArrayCol]();							// 初始化 0
}

for(i = 0; i < ArrayRow; i++)  								// 释放内存
{  
    delete[] Array[i];  
}   
delete[] Array;  
