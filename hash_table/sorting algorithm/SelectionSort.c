
void selectionSortMax(int* arr, int length) {

	int i, j, max, temp = 0;

	for (i = length; i > 0; i--) 
	{
		max = 0;
		
		for (j = 0; j < i; j++)
			if (arr[j] > arr[max])	
				max = j;
			
		temp = arr[j - 1];
		arr[j - 1] = arr[max];
		arr[max] = temp;
	}

}

void selectionSortMin(int* arr, int length) {

	int i, j, min, temp = 0;

	for (i = 0; i < length; i++)
	{
		min = i;

		for (j = i + 1; j < length; j++)
			if (arr[j] < arr[min])
				min = j;

		temp = arr[i];
		arr[i] = arr[min];
		arr[min] = temp;
	}
}