void swap(int* first, int* second);

void selectionSortMax(int* arr, int length) {

	int i, j, max, temp = 0;

	for (i = length; i > 0; i--) 
	{
		max = 0;
		
		for (j = 0; j < i; j++)
			if (arr[j] > arr[max])	
				max = j;
		
		swap(&arr[j - 1], &arr[max]); // j - 1, because we did 'j++' in the loop above
	}

}

void selectionSortMin(int* arr, int length) {

	int i, j, min, temp = 0;

	for (i = 0; i < length; i++)
	{
		min = i;

		for (j = i + 1; j < length; j++) // j = i + 1, because min has to be the first element
			if (arr[j] < arr[min])
				min = j;

		swap(&arr[i], &arr[min]);
	}
}