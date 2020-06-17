From time to time, I found I had some better solutions than the published ones.

In order for me to review the solutions easily, besides commenting on the original page, I put my solution here also.


# 1. Count number of increasing sub-sequences : O(NlogN)
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


# 2. Counting tilings
Sometimes the states of a dynamic programming solution are more complex
than fixed combinations of numbers. As an example, consider the problem of
calculating the number of distinct ways to fill an n£m grid using 1£2 and 2£1
size tiles. For example, one valid solution for the 4x7 grid is

![4x7](https://github.com/MRYingLEE/Algo_Cpp/blob/master/BetterSolutions/4x7.JPG?raw=true)

and the total number of solutions is 781.

```c++
#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include <chrono>

using namespace std;
using namespace std::chrono;

using state = vector < vector<int>>;

int checked_states = 0;

int count_by_state(state state_current) {
	int i_rows = state_current.size();
	int i_columns = state_current[0].size();

	//if ((i_rows != 8) || (i_columns != 8))
	//	return 0;

	checked_states++;
	for (int i = 0; i < i_rows; i++)
		for (int j = 0; j < i_columns; j++)
		{
			if (state_current[i][j] == 0)
			{
				int count_down = 0;
				int count_right = 0;

				if (j < i_columns - 1) // right
				{
					if (state_current[i][j + 1] == 0) {
						state state_new = state_current;

						state_new[i][j] = 1;
						state_new[i][j + 1] = 1;

						count_right = count_by_state(state_new);
					}
				}

				if (i < i_rows - 1) //down
				{
					if (state_current[i + 1][j] == 0) {
						state state_new = state_current;
						state_new[i][j] = 1;
						state_new[i + 1][j] = 1;

						count_down = count_by_state(state_new);
					}
				}

				return count_down + count_right; // if not found right or down, just return 0;
				// This is the critical point to improve efficiency
			}
		}

	return 1; // All filled
}

void example(state state_a, string hint)
{
	std:cout <<endl<< hint << endl;

	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	checked_states = 0;
	int counts = count_by_state(state_a);

	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	auto duration = duration_cast<milliseconds>(t2 - t1).count();

	cout << "modulo duration(ms):" << duration << endl;
	std::cout << "Total Counting tilings:" << counts << endl;
	std::cout << "Total checked states:" << checked_states << endl;
}

void fill_0(state& state_0, int i_rows, int i_columns) {
	state_0.resize(i_rows);
	for (int i = 0; i < i_rows; i++) {
		state_0[i].resize(i_columns);
		for (int j = 0; j < i_columns; j++)
			state_0[i][j] = 0;
	}
}

int main()
{

	//************** This is the Aztec diamond tiling( https://en.wikipedia.org/wiki/Aztec_diamond )
	state  aztec_diamond  //{ 0 };
	{
	{ 1,1,1,0,0,1,1,1 },
	{ 1,1,0,0,0,0,1,1 },
	{ 1,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0 },
	{ 1,0,0,0,0,0,0,1 },
	{ 1,1,0,0,0,0,1,1 },
	{ 1,1,1,0,0,1,1,1 }
	};

	example(aztec_diamond, "This is the Aztec diamond tiling( https://en.wikipedia.org/wiki/Aztec_diamond )");


	//************** This is 4x7 grid
	state  state_4x7;

	fill_0(state_4x7, 4, 7);

	example(state_4x7, "This is 4x7 grid");


	//************** This is 5x5 grid
	state  state_5x5;

	fill_0(state_5x5, 5, 5);

	example(state_5x5, "This is 5x5 grid");



	//************** This is 8x8 grid
	state  state_8x8;

	fill_0(state_8x8, 8, 8);

	example(state_8x8, "This is 8x8 grid");


	return 0;
}
```
