// ================================================================= Begin of Auto memoization section ==================================================

// The latest code can be found at: https://github.com/MRYingLEE/Algo_Cpp

#include <iostream>
#include <algorithm>
#include <cmath>
#include <limits>
#include <vector>
#include <functional>
#include <vector>
#include <string.h>

//*************************************************************
// The automatic memoization function 1D
//*************************************************************

using namespace std;

template<typename T, typename... ARGS>
class automemoizer_1d
{
	std::function<T(size_t, ARGS...)> m_f;
public:
	vector<T> memory_1d;
	vector<bool> memorized_1d;
	automemoizer_1d(std::function<T(size_t, ARGS...)> f, size_t size) : m_f(f), memorized_1d(size, false), memory_1d(size) {}
	T operator()(size_t id, ARGS... args) {
		if (memorized_1d[id] == false)
		{
			memory_1d[id] = m_f(id, args...);
			memorized_1d[id] = true;
		};

		return memory_1d[id];
	}

	void resize(size_t size) {
		if (memory_1d.size() < size)
		{
			memory_1d.resize(size + 1);
			memorized_1d.resize(size + 1);
		}
	}

	// fill is highly suggested for the following reason:
	// 	An iteration replaces recursive. 
	// Stack overflow and other overhead can be minimized.

	void fill(size_t endindex, ARGS... args) {
		fillrange(0, endindex, args...);
	}

	void fillrange(size_t startindex, size_t endindex, ARGS... args) {
		if (memory_1d.size() < endindex + 1)
		{
			memory_1d.resize(endindex + 1);
			memorized_1d.resize(endindex + 1, false);
		}

		for (size_t current = startindex; current <= endindex; current++) {
			memory_1d[current] = m_f(current, args...);
			memorized_1d[current] = true;
		}
	}
};

template<typename T, typename... ARGS>
automemoizer_1d<T, ARGS...> auto_1d(T(*f)(size_t, ARGS...),size_t size) { return automemoizer_1d<T, ARGS...>(f,size); } // size_t=unsigned int

template<typename T, typename... ARGS>
automemoizer_1d<T, ARGS...> auto_1d(T(*f)(int, ARGS...), size_t size) { return automemoizer_1d<T, ARGS...>(f, size); }

//*************************************************************
// The automatic memoization function -2D
//*************************************************************

template<typename T, typename... ARGS>
class automemory_2d
{
	std::function<T(size_t, size_t, ARGS...)> m_f;
public:
	vector<vector<T>> memory_2d;
	vector<vector<bool>> memorized_2d;
	automemory_2d(std::function<T(size_t, size_t, ARGS...)> f, size_t size0, size_t size1) : 
		m_f(f), 
		memorized_2d(size0, std::vector<bool>(size1, false)), 
		memory_2d(size0, std::vector<T>(size1)) {}

	T operator()(size_t id0, size_t id1, ARGS... args) {
		if (memorized_2d[id0][id1] == false)
		{
			memory_2d[id0][id1] = m_f(id0, id1, args...);
			memorized_2d[id0][id1] = true;
		};

		return memory_2d[id0][id1];
	}

	// fill is highly suggested for the following reason:
	// 	An iteration replaces recursive. 
	// Stack overflow and other overhead can be minimized.

	void resize(size_t size0, size_t size1) {
		if (memory_2d.size() < size0)
		{
			memory_2d.resize(size0 + 1);
			memorized_2d.resize(size0 + 1);
		}

		for (auto m : memorized_2d) {
			if (m.size() < size1) {
				m.resize(size1, false);
			}
		}

		for (auto m : memory_2d) {
			if (m.size() < size1) {
				m.resize(size1);
			}
		}
	}

	void fill01(size_t index0, size_t index1, ARGS... args) {
		//resize(index0, index0);

		for (size_t id1 = 0; id1 <= index0; id1++) {
			for (size_t id2 = 0; id2 <= index1; id2++) {
				if (memorized_2d[id1][id2] == false)
				{
					memory_2d[id1][id2] = m_f(id1, id2, args...);
					memorized_2d[id1][id2] = true;
				};
			}
		}
	}

	void fill10(size_t index0, size_t index1, ARGS... args) {
		//resize(index0, index1);

		for (size_t id1 = 0; id1 <= index1; id1++) {
			for (size_t id0 = 0; id0 <= index0; id0++) {
				if (memorized_2d[id0][id1] == false)
				{
					memory_2d[id0][id1] = m_f(id0, id1, args...);
					memorized_2d[id0][id1] = true;
				};
			}
		}
	}
};


