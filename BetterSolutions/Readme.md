From time to time, I found I had some better solutions than the published ones.

In order for me to review the solutions easily, besides commenting on the original page, I put my solution here also.


1. Count number of increasing sub-sequences : O(NlogN)
Given an array arr[] of length N, the task is to find the number of strictly increasing sub-sequences in the given array.
(https://www.geeksforgeeks.org/count-number-of-increasing-sub-sequences-onlogn/?ref=leftbar-rightbar).

Please check "increasing sub-sequences.cpp" or the following code snippet:

```c++
// Example program
#include <iostream>
#include <string>
#include <climits>
#include <vector>
#include <array>
#include <chrono>
#include <functional>
#include <map>

using namespace std;
using namespace std::chrono;


// Driver code 
int main()
{
	int arr[] = { 1, 2, 10, 9 };
	int n = sizeof(arr) / sizeof(int);

	int sum_v = 1;

	map<int, int> m;
	m.emplace(arr[0], 1);

	for (int i = 1; i < n; i++) {
		int sum_below = 0;

		for (auto j : m) {
			if (j.first < arr[i])
				sum_below = sum_below + j.second;
		}

		auto f = m.find(arr[i]);

		if (f != m.end()) {
			m[arr[i]] = f->second + sum_below + 1;
		}
		else
			m.emplace(arr[i], sum_below + 1);

		sum_v += sum_below + 1;

	}

	std::cout << sum_v;

	return 0;
}
```
