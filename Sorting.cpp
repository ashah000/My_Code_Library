#include <stdio.h>

//Helper Functions

//Helper Swap Function
void swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

//Helper Display Function
void Display(int *a, int n)
{
	printf("Elements in Array are:");
	for (int i = 0; i < n; i++)
	{
		printf(" %d", a[i]);
	}
	printf("\n");
}

/*
**** Bubble_Sort ****

Name is given as like Stone when thrown in water it settles down and bubbles come on the top.
Similarly Greatest Element will go down the list that is in the end after every pass.
For 'n' elements, n - 1 passes are required to sort the complete list. 
i.e list of 5 Elements after 4 passes will get sorted as remaining 5th element is smallest when four largest have already been found.

Time Complexity is O(n^2)

Advantages: Adaptive sorting using the flag variable.
For Already sorted/Nearly Sorted list - The time complexity is O(n)
Finding first 5 Greatest number in a long list will have only 5 passes.

*/
void Bubble_Sort(int *a, int n)
{
	int flag = 0;
	for (int i = 0; i < n - 1; i++)
	{
		flag = 0;
		for (int j = 0; j < n - i - 1; j++) // Should not traverse to the element already sorted.
		{
			if (a[j] > a[j + 1])
			{
				swap(&a[j], &a[j + 1]);
				flag = 1;
			}
		}
		if (flag == 0) // Adaptive Bubble Sort - Improvement by saving the Passes.
		{
			break;
		}
	}
}

/*
**** Insertion Sort ****
Assuming First Element in the Array is already Sorted. Remaining Elements are not Sorted.
Take out one Element from unsorted Elements from our Assumption and insert - Compare with the First Element and Swap in case 2nd Number 
is less than First Element - This is First Pass.

This way we will continue and Compare with already Sorted Elements and Swap Whenever there is swap, other already sorted elements 
will be shifted towards right as they are already sorted. 

The left Side of the Array will be sorted and the elements in the right will be unsorted.
There will be 4 Passes for 5 Elements. i.e. n-1 Passes for n Elements.
No. of Swaps :- 1 + 2 + 3 + ... + (n-1) = n(n-1)/2 = O(n^2)

Time Complexity : O(n^2)

Benefit of Insertion Sort in Linked List is that we dont need to shift Elements. Thats why more useful in Linked List than Array or it can be 
said that it is designed for Linked Lists.

Insertion Sort is Adaptive in nature, dont need use any separate Flags. If the list is already sorted Time is : O(n)
Worst Case : O(n^2) - list is sorted in descending order.

Only Bubble Sort and Insertion_Sort are Adaptive Algorithms.

*/
void Insertion_Sort(int *arr, int n)
{
	int key, j;
	for (int i = 1; i < n; i++) // This is for Passes - Start from 1 as we are assuming that First Element is already Sorted.
	{
		key = arr[i]; // First Element from the Unsorted Array Part
		j = i - 1;	  // It will be used for shifting and Swapping in the Sorted Part.

		while (j >= 0 && arr[j] > key) // The Unsorted Element is less than Element in Sorted Part -> So Shift 
		{
			arr[j + 1] = arr[j]; // Shifting starts,  Also arr[j+1] is already saved in key.
			j = j - 1; // Shifting till it reaches First Element or found element less than key
		}

		arr[j + 1] = key; // In Case of first Position, The current value of j would be -1 
	}
}

/*
**** Selection Sort ****
In 1st Pass we will sort the smallest Element in the List.
We will select the position i.e index 0 and i will be pointing to the slected position.
We will use two variables/Pointers j and k pointing to index i. 
We will move j in the list and only brings k to the position when a[j] < a[k]

This way we will keep selecting the index i in second passes and more. so we will sort in (n - 1 ) passes.
Selection sort good for less number of swaps. since we are using the extra variables j and k to avoid swaps.

Also result of first pass gives smallest number in the list and so on and so forth. 
similar to Bubble Sort - which gives largest number after first pass.

Drawback : It is not adaptive since it is also swapping with itself if it is already sorted.
so always time complexity  - O(n^2)

*/
void Selection_Sort(int arr[], int n)
{
	int i, j, k;
	for (i = 0; i < n - 1; i++)
	{
		for (j = k = i; j < n; j++)
		{
			if (arr[j] < arr[k])
			{
				k = j;
			}
		}
		swap(&arr[k], &arr[i]);
	}
}


