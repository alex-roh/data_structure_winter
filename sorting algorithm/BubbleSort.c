void swap(int* first, int* second);

void bubbleSortFaster(int *arr, int length) {

	int i, j, temp, flag = 1;

	for (i = length - 1; flag > 0; i--) {
		
		flag = 0;

		for (j = 0; j < i; j++) {

			if (arr[j] > arr[j + 1]) {

				swap(&arr[j], &arr[j + 1]);
				flag = 1;
			}
		}
	}
}

void bubbleSortSlower(int* arr, int length) {

	int i, j, temp;

	for (i = length - 1; i > 0; i--) {

		for (j = 0; j < i; j++) {

			if (arr[j] > arr[j + 1])
				swap(&arr[j], &arr[j + 1]);
		}
	}

}