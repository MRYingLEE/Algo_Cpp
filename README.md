# Algo_Cpp
Some ideas, code snippets about Algorithm design and implementation, especially for C++. The primary topics include Automatic Memoization and Circular Array.

# Circular Array
Technically, Circular Array is the same as circular buffer.

According to https://en.wikipedia.org/wiki/Circular_buffer:
A circular buffer, circular queue, cyclic buffer or ring buffer is a data structure that uses a single, fixed-size buffer as if it were connected end-to-end. This structure lends itself easily to buffering data streams.

Circular Array is intended to extend the features of std::array:
1. To support negative index, such as floor -3 to 80.
2. To support assigned index range, such as year 1989-2019.
3. To save space for some recursive situation. For example, if you want to calculate Fibonacci numbes of the 1000th, but you don't need to save the first 999 data. You may use a circular array with a real size of 2 to calculate.

# Automatic Memoization
According to https://en.wikipedia.org/wiki/Memoization:

In computing, memoization or memoisation is an optimization technique used primarily to speed up computer programs by storing the results of expensive function calls and returning the cached result when the same inputs occur again. Memoization has also been used in other contexts (and for purposes other than speed gains), such as in simple mutually recursive descent parsing[1]. Although related to caching, memoization refers to a specific case of this optimization, distinguishing it from forms of caching such as buffering or page replacement. In the context of some logic programming languages, memoization is also known as tabling.[2].

## Objectives: 
  Competitive Oriented. This is not a general automatic Memoization solution or framework. Instead, this is for rush coding. 
  
  1. The syntax should be simple, compatible with C++ 11. 
  
  2. A non-recursive function is not needed to be modified.
  
  3. The recursive function code is not needed to be modified greatly.
  
  4. The speed is the top priority.
    
  5. Best practice usage demo is provided.
  
## Logical

1. Vanilla version: corresponding vectors will be used to store function values. (Implemented!)

2. Rolling version: An advanced vector with a rolling window and assigned offset will be used to store.
  This is to save space. Just in case. (In future!)

3. We use functors to extend the original recursive function code.

## It's easy to use for non-recursive functions by wrapping

just write:
```c++
auto new_name=auto_1d(old_name);
```
Or
```c++
auto new_name=auto_2d(old_name);
```
And make all references to the new name.

### OR a tricky way, to rename the function declare 
```c++
auto old_name=auto_1d(renamed_name);
```

Or
```c++
auto old_name=auto_2d(renamed_name);
```

Thereafter, no references are needed to be renamed.

## Usage in rush coding for RECURSIVE function

1. Write your recursive function code, which is intuitive.

  Make sure your function is immutable. In other words, the same parameters always return the same value;
    
2. After successful running, copy the following code snippet BEFORE your recursive function.

```C++
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




```

3. Change slightly the functor variable declare section if needed.

### The demo of 1D

```c++

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



```

### The demo of 2D

```c++

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

```
## Tested by VS 2019 with C++14, www.cpp.sh with C++11/C++14.
