#include <time.h>

void swap(int* first, int* second);

// partition using additional array
int partitionAdd(int* arr, int p, int r) {

	int i, j, k, pivot;
	int* temp = (int*)malloc(sizeof(int) * (r + 1)); // dynamic allocation to the additional array
	
	pivot = arr[p]; // pivot -> first element
	i = p;
	j = r;

	for (k = p + 1; k <= r; k++) // k -> cursor
	{
		if (arr[k] < pivot) {
			temp[i++] = arr[k];
		}
		else {
			temp[j--] = arr[k];
		}
	}

	temp[i] = pivot; // i -> after the loop, 'i' becomes the pivot position

	for (k = p; k <= r; k++) // copy
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

		while (i <= r && arr[i] < arr[pivot]) i++; // larger than the pivot
		while (j >= p && arr[j] > arr[pivot]) j--; // smaller than the pivot

		if (i < j) 
			swap(&arr[i], &arr[j]);

	} while (i < j);

	swap(&arr[p], &arr[j]); // change the pivot position

	return j;
}

// randomized parition in-place
int randomizedPartition(int *arr, int p, int r) {

	srand(time(NULL));
	int i, j, pivot, temp;
	pivot = (rand() % (r - p + 1)) + p;
	swap(&arr[pivot], &arr[p]);

	return partitionInPlace(arr, p, r);
}

// easy partition - use the last element as a pivot
int partitionEasy(int *arr, int p, int r) {

	int pivot, i, cursor, temp;

	pivot = arr[r];
	i = p - 1; // there is yet no element smaller than the pivot
	cursor = 0;
	temp = 0;

	for (cursor = p; cursor < r; cursor++) {

		if (arr[cursor] <= pivot) {
			// we found an element smaller than the pivot
			i++; // so, increase i by 1
			swap(&arr[i], &arr[cursor]);
		}
	}

	// index (i + 1) means the first element not smaller than the pivot
	// so, we swap arr[i + 1] and arr[r](pivot)
	swap(&arr[i + 1], &arr[r]);

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