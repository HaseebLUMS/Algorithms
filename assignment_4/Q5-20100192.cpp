#include <algorithm>
#include <iostream>
#include <limits.h>
#include <cstdlib>
#include <vector>

using namespace std;


/*
	Time Complexity: O(n*n*n)
	Space Complexity: O(n*n)

*/



struct ansFormat
{
	int value;
	int order;
	int cornerIndexI;
	int cornerIndexJ;
};


void calculatePrefixSum(int** arr, int** arrSum, int n)
{
	for(int i = 0; i< n; i++)
	{
		for(int j = 0; j< n; j++)
		{
			if(i == 0)
			{
				if(j != 0){arrSum[i][j] = arrSum[i][j] + arrSum[i][j-1];}
			}

			else if (j == 0)
			{
				arrSum[i][j] = arrSum[i][j] + arrSum[i-1][j];
			}

			else
			{
				arrSum[i][j] = arrSum[i][j] + arrSum[i][j-1] + arrSum[i-1][j] - arrSum[i-1][j-1];
			}
		}
	}
}

void setAns(int i, int j, int order, int** arrSum, ansFormat& ans)
{
	if(i-order+1 >= 0){if(j-order+1 < 0){return;}}
	if(j-order+1 >= 0){if(i-order+1 < 0){return;}}
	if(i-order+1 < 0 || j-order+1 < 0){return;}

	/*if(order == 1)
	{
		if(ans.value < arrSum[i][j]){ans.value = arrSum[i][j]; ans.order = order; ans.cornerIndexI = i; ans.cornerIndexJ = j;}
	}*/

	else
	{
		int left = 0, top = 0, diagonal = 0;

		if(j-order >= 0){left = arrSum[i][j-order];}
		if(i-order >= 0){top = arrSum[i-order][j];}
		if(j-order >= 0 && i-order >= 0){diagonal = arrSum[i-order][j-order];}

		int currentAns = arrSum[i][j] - left - top + diagonal;

		if(ans.value < currentAns){ans.value = currentAns; ans.order = order; ans.cornerIndexI = i; ans.cornerIndexJ = j;}
	}


}


void calculateMaxAns(int** arrSum, int n, ansFormat& ans)
{
	for(int i = 0; i< n; i++)
	{
		for(int j = 0; j< n; j++)
		{
			for(int k = 1; k <= n; k++)
			{
				setAns(i, j, k, arrSum, ans);
			}
		}
	}
}


int main(){
	int n = 8;
	cin >> n;


	int** arr = new int*[n];
	for(int i = 0; i< n; i++)
	{arr[i] = new int[n];}


	int** arrSum = new int*[n];
	for(int i = 0; i< n; i++)
	{arrSum[i] = new int[n];}


	//Taking User Input
	//int inputArray[n*n] = { 25, 31, 1, 8, 33, -1, 20, -25,14, 13, -10, 2, 23, -7, 27, 21,31, 45, 11, -27, 8, 6, 7, 32,12, -19, -25, 4, -67, 4, 4, 13,14, -12, 10, 3, 11, 5, 4, 5,4, 4, -25, 4, -67, 13, 12, -19,22, -29, -15, 14, -37, -141, 14, 13,11, -29, -15, 14, 17, 6, 4, 13};
	//int inputArray[n*n] = { 1, 8, 33, -1, 20,-10, 2, 23, -7, 27,-27, 8, 6, 7, 32,-25, 4, -67, 4, 4,3, 11, 5, 4, 5 };
	int inputArray[n*n] = { 13, -3, 11, 18, -41, -75, -20, 25,11, -29, -15, 14, 17, 6, 4, 13,-93, -31, -10, 2, 23, -7, 27, 21, 2, -9, -25, 41, 67, 44, 14, -13, 14, -12, 10, 31, 13, 51, 14, 5, 4, 4, -25, 4, 67, 13, 21, -19,22, -77, -15, 53, 37, 47, 41, 13,-76, 45, 11, -27, 8, 6, 7, 32};

	/*
		int inputArray[n*n];
		srand(time(NULL));

		for(int i = 0; i< n*n; i++)
		{
			int ra = rand();
			inputArray[i] = ra;	
		}
	*/

	int t = 0;
	for(int i = 0; i< n; i++)
	{
		for(int j = 0; j< n; j++)
		{
			arr[i][j] = inputArray[t];
			arrSum[i][j] = inputArray[t];
			t++;
		}
	}


	calculatePrefixSum(arr, arrSum, n);
	ansFormat ans = {INT_MIN, 0, 0};
	calculateMaxAns(arrSum, n, ans);
	//for(int i = 0; i< n; i++){for(int j = 0; j< n; j++){cout << arrSum[i][j] << "  " ;}cout << endl;}

	cout << "Order: "<< ans.order << endl;
	cout << "Max Sum: "<< ans.value << endl;
	cout << "Bottom Right Corner: (" << ans.cornerIndexI << "," << ans.cornerIndexJ<< ")"<<endl; 
	cout << "Upper Left Corner: (" << ans.cornerIndexI - ans.order +1 << "," << ans.cornerIndexJ - ans.order +1 << ")" << endl;
	return 0;
}