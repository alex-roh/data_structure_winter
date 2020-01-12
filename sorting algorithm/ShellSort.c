
void shellSort(int* arr, int length) {

	int i, j, gap, key;

	for (gap = length / 2; gap > 0; gap /= 2) {

		if (gap % 2 == 0) gap++; // determine 'gap', which should be the odd number
		
		// it's just a plain insertion sort, but we use 'gap' to compare distant elements
		for (i = gap; i < length; i++) {
			
			key = arr[i]; // key -> current item to be sorted

			for (j = i; j >= gap; j -= gap) {
				if (key < arr[j - gap])
					arr[j] = arr[j - gap];
				else
					break;
			}

			arr[j] = key;
		}
	}

}

void insertionSortForShellSort(int * arr, int p, int r, int gap) {

	int i, j, key;

	for (i = p + gap; i < r; i += gap) {

		key = arr[i];

		for (j = i - gap; (j >= p && arr[j] > key); j -= gap)
			arr[j + gap] = arr[j];
 		
		arr[j + gap] = key;

	}

}

void shellSortSecond(int *arr, int length) {

	int i, gap;

	for (gap = length / 2; gap > 0; gap /= 2) {

		if (gap % 2 == 0) gap++;

		for (i = 0; i < gap; i++) { // gap -> the number of sub-lists
			insertionSortForShellSort(arr, i, length, gap);
		}

	}
}