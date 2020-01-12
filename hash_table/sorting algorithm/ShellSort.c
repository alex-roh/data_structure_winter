
void shellSort(int* arr, int length) {

	int i, j, gap, next;

	for (gap = length / 2; gap > 0; gap /= 2) {

		if (gap % 2 == 0) gap++;

		for (i = gap; i < length; i++) {
			
			next = arr[i];

			for (j = i; j >= gap; j -= gap) {
				if (next < arr[j - gap])
					arr[j] = arr[j - gap];
				else
					break;
			}

			arr[j] = next;
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