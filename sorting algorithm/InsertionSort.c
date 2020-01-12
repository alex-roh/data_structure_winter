
void insertionSort(int* arr, int length) {

	int i, j, key;

	for (i = 1; i < length; i++) {

		j = i - 1;
		key = arr[i];

		while (j >= 0 && key < arr[j]) {
			arr[j + 1] = arr[j];
			j--;
		}

		arr[j + 1] = key;
	
	}
}