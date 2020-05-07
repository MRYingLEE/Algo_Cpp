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
