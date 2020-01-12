#define MAX 1000

void merge(int *arr, int p, int q, int r) 
{
	int i, lst_end, length, pos;
	int temp[MAX];

	// lst arr = [p...q]
	// 2nd arr = [q+1...r]
	lst_end = q - 1;
	pos = p; // index for temp
	length = r - p + 1;

	// copy two arrays into temp
	while ((p <= lst_end) && (q <= r))
		if (arr[p] <= arr[q]) 
			temp[pos++] = arr[p++];
		else 
			temp[pos++] = arr[q++];

	// if lst array has a leftover element
	while (p <= lst_end)
		temp[pos++] = arr[p++];

	// if 2nd array has a leftover element
	while (q <= r)
		temp[pos++] = arr[q++];

	// copy temp into the original array
	for (i = 0; i < length; i++)
		arr[r] = temp[r--];
}

void mergeSort(int *num, int p, int r) {

	if (r > p) 
	{	
		int q = (p + r) / 2;
		mergeSort(num, p, q);
		mergeSort(num, q + 1, r);
		merge(num, p, q + 1, r);
	}

}

// arr[] = { 26, 5, 37, 1, 61, 11, 59, 15, 48, 19 };

/*  when merge(num, p, q + 1, r), lst_end = q - 1
	after merge: 5 26 37 1 61 11 59 15 48 19
	after merge: 5 26 37 1 61 11 59 15 48 19
	after merge: 5 26 37 1 61 11 59 15 48 19
	after merge: 1 5 26 37 61 11 59 15 48 19
	after merge: 1 5 26 37 61 11 59 15 48 19
	after merge: 1 5 26 37 61 11 15 59 48 19
	after merge: 1 5 26 37 61 11 15 59 19 48
	after merge: 1 5 26 37 61 11 15 19 48 59
	after merge: 1 5 11 15 19 26 37 48 59 61
	mergeSort: 1 5 11 15 19 26 37 48 59 61
*/

/* when merge(num, p, q, r), lst_end = q
	after merge: 26 26 37 1 61 11 59 15 48 19
	after merge: 26 26 26 1 61 11 59 15 48 19
	after merge: 26 26 26 1 1 11 59 15 48 19
	after merge: 26 26 26 26 1 11 59 15 48 19
	after merge: 26 26 26 26 1 11 11 15 48 19
	after merge: 26 26 26 26 1 11 11 11 48 19
	after merge: 26 26 26 26 1 11 11 11 48 48
	after merge: 26 26 26 26 1 11 11 11 11 48
	after merge: 1 11 11 11 11 26 26 26 26 1
	mergeSort: 1 11 11 11 11 26 26 26 26 1
*/