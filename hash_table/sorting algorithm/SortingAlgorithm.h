#pragma once

// selection sort
void selectionSortMax(int* arr, int length);
void selectionSortMin(int* arr, int length);

// bubble sort
void bubbleSortFaster(int* arr, int length);
void bubbleSortSlower(int* arr, int length);

// insertion sort
void insertionSort(int* arr, int length);

// shell sort
void shellSort(int* arr, int length);
void shellSortSecond(int* arr, int length);

// quick sort
void quickSort(int* arr, int p, int r);

// merge sort
void mergeSort(int* num, int p, int r);

// heap sort
void buildMaxHeap(int* arr, int length);
void heapSort(int* arr, int length);