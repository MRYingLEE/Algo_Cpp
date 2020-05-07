From time to time, I found I had some better solutions than the published ones.

In order for me to review the solutions easily, besides commenting on the original page, I put my solution here also.


1. Count number of increasing sub-sequences : O(NlogN)
Given an array arr[] of length N, the task is to find the number of strictly increasing sub-sequences in the given array.
(https://www.geeksforgeeks.org/count-number-of-increasing-sub-sequences-onlogn/?ref=leftbar-rightbar).

Please check "increasing sub-sequences.cpp" or the following code snippet:

```c++
#include <iostream>
#include <vector>
using namespace std;


#define maxN 20 
#define maxSum 50 
#define minSum 50 
#define base 50 


// To store the states of DP 
int dp[maxN][maxSum + minSum];

// Function to return the required count 
int findCnt(int* arr, int i, int required_sum, int n)
{
	if (n == 0) return (required_sum == 0) ? 1 : 0;

	dp[0][0] = 1;
	for (int j = 1; j < maxSum + minSum; j++)
		dp[0][j] = 0;

	dp[0][arr[0]]++;

	for (auto k = 1; k < n; k++)
	{
		for (int j = 0; j < maxSum + minSum; j++)
			if ((j - arr[k - 1]) >= 0)
				dp[k][j] = dp[k - 1][j] + dp[k - 1][j - arr[k - 1]];
			else
				dp[k][j] = dp[k - 1][j];
	}

	auto result = dp[n-1][required_sum];

	return result;

}

// Driver code 
int main()
{
	int arr[] = { 3, 3, 3, 3 };
	int n = sizeof(arr) / sizeof(int);
	int x = 6;

	cout << "fff" << findCnt(arr, 0, 6, n);

	return 0;
}


```
