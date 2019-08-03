// MergeSort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <time.h>

using namespace std;

///
///	Reference: http://en.wikipedia.org/wiki/Merge_sort
///
void TopDownmergeSort(int A[], int B[], int n);
void TopDownSplitMerge(int A[], int iBegin, int iEnd, int B[]);
void TopDownMerge(int A[], int iBegin, int iMiddle, int iEnd, int B[]);
void CopyArray(int B[], int iBegin, int iEnd, int A[]);


int _tmain(int argc, _TCHAR* argv[])
{
	srand ((unsigned int)time(NULL));

	const int size = 20000;
	int *A = new int[size];
	int *B = new int[size];

	for (int i = 0; i < size; i++)
	{
		A[i] = rand() % 100;
	}

	cout << "Start sorting" << endl;

	TopDownmergeSort(A,B,size);

	for (int i = 0; i < size; i++)
	{
		cout << B[i] << ' ';
	}

	cout << endl;

	system("pause");

	return 0;
}

void TopDownmergeSort(int A[], int B[], int n)
{
	TopDownSplitMerge(A, 0, n, B);
}

void TopDownSplitMerge(int A[], int iBegin, int iEnd, int B[])
{
   if(iEnd - iBegin < 2)                       // if run size == 1
        return;                                 //   consider it sorted
    // recursively split runs into two halves until run size == 1,
    // then merge them and return back up the call chain
    int iMiddle = (iEnd + iBegin) / 2;              // iMiddle = mid point
    TopDownSplitMerge(A, iBegin,  iMiddle, B);  // split / merge left  half
    TopDownSplitMerge(A, iMiddle,    iEnd, B);  // split / merge right half
    TopDownMerge(A, iBegin, iMiddle, iEnd, B);  // merge the two half runs
    CopyArray(B, iBegin, iEnd, A);              // copy the merged runs back to A
}

void TopDownMerge(int A[], int iBegin, int iMiddle, int iEnd, int B[])
{
    int i0 = iBegin, i1 = iMiddle;
 
    // While there are elements in the left or right runs
    for (int j = iBegin; j < iEnd; j++) {
        // If left run head exists and is <= existing right run head.
        if (i0 < iMiddle && (i1 >= iEnd || A[i0] <= A[i1]))
		{
            B[j] = A[i0];
            i0 = i0 + 1;
		}
        else
		{
            B[j] = A[i1];
            i1 = i1 + 1;   
		}
    } 
}

void CopyArray(int B[], int iBegin, int iEnd, int A[])
{
    for(int k = iBegin; k < iEnd; k++)
        A[k] = B[k];
}
 