template<typename T, typename... ARGS>
automemory_2d<T, ARGS...> auto_2d(T(*f)(size_t, size_t, ARGS...), size_t size0, size_t size1) { return automemory_2d<T, ARGS...>(f, size0,size1); }

template<typename T, typename... ARGS>
automemory_2d<T, ARGS...> auto_2d(T(*f)(int, int, ARGS...), size_t size0, size_t size1) { return automemory_2d<T, ARGS...>(f, size0, size1); }

template<typename T, typename... ARGS>
automemory_2d<T, ARGS...> auto_2d(T(*f)(size_t, int, ARGS...), size_t size0, size_t size1) { return automemory_2d<T, ARGS...>(f, size0, size1); }

template<typename T, typename... ARGS>
automemory_2d<T, ARGS...> auto_2d(T(*f)(int, size_t, ARGS...), size_t size0, size_t size1) { return automemory_2d<T, ARGS...>(f, size0, size1); }


// ================================================================= End of Auto memoization section ==================================================






// ================================================================= Begin of Demo section ==================================================
int stack_levels = 0;
int max_stack_levels = 0;


//*************************************************************
// The recursive function - 1D Demo
//*************************************************************

//Step 0: rearrange your parameter, let the parameter (size_t/int/unsigned int) which will be used as index at the first positions.

//Step 1: To declare your recursive function with a NEW name at first;
long fib_new(int n, string hint);

//Step 2: To create the wrapper in the format: auto OLD_NAME=ram_id(NEW_NAME, size)
auto fib = auto_1d(fib_new, 1024); // fib: The old name; fib_new: the new name // Here the size of 1024 is too big. You may tailor.

//Step 3: to rename your function name, but not the references
long fib_new(int n, string hint) {
	stack_levels++;
	max_stack_levels = std::max(max_stack_levels, stack_levels);

	std::cout << n << hint;
	if (n <= 1)
	{
		stack_levels--;
		return 1;
	}

	long sum = fib(n - 1, hint) + fib(n - 2, hint); //!! Don't change the reference names here!!

	stack_levels--;

	return sum;
}



//*************************************************************
// The recursive function - 2D Demo
//*************************************************************

//      The original recursive function
//
// This code was digested from:
// https://www.geeksforgeeks.org/longest-common-subsequence-dp-4/

/* Returns length of LCS for X[0..m-1], Y[0..n-1] */
int lcs_recursive(char* X, char* Y, int m, int n)
{
	if (m == 0 || n == 0)
		return 0;
	if (X[m - 1] == Y[n - 1])
		return 1 + lcs_recursive(X, Y, m - 1, n - 1);
	else
		return std::max(lcs_recursive(X, Y, m, n - 1), lcs_recursive(X, Y, m - 1, n));
}


// Slightly Changed code

//Step 0: rearrange your parameter, let the parameter (size_t/int/unsigned int) which will be used as index at the first positions.

//Step 1: To declare your recursive function with a NEW name at first;

int lcs_new(int m, int n, char* X, char* Y);

//Step 2: To create the wrapper in the format: auto OLD_NAME=ram_id(NEW_NAME)
auto lcs = auto_2d(lcs_new, 128,128); // Here the size of 128s are too big. You may tailor.

//Step 3: to rename your function name, but not the references
/* Returns length of LCS for X[0..m-1], Y[0..n-1] */
int lcs_new(int m, int n, char* X, char* Y) 
{
	cout << "(" << m << "," << n << ") ";
	stack_levels++;
	max_stack_levels = std::max(max_stack_levels, stack_levels);

	if (m == 0 || n == 0) {
		stack_levels--;
		return 0;
	}
		
	if (X[m - 1] == Y[n - 1]) {
		auto sum = 1 + lcs(m - 1, n - 1, X, Y); //!! Don't change the reference names here!!
		stack_levels--;
		return sum;
	}
	else
	{
		auto sum= std::max(lcs(m, n - 1, X, Y), lcs(m - 1, n, X, Y)); //!! Don't change the reference names here!!
		stack_levels--;
		return sum;
	}
}


