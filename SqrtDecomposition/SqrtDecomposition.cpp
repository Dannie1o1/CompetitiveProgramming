// SqrtDecomposition.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "iostream"
#include "math.h"

using namespace std;

#define N 100000 //Maximum number for array
#define SQRSIZE 10000 //Square Root of N

int arr[N]; //Holds the original array
int dArr[SQRSIZE]; //Holds the decomposed array
int dArrSize; //Size of the decomposed array

void preprocess(int input[], int numOfElements)
{
	//Fills values in input[] into arr
	
	//Initializing Block pointer
	int dArrIndex = -1;

	//Calulate Size of dArr
	dArrSize = sqrt(numOfElements);

	//Build Decomposed Arr
	for (int i = 0; i < numOfElements; i++)
	{
		arr[i] = input[i];
		if (i%dArrSize == 0)
			dArrIndex++;
		dArr[dArrIndex] += arr[i];
	}
}


int query(int l, int r) // Time Complexity : 0(sqrt(n))
{
	int sum = 0;
	while (l < r && l%dArrSize != 0 && l != 0)
	{
		//Calculate First Block
		sum += arr[l];
		l++;
	}
	while (l + dArrSize <= r)
	{
		//Calculate Middle Whole Blocks
		sum += dArr[l / dArrSize];
		l += dArrSize;
	}
	while (l <= r)
	{
		sum += arr[l];
		l++;
	}

	return sum;
}

void update(int val, int index)
{
	int dArrIndex = index / dArrSize;
	dArr[dArrIndex] += val - arr[index];
	arr[index] = val;
}


int main()
{
	int input[] = { 1, 5, 2, 4, 6, 1, 3, 5, 7, 10 };
	int n = sizeof(input) / sizeof(input[0]);

	preprocess(input, n);

	cout << "query(3,8) : " << query(3, 8) << endl;
	cout << "query(1,6) : " << query(1, 6) << endl;
	update(0, 8);
	cout << "query(8,8) : " << query(8, 8) << endl;
	return 0;
}
