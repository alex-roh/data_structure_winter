#include <stdio.h>
#include <stdlib.h>
#include "SortingAlgorithm.h"

int arr[] = { 26, 5, 37, 1, 61, 11, 59, 15, 48, 19 }; 
int temp[] = { 26, 5, 37, 1, 61, 11, 59, 15, 48, 19 };
int length = 10;

void printArr(const char* str) {

	int i;

	printf("%s: ", str);

	for (i = 0; i < length; i++) {
		printf("%d ", arr[i]);
	}

	printf("\n");
}

int main(void) {

	//printArr("before buildMaxHeap");
	//buildMaxHeap(arr, length);
	//printArr("After buildMaxHeap");

	printArr("before heapSort");
	heapSort(arr, length);
	printArr("after heapSort");

	return 0;
}