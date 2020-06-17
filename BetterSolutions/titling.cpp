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