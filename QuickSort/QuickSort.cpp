// QuickSort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <time.h>

using namespace std;

void	quicksort(int A[], int low, int high);
int		partition(int A[], int low, int high);
int		choosePivot(int A[], int low, int high);

int _tmain(int argc, _TCHAR* argv[])
{
	/* initialize random seed: */
	srand ((unsigned int)time(NULL));

	const int size = 2000;
	int *tosort = new int[size];

	for (int i = 0; i < size; i++)
	{
		tosort[i] = rand() % 100;
	}

	cout << "Start sorting" << endl;

	quicksort(tosort,0,size - 1);

	for (int ii = 0; ii < size; ii++)
	{
		cout << tosort[ii] << ' ';
	}

	cout << endl;

	delete [] tosort;

	system("pause");
	return 0;
}

void quicksort(int A[] , int low, int high)
{
	if (low < high)
	{
		int p = partition(A,low, high);
		quicksort(A,low,p-1);
		quicksort(A,p + 1,high);
	}
}

int partition(int A[], int low, int high)
{
	int pivotIndex = choosePivot(A,low,high);
	int pivotValue = A[pivotIndex];
	swap(A[pivotIndex],A[high]);
	int storeIndex = low;

	for (int i = low; i < high; i++)
	{
		if (A[i] <= pivotValue)
		{
			swap(A[i],A[storeIndex]);
			storeIndex = storeIndex + 1;
		}
	}

	swap(A[storeIndex],A[high]);
	return storeIndex;
}

int		choosePivot(int A[], int low, int high)
{
	//check for overfow
	int index = (low + high) / 2;

	return index;
}


