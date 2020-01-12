
void insertionSort(int* arr, int length) {

	int i, j, key;

	for (i = 1; i < length; i++) {

		j = i - 1;     // j -> right border of the sorted part (and a cursor)
		key = arr[i];  // key -> current item to be sorted

		while (j >= 0 && key < arr[j]) { // shift right until 'j' finds the correct position
			arr[j + 1] = arr[j];
			j--;
		}

		arr[j + 1] = key;
	
	}
}