/*
**** Quick Sort ****

It works on the idea that Element is in the sorted Position if all the Elements in the left are smaller than the selected Element and 
all the Elements in the right are greater than the selected Element. This Selected Element initially Pivot Element will be used for partitioning.

Quicksort uses partitioning Procedure for sorting - Actually it starts with Pivot Element which could be first index in the list and later this Pivot Element 
Comes exactly in the sorted position around which list divides in to two and then recursive Quicksort Algorithm is applied on smallers left and right sublists and 
their respective Pivots and Partioning till only element remains in each of the list.

Example : Teaching Asking the Students to be in Queue as per their Height. Here Student coming to its poistion is Pivot.

Algorithm has 2 Parts: 
1.) Partitioning Procedure :- i and j index pointing to 2nd Index and EOL(Infinity) respectively. Loop till i <= j and keep incrementing i till A[i] <= pivot	
							  and keep decrementing j till A[j] > pivot. Swap A[i] and A[j] for other cases. 
							  In the end swap A[j] with pivot element which is in sorted position and j is the partitioning position.

2.) Recursive Quick Sort Algorithm

*/


/* Partitioning Procedure for Qucik Sort and returns the Partitioning Element 

Worst Case Time Complexity of Quick Sort is O(n^2) when the list is already sorted.

Best Case : If the Pivot Element divides exactly in to 2 halves. i.e. Partitioning in the middle. 
so list is reduced by 2 on every iteration so total logn times for n elements. Time Complexity is nlogn (Divide and Conquer)

Average Case is : O(nlogn)

When Middle Element is Pivot: (Worst case will become best case)
For a Sorted list we can take the Pivot Element as Middle rather than First then time Complexity is nlogn
Worst Case : Partitioning it at one of the end but not sorted still complexity is O(n^2) in this case. 

Randomized Quick Sort - Some Random Element is taken as Pivot

In Selection Sort - Selecting the Index and Finding the Element.
In Quick Sort - Selecting the Element and Finding the Index for partitioning. thats why also called selection Exchange Sort/ Partition Exchange Sort.

*/

int partition(int arr[], int low, int high)
{
	int pivot = arr[low]; // This will change for Middle Element and Random Element as Pivot
	int i = low, j = high;

	while (i < j)
	{
		while (arr[i] <= pivot)
		{
			i++;
		}

		while (arr[j] > pivot)
		{
			j--;
		}

		if (i < j)
		{
			swap(&arr[i], &arr[j]);
		}
	}

	swap(&arr[low], &arr[j]); // Pivot must be placed in correct position now.
	return j;
}

void Quick_Sort(int arr[], int low, int high)
{
	int pivot_index;
	if (low < high)
	{
		pivot_index = partition(arr, low, high);
		Quick_Sort(arr, low, pivot_index - 1);
		Quick_Sort(arr, pivot_index + 1, high);
	}
}

void Sorting()
{
	printf("\nLets Do Sorting!!\n");
	int A[10] =  { 5, 7, 9, 1, 4, 8, 2, 6, 10, 3 };
	int A1[10] = { 6, 7, 8, 1, 4, 9, 2, 5, 10, 3 };
	int A2[10] = { 6, 7, 8, 1, 4, 9, 2, 10, 3, 5 };
	int A3[10] = { 7, 8, 6, 1, 4, 2, 9, 10, 3, 5 };
	Display(A, 10);
	printf("\n1.) ******Bubble Sort****** \n");
	Bubble_Sort(A, 10);
	Display(A, 10);

	printf("\n2.) ******Insertion Sort****** \n");
	Insertion_Sort(A1, 10);
	Display(A1, 10);

	printf("\n3.) ******Selection Sort****** \n");
	Selection_Sort(A2, 10);
	Display(A2, 10);

	printf("\n4.) ******Quick Sort****** \n");
	Quick_Sort(A3, 0, 9);
	Display(A3, 10);

}