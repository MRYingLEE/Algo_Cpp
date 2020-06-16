# A kind of 2-step dynamic programming algorithm

There is a typical algorithm problem (such as Maximum subarray problem https://en.wikipedia.org/wiki/Maximum_subarray_problem ) to find an optimal subsequence in a sequence. A brute force method for such a kind of problem has a time complexity of O(n^2). Of course, there are some smart methods by dynamic programming (DP), which only costs O(n). 

But, such a kind of smart method is not easy to find and understand. Here I want to show my thoughts to understand this kind of method and also the structure of such a kind of DP.

## Maximum subarray problem
In computer science, the maximum sum subarray problem is the task of finding a contiguous subarray with the largest sum, within a given one-dimensional array A[1...n] of numbers. 
For example, for the array of values [−2, 1, −3, 4, −1, 2, 1, −5, 4], the contiguous subarray with the largest sum is [4, −1, 2, 1], with sum 6.

There is a Kadane's algorithm, which can be expressed by Python code as:

def max_subarray(numbers):
    """Find the largest sum of any contiguous subarray."""
    best_sum = 0  # or: float('-inf')
    current_sum = 0
    for x in numbers:
        current_sum = max(0, current_sum + x)
        best_sum = max(best_sum, current_sum)
    return best_sum

The runtime complexity of Kadane's algorithm is O(n).

## In the view of DP

Because of the way this algorithm uses optimal substructures (the maximum subarray ending at each position is calculated in a simple way from a related but smaller and overlapping subproblem: the maximum subarray ending at the previous position) this algorithm can be viewed as a simple/trivial example of DP.

It is very smart, but not intuitive.

Intuitively, by using DP, we have a formula as

dp(n+1)= f(dp(n), dp(n-1),...dp(0))

But, obviously, if we define
dp(n): the largest sum for the array A[1..n]

We cannot find the function f.

A sequence has the properties of begin, end and length. 

Option A: If we define
	dp(n):the largest sum for the subsequence ending at n.

It’s easy to find
	dp(n+1)= max(dp(n), dp(n)+A[n])

Option B: If we define
	dp(n): the largest sum for the subsequence starting at n.

It’s easy to find
	dp(n)= max(dp(n+1), dp(n+1)+A[n])
It works, but not intuitive.

Option C: If we define 
	dp(n):the largest sum for the subsequence with length n.

It’s hard to find a relation between dp(n+1) and dp(n).

So that to define an ending based function is the natural way to go.


Of course, dp(n) is not the answer.
	answer= max(dp(n), dp(n-1),...dp(0)).

So that in the view of the DP, the solution structure is:
	dp(n+1)= f(dp[n-1], dp[n-2],...dp[0])
	answer(n+1) = g(answer([n], answer[n-1],...answer[0]) with answer[0]=h(dp[0])

We may call this kind of DP as 2-step DP.

## Other 2-steps DP problem

A lot of hard DP problems can be solved by 2-step DP, such as:

Longest Increasing Subsequence (https://www.geeksforgeeks.org/longest-increasing-subsequence-dp-3/)
Maximum Length Chain of Pairs (https://www.geeksforgeeks.org/maximum-length-chain-of-pairs-dp-20/) 


Besides popular 1d and 2d DP methods, 2-step DP ones can be used to solve more hard problems. 
