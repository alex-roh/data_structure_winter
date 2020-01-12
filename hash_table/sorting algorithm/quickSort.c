#include <time.h>

// partition using additional array
int partitionAdd(int* arr, int p, int r) {

	int i, j, k, pivot;
	int* temp = (int*)malloc(sizeof(int) * (r + 1));
	
	pivot = arr[p];
	
	i = p;
	j = r;

	for (k = p + 1; k <= r; k++) 
	{
		if (arr[k] < pivot) {
			temp[i++] = arr[k];
		}
		else {
			temp[j--] = arr[k];
		}
	}

	temp[i] = pivot;
	for (k = p; k <= r; k++)
		arr[k] = temp[k];

	free(temp);

	return i;
}

// parition in-place
int partitionInPlace(int *arr, int p, int r) {

	int i, j, pivot, temp;
	pivot = p;
	i = p + 1;
	j = r;

	do {

		while (i <= r && arr[i] < arr[pivot]) i++;
		while (j >= p && arr[j] > arr[pivot]) j--;

		if (i < j) 
		{
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}

	} while (i < j);

	temp = arr[p];
	arr[p] = arr[j];
	arr[j] = temp;

	return j;
}

// randomized parition in-place
int randomizedPartition(int *arr, int p, int r) {

	srand(time(NULL));
	int i, j, pivot, temp;
	pivot = (rand() % (r - p + 1)) + p;
	temp = arr[pivot];
	arr[pivot] = arr[p];
	arr[p] = temp;

	return partitionInPlace(arr, p, r);
}

// easy partition - use the last element as a pivot
int partitionEasy(int *arr, int p, int r) {

	int pivot, i, cursor, temp;

	pivot = arr[r];
	i = p - 1; // there is yet no element less than the pivot
	cursor = 0;
	temp = 0;

	for (cursor = p; cursor < r; cursor++) {

		if (arr[cursor] <= pivot) {
			// we found an element less than the pivot
			i++; // so, increase i by 1
			temp = arr[i];
			arr[i] = arr[cursor];
			arr[cursor] = temp;
		}
	}

	// index (i + 1) means the first element not less than the pivot
	// so, we swap arr[i + 1] and arr[r](pivot)
	temp = arr[i + 1];
	arr[i + 1] = arr[r];
	arr[r] = temp;

	return i + 1;
}

void quickSort(int* arr, int p, int r) {
	
	if (p < r)
	{
		// int q = partitionAdd(arr, p, r);
		// int q = partitionInPlace(arr, p, r);
		// int q = randomizedPartition(arr, p, r);
		int q = partitionEasy(arr, p, r);
		quickSort(arr, p, q - 1);
		quickSort(arr, q + 1, r);
	}
}