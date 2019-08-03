// GrahamScan.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>

struct PointAnglePair
{
	double x;
	double y;
	double angle;

	PointAnglePair(double X, double Y, double ANGLE)
	{
		x = X;
		y = Y;
		angle = ANGLE;
	}

	PointAnglePair()
	{
		x = y = angle = 0;
	}
};

double	CCW(PointAnglePair p1, PointAnglePair p2, PointAnglePair p3);
double	Polar_Angle(PointAnglePair center, PointAnglePair point);
double  ComputeArea(std::vector<PointAnglePair> input);

//quicksort
/*!	\brief QuickSort
*/
void	quicksort(PointAnglePair A[], int low, int high);
int		partition(PointAnglePair A[], int low, int high);
int		choosePivot(PointAnglePair A[], int low, int high);

int _tmain(int argc, _TCHAR* argv[])
{
	std::vector<PointAnglePair> input;

	/*
	input.push_back(PointAnglePair(-2,0,0));
	input.push_back(PointAnglePair(-2,2,0));
	input.push_back(PointAnglePair(0,2,0));
	input.push_back(PointAnglePair(0,4,0));
	input.push_back(PointAnglePair(2,4,0));
	input.push_back(PointAnglePair(2,2,0));
	input.push_back(PointAnglePair(4,2,0));
	input.push_back(PointAnglePair(4,0,0));
	input.push_back(PointAnglePair(0,0,0));
	*/
	
	
	input.push_back(PointAnglePair(0,2,0));
	input.push_back(PointAnglePair(-2,2,0));
	input.push_back(PointAnglePair(-2,0,0));
	input.push_back(PointAnglePair(-4,0,0));
	input.push_back(PointAnglePair(-4,-2,0));
	input.push_back(PointAnglePair(-2,-2,0));
	input.push_back(PointAnglePair(-2,-4,0));
	input.push_back(PointAnglePair(0,-4,0));
	input.push_back(PointAnglePair(0,-2,0));
	input.push_back(PointAnglePair(2,-2,0));
	input.push_back(PointAnglePair(2,0,0));
	input.push_back(PointAnglePair(0,0,0));
	

	std::random_shuffle ( input.begin(), input.end() );


	double area = ComputeArea(input);

	std::cout << "Area: " << area << std::endl;

	double convexArea = 0;

	size_t inputSize = input.size();

	PointAnglePair *points = new PointAnglePair[inputSize + 1];

	//determine lowest y-coordinate point
	std::vector<PointAnglePair>::const_iterator it = input.begin();
	int index = 1;

	while (it != input.end())
	{
		points[index].x		= (*it).x;
		points[index].y		= (*it).y;
		points[index].angle	= 0;

		if (index > 1 && points[index].y < points[1].y)
		{
			std::swap(points[index],points[1]);
		}

		++it;
		index++;
	}

	std::cout << "Lowest point is (" << points[1].x << " " << points[1].y << ")" << std::endl; 

	//compute polar angle
	std::cout << "Compute polar angle" << std::endl;
	for (int kk = 2; kk <= inputSize; kk++)
	{
		points[kk].angle = Polar_Angle(points[1], points[kk]);
		std::cout << points[kk].x << " " << points[kk].y << " " << points[kk].angle << std::endl;
	}

	//sort based on angle to x (based on angle)
	std::cout << "\nQuick Sort" << std::endl;
	quicksort(&points[1],0,inputSize - 1);

	//convex
	points[0] = points[inputSize];

	for (int ii = 0; ii <= inputSize; ii++)
	{
		std::cout << points[ii].x << " " << points[ii].y << " " << points[ii].angle << std::endl;
	}

	int M = 1;

	for (int ii = 2; ii <= inputSize; ii++)
	{
		while (CCW(points[M-1],points[M],points[ii]) <= 0)
		{
			if (M > 1)
				M -= 1;
			else if (ii == inputSize)
				break;
			else
				ii+=1;
		}

		M+=1;
		std::swap(points[M],points[ii]);
	}

	std::cout << "Convex points: " << std::endl;

	for (int ii = 0; ii <= M; ii++)
	{
		std::cout << points[ii].x << " " << points[ii].y << " " << points[ii].angle << std::endl;
	}

	//compute convexArea

	points[M] = points[0];

	for (int jj = 0; jj < M; jj++)
	{
		convexArea += points[jj].x * points[jj+1].y - points[jj].y * points[jj+1].x;
	}

	convexArea = convexArea * 0.5;

	std::cout << "Convex Area: " << convexArea << std::endl;
	
	//compute solidity
	double solidity = area / convexArea;

	delete [] points;


	system("pause");
	 
	return 0;
}

double CCW(PointAnglePair p1, PointAnglePair p2, PointAnglePair p3)
{
	double ret;

	ret = (p2.x - p1.x)*(p3.y - p1.y) - (p2.y - p1.y)*(p3.x - p1.x);

	return ret;
}

double	Polar_Angle(PointAnglePair center, PointAnglePair point)
{
	double ret;
	
	if (center.y == point.y)
	{
		if (point.x < center.x)
			ret =  180.0;
		else
			ret =  0.0;
	}
	else if (point.x == center.x)
		ret = 90.0;
	else
	{
		double dx = point.x - center.x;
		double dy = -(point.y - center.y);

		double inRads = std::atan2(dy,dx);

		// We need to map to coord system when 0 degree is at 3 O'clock, 270 at 12 O'clock
		if (inRads < 0)
			inRads = fabs(inRads);
		else
			inRads = 2.0*3.14159265359 - inRads;

		ret =  inRads * 180.0 / 3.14159265359;
	}

	return ret;
}

void quicksort(PointAnglePair A[] , int low, int high)
{
	if (low < high)
	{
		int p = partition(A,low, high);
		quicksort(A,low,p-1);
		quicksort(A,p + 1,high);
	}
}

int partition(PointAnglePair A[], int low, int high)
{
	int pivotIndex = choosePivot(A,low,high);
	double pivotValueAngle = A[pivotIndex].angle;
	double pivotValueX = A[pivotIndex].x;
	std::swap(A[pivotIndex],A[high]);
	int storeIndex = low;

	for (int i = low; i < high; i++)
	{
		if (A[i].angle < pivotValueAngle || A[i].angle == pivotValueAngle && A[i].x < pivotValueX)
		{
			std::swap(A[i],A[storeIndex]);
			storeIndex = storeIndex + 1;
		}
	}

	std::swap(A[storeIndex],A[high]);
	return storeIndex;
}


int	choosePivot(PointAnglePair A[], int low, int high)
{
	//check for overfow
	int index = (low + high) / 2;

	return index;
}

double  ComputeArea(std::vector<PointAnglePair> input)
{
	double area = 0.0;

	std::vector<PointAnglePair>::iterator it = input.begin();
	PointAnglePair currentPoint = *it;
	++it;

	for (; it != input.end(); ++it)
	{
		double y = (*it).y;
		double x =  (*it).x;
		area += (currentPoint.x * y- currentPoint.y * x) / 2.0;
		currentPoint = *it;
	}

	return fabs(area);
}