//   FYI:   The manual made iteration function
//
// This code was digested from:
// https://www.geeksforgeeks.org/longest-common-subsequence-dp-4/

//#include<bits/stdc++.h> 
///* Returns length of LCS for X[0..m-1], Y[0..n-1] */
//int lcs_loop(char* X, char* Y, int m, int n)
//{
//	int L[m + 1][n + 1];
//	int i, j;
//
//	/* Following steps build L[m+1][n+1] in bottom up fashion. Note
//	   that L[i][j] contains length of LCS of X[0..i-1] and Y[0..j-1] */
//	for (i = 0; i <= m; i++)
//	{
//		for (j = 0; j <= n; j++)
//		{
//			if (i == 0 || j == 0)
//				L[i][j] = 0;
//
//			else if (X[i - 1] == Y[j - 1])
//				L[i][j] = L[i - 1][j - 1] + 1;
//
//			else
//				L[i][j] = max(L[i - 1][j], L[i][j - 1]);
//		}
//	}
//
//	/* L[m][n] contains length of LCS for X[0..n-1] and Y[0..m-1] */
//	return L[m][n];
//}

//*************************************************************

int memorytest(void)
{
	auto i = 20;
	
	auto d = fib(i, " ");

	cout << endl << "Fib(" << i << "):" << d << "  with Max Stack Levels:" << max_stack_levels << endl;

	//
	// Without fill, the output is as the following:
	// 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
	// Fib(20):10946  with Max Stack Levels:20
	//

	cout << "******************" << endl;
	cout << " Now the memory has been filled." << endl;
	cout << "******************" << endl;

	max_stack_levels = 0;

	// fib.fill(i, " "); // This not needed now for the above code has filled.

	d = fib(i, "_");

	cout << endl << "Fib(" << i << "):" << d << "  with Max Stack Levels:" << max_stack_levels << endl<<endl;

	//
	// With fill, the output is as the following:
	// 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
	// Fib(20):10946  with Max Stack Levels:1
	//

	char X[] = "AGGTAB";
	char Y[] = "GXTXAYB";

	size_t m = strlen(X);
	size_t n = strlen(Y);

	stack_levels = 0;
	max_stack_levels = 0;

	printf("\n1st Run---  \n");
	auto result1 = lcs(m, n, X, Y);

	printf("\nLength of LCS is %d, with max stack is %d \n", result1, max_stack_levels);

	stack_levels = 0;
	max_stack_levels = 0;
	
	printf("\n2nd Run---  \n");
	auto result = lcs(m, n, X, Y);

	printf("Length of LCS is %d, with max stack  is %d \n", result, max_stack_levels);

	return 0;
}

int bestpractice(void)
{
	auto i = 20;

	fib.fill(i," "); // Highly suggested to fill at first.

	auto d = fib(i, " ");

	cout << endl << "Fib(" << i << "):" << d << "  with Max Stack Levels:" << max_stack_levels << endl;
	
	cout << "******************" << endl;
	cout << " Now the memory has been filled." << endl;
	cout << "******************" << endl;

	max_stack_levels = 0;

	// fib.fill(i, " "); // This not needed now for the above code has filled.

	d = fib(i, "_");

	cout << endl << "Fib(" << i << "):" << d << "  with Max Stack Levels:" << max_stack_levels << endl << endl;

	//
	// With fill, the output is as the following:
	// 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
	// Fib(20):10946  with Max Stack Levels:1
	//

	char X[] = "AGGTAB";
	char Y[] = "GXTXAYB";

	size_t m = strlen(X);
	size_t n = strlen(Y);

	stack_levels = 0;
	max_stack_levels = 0;

	lcs.fill01(m, n, X, Y); // Highly suggested to fill at first.

	printf("\n1st Run---  \n");
	auto result1 = lcs(m, n, X, Y);

	printf("\nLength of LCS is %d, with max stack is %d \n", result1, max_stack_levels);

	stack_levels = 0;
	max_stack_levels = 0;

	printf("\n2nd Run---  \n");
	auto result = lcs(m, n, X, Y);

	printf("Length of LCS is %d, with max stack  is %d \n", result, max_stack_levels);

	return 0;
}

int main() {
	bool test = false;

	// Due to the memory effect, you cannot run memorytest and bestpractice in the same run!
	if (test) {
		memorytest();
	}
	else {
		bestpractice();
	}
}

// ================================================================= End of Demo section ==================================================