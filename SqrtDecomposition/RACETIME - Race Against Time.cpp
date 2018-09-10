//#include "stdafx.h"
#include <iostream>
#include <math.h>

using namespace std;

#define N 100000		//Max num for arr
#define SQRSIZE 317		//Max size for the decomposed arr

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

void count(int L, int R, int v)
{
	L--, R-- ;	 //Since the array starts from index zero and the range of these two parameters start from 1
	unsigned long long k = 0; //Tracks the numbers greater than 'v' parameter

	while (L < R && L%dArrSize != 0 && L != 0)
	{
		if (v >= arr[L])
			k++;
		L++; //Move to next index
	}
	while (L + dArrSize <= R)
	{
		if (v >= dArr[L / dArrSize])
			k += dArrSize;
		else
		{
			for (int i = L; i < L + dArrSize; i++)
			{
				//cout << "dArr[" << i << "] = " << dArr[i] << endl;
				//go through all the elements in that block
				if (v >= arr[i])
					k++;
			}
		}

		L += dArrSize;
	}
	while (L <= R)
	{
		if (v >= arr[L])
			k++;
		L++; //Move to next index
	}

	//Update arr at index p to u*k/(R-L+1)




	cout /*<< "The value of k is..."*/ << k << endl;


}

void update(int i, int X)
{
	i--;
	int dArrIndex = i / dArrSize;
	dArr[dArrIndex] += X - arr[i];
	arr[i] = X;
}


int main()
{
	int n, q;
	int * inputArr;

	cin >> n >> q;
	inputArr = new int[n];

	for (int i = 0; i < n; i++)
	{
		int num;
		cin >> num;
		inputArr[i] = num;
	}

	preprocess(inputArr, n);

	
	//for (int i = 0; i < dArrSize; i++)
	//{
	//	cout << dArr[i] << endl;
	//}


	for (int  i = 0; i < q; i++)
	{
		char option;
		cin >> option;

		if (option == 'M')
		{
			int i, X;
			cin >> i >> X;
			update(i, X);
			//for (int i = 0; i < n; i++)
			//{
			//	cout << arr[i] << endl;
			//}

		}
		else if (option == 'C')
		{
			int P, Q, X;
			cin >> P >> Q >> X;
			count(P, Q, X);
		}
	}

	return 0;
}