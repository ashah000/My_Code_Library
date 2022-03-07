#include <stdio.h>

// Subarray with given sum
//// Algorithm  - 1.1
int subarray_given_sum_brute_force(int *arr, int n, int given_sum)
{
	int curr_sum;
	int i = 0, j;
	for (; i < n; i++)
	{
		curr_sum = arr[i];
		if (curr_sum == given_sum) // Checking for First Element
		{
			printf("\nsub array found at index %d\n", i);
			return 1;
		}
		for (j = i + 1; j < n; j++)
		{
			curr_sum = curr_sum + arr[j];

			if (curr_sum > given_sum)
			{
				break;
			}

			if (curr_sum == given_sum) // Checking
			{
				printf("\nsub array found between index %d and %d\n", i, j); // j was incremented.. 
				return 1;
			}
		}
	}

	// If we reach here, then no subarray
	printf("\nNo subarray found!!!\n");
	return 0;
}

//// Algorithm  - 1.2
//Two Pointer Approach - Left and Right
int subarray_given_sum(int *arr, int n, int given_sum)
{
	int curr_sum = arr[0];
	int right = 1;
	for (int left = 0; left < n && right <= n; )
	{
		if (curr_sum == given_sum) // Checking
		{
			printf("\nsub array found between index %d and %d\n", left, right - 1); // right is already incremented.
			return 1;
		}

		if (curr_sum > given_sum)
		{
			curr_sum -= arr[left];
			left += 1;
		}

		if (curr_sum < given_sum)
		{
			if (right < n)
				curr_sum += arr[right];
			right += 1;
		}

	}

	// If we reach here, then no subarray
	printf("\nNo subarray found!!!\n");
	return 0;
}

// Algorithm - 2.1
// Find a triplet such that sum of two equals to third element, Time Complexity - O(n^3)
void find_triplet_brute_force(int *arr, int n)
{
	for (int i = 0; i < n - 2; i++) // i doesnt need to traverse till n as j and k will help
	{
		for (int j = i + 1; j < n - 1; j++) // j doesnt need to traverse till n as k will help
		{
			for (int k = j + 1; k < n; k++)
			{
				if ((arr[i] == (arr[j] + arr[k])) || (arr[j] == (arr[i] + arr[k])) || (arr[k] == (arr[j] + arr[i]))) // Any order, unsorted array
				{
					printf("\nTriplet found %d %d %d\n", arr[i], arr[j], arr[k]);
					return;
				}
			}
		}
	}
	printf("\n No such Triplet Exist \n");
}

// Algorithm - 2.2
void find_triplet_efficient(int *arr, int n)
{
	printf("\n No such Triplet Exist \n");
}

void Array_Algo()
{
	printf("\nLets Do Array Algos!!\n");

	int arr[] = { 15, 8, 9, 10, 30, 26, 56 };
	int given_sum = 49;
	int n = sizeof(arr) / sizeof(arr[0]);

	// 1st Algorithm
	//subarray_given_sum(arr, n, given_sum);
	//subarray_given_sum_brute_force(arr, n, given_sum);

	// 2nd Algorithm
	find_triplet_brute_force(arr, n);
	find_triplet_efficient(arr, n);

}