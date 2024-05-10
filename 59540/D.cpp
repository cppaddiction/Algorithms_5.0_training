#include <iostream>
#include <set>
#include <vector>
#include <climits>

using namespace std;

int main()
{
	vector<vector<int>> matrix;
	vector<int> row(8, 0);
	for (int i = 0; i < 8; i++) { matrix.push_back(row); }
	int n; cin >> n;
	for (int i = 0; i < n; i++)
	{
		int x, y; cin >> x >> y; matrix[x - 1][y - 1] = 1;
	}
	int ans = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (matrix[i][j] == 1)
			{
				int k = 4;
				if (j - 1 >= 0 && matrix[i][j-1] == 1)
				{
					k -= 1; ans -= 1;
				}
				if (j + 1 < 8 && matrix[i][j+1] == 1)
				{
					k -= 1; ans -= 1;
				}
				if (i - 1 >= 0 && matrix[i - 1][j] == 1)
				{
					k -= 1; ans -= 1;
				}
				if (i + 1 < 8 && matrix[i + 1][j] == 1)
				{
					k -= 1; ans -= 1;
				}
				ans += k;
				matrix[i][j] = -1;
			}
		}
	}
	cout << ans;
	return 0;
}