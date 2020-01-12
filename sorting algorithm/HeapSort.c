void swap(int* first, int* second);

void maxHeapify(int *arr, int root, int length) {

	int leftChild = 2 * root + 1;
	int rightChild = 2 * root + 2;
	int largest = root;

	// if left child is larger than root
	if (leftChild < length && arr[leftChild] > arr[largest])
		largest = leftChild;

	// if right child is larger than root
	if (rightChild < length && arr[rightChild] > arr[largest])
		largest = rightChild;

	// if the largest index is not root, call itself recursively
	if (largest != root) {

		// swap largest and root
		swap(&arr[largest], &arr[root]);

		// now largest is original root (one level down)
		maxHeapify(arr, largest, length);
	}
}

void buildMaxHeap(int *arr, int length) {

	int i, firstParent;
	firstParent = (length - 1) / 2;

	for (i = firstParent; i >= 0; i--)
		maxHeapify(arr, i, length);
}

void heapSort(int* arr, int length) {

	int i, heapSize;
	heapSize = length;

	// convert an array into a max heap
	buildMaxHeap(arr, heapSize);

	// extract roots iteratively
	for (i = length; i > 1; i--) {

		// swap the root and the last node
		swap(&arr[0], &arr[heapSize - 1]);

		// make the current array into max heap
		maxHeapify(arr, 0, --heapSize); // minus heap size by 1
	}
}