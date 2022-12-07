
int Partition(vector<string>& A, int low, int high) {
	string pivot = A[low];
	while (low < high) {
		while (low < high && A[high] >= pivot) high--;
		A[low] = A[high];
		while (low < high && A[low] <= pivot) low++;
		A[high] = A[low];
	}
	A[low] = pivot;

	return low;
}

void QuickSort(vector<string>& A, int low, int high) {
	if (low < high) {
		int pivot_pos = Partition(A, low, high);
		QuickSort(A, low, pivot_pos - 1);
		QuickSort(A, pivot_pos + 1, high);
	}
}