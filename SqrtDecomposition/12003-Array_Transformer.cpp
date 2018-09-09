#include "stdafx.h"
#include <iostream>
#include <math.h>

using namespace std;

#define N 300000		//Max num for arr
#define SQRSIZE 547		//Max size for the decomposed arr

int arr[N];				//Input Array
int dArr[SQRSIZE];		//Holds the decomposed array
int dArrSize;			//Holds the size of the decomposed array

void preprocess(int input[], int numOfElements)
{
	/*This function processes an input array, 
	places it into a global array, and creates a sqrt decomposed array*/ 

	//Initialize Block Pointer for the decomposed array to be
	int dArrIndex = -1;

	//Calculate Size of decomp Arr
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
			
void query(int L, int R, int v, int p)
{
	L--, R--;  //Since the array starts from index zero and the range of these two parameters start from 1
	int k = 0; //Tracks the numbers greater than 'v' parameter

	while (L < R && L%dArrSize != 0 && L != 0)
	{
		if (v > arr[L])
			k++;
		L++; //Move to next index
	}
	while (L + dArrSize <= R)
	{
		if (v > dArr[L / dArrSize])
			k += dArrSize;
		else
		{
			for (int i = L; i < L+dArrSize; i++)
			{
				//go through all the elements in that block
				if (v > arr[i])
					k++;
			}
		}

		L += dArrSize;
	}
	while (L <= R)
	{
		if (v > arr[L])
			k++;
		L++; //Move to next index
	}

	//Update arr at index p to u*k/(R-L+1)
	cout << "The value of k is..." << k << endl;
	int dArrIndex = p / dArrSize;
	int val = (arr[p] * k) / (R - L + 3);
	dArr[dArrIndex] += val - dArr[p];
	cout << "Val is..." << val << endl;
	arr[p] = val;


	
}


int main()
{
	cout << "program is running" << endl;
	int n = 0;		//Size of the input array
	int m = 0;		//Number of queries
	int u = 0;		//Max Num that could be in the input arr
	int L = 0;      //Left boundary parameter for the query func
	int R = 0;      //Right boundary parameter for the query func
	int v = 0;      //Comparison Value Parameter for the query func
	int p = 0;		//Target index parameter
	int *inputArr;  //Point for inputArr 

	cin >> n >> m >> u;

	inputArr = new int[n]; //Assign pointer to an array with N elements

	for (int i = 0; i < n; i++)
	{
		if (i <= n)
		{
			cin >> u;
			inputArr[i] = u;
			preprocess(inputArr, n);
		}
	}
	for (int i = 0; i < m; i++)
	{
		cin >> L >> R >> v >> p;
		/*cout <<*/ query(L, R, v, p) /*<< endl*/;
	}


	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << endl;
	}
	return 0;
}