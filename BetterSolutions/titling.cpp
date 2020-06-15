#include <iostream>
#include <string>
#include <algorithm>
#include <array>

using namespace std;

const int i_columns = 7;
const int i_rows = 4;

using state = array < array<int, i_columns>, i_rows>;
int checked_states = 0;

int count_by_state(state state_current) {
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
						state state_new;
						std::copy(&state_current[0][0], &state_current[0][0] + i_rows * i_columns, &state_new[0][0]);

						state_new[i][j] = 1;
						state_new[i][j + 1] = 1;

						count_right = count_by_state(state_new);
					}
				}

				if (i < i_rows - 1) //down
				{
					if (state_current[i + 1][j] == 0) {
						state state_new;
						std::copy(&state_current[0][0], &state_current[0][0] + i_rows * i_columns, &state_new[0][0]);
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

int main()
{
	state  state_0 = { 0 };

	int counts = count_by_state(state_0);

	std::cout << counts << endl;
	std::cout << checked_states << endl;

	return 0;
}