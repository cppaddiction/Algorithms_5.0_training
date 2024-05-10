#include <vector>
#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

void display(const vector<vector<char>>& matrix)
{
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].size(); j++)
		{
			cout << matrix[i][j];
		}
		cout << '\n';
	}
}

void change_matrix_if_three(const pair<pair<int, int>, pair<int, int>>& found, const pair<pair<int, int>, pair<int, int>>& found_another_first, const pair<pair<int, int>, pair<int, int>>& found_another_third, vector<vector<char>>& matrix)
{
	for (int i = found.first.first; i < found_another_first.first.first; i++)
	{
		for (int j = found.first.second; j <= found.second.second; j++)
		{
			matrix[i][j] = 'a';
		}
	}

	for (int i = found_another_first.first.first; i <= found_another_first.second.first; i++)
	{
		for (int j = found_another_first.first.second; j <= found_another_third.second.second; j++)
		{
			matrix[i][j] = 'b';
		}
	}
}

void change_matrix_if_two(const pair<pair<int, int>, pair<int, int>>& rect_one, const pair<pair<int, int>, pair<int, int>>& rect_two, vector<vector<char>>& matrix)
{
	for (int i = rect_one.first.first; i <= rect_one.second.first; i++)
	{
		for (int j = rect_one.first.second; j <= rect_one.second.second; j++)
		{
			matrix[i][j] = 'a';
		}
	}

	for (int i = rect_two.first.first; i <= rect_two.second.first; i++)
	{
		for (int j = rect_two.first.second; j <= rect_two.second.second; j++)
		{
			matrix[i][j] = 'b';
		}
	}
}

bool change_matrix_if_one(const pair<pair<int, int>, pair<int, int>>& rect_one, vector<vector<char>>& matrix)
{
	if (rect_one.second.first - rect_one.first.first == 0 && rect_one.second.second - rect_one.first.second == 0) { return false; }
	else if (rect_one.second.first - rect_one.first.first == 0)
	{
		matrix[rect_one.first.first][rect_one.first.second] = 'b';
		for (int j = rect_one.first.second + 1; j <= rect_one.second.second; j++)
		{
			matrix[rect_one.first.first][j] = 'a';
		}
	}
	else if (rect_one.second.second - rect_one.first.second == 0)
	{
		matrix[rect_one.first.first][rect_one.first.second] = 'b';
		for (int i = rect_one.first.first + 1; i <= rect_one.second.first; i++)
		{
			matrix[i][rect_one.first.second] = 'a';
		}
	}
	else
	{
		for (int j = rect_one.first.second; j <= rect_one.second.second; j++)
		{
			matrix[rect_one.first.first][j] = 'b';
		}
		for (int i = rect_one.first.first + 1; i <= rect_one.second.first; i++)
		{
			for (int j = rect_one.first.second; j <= rect_one.second.second; j++)
			{
				matrix[i][j] = 'a';
			}
		}
	}
	return true;
}

pair<pair<int, int>, pair<int, int>> find(const pair<int, int>& b, const pair<int, int>& e, const vector<vector<char>>& matrix, int m, int n)
{
	pair<pair<int, int>, pair<int, int>> result;

	result.first.first = -1;
	result.first.second = -1;
	result.second.first = -1;
	result.second.second = -1;

	if (!(0 <= b.first && b.first <= m - 1 && 0 <= e.first && e.first <= m - 1 && 0 <= b.second && b.second <= n - 1 && 0 <= e.second && e.second <= n - 1))
	{
		return result;
	}
	
	for (int i = b.first; i <= e.first; i++)
	{
		for (int j = b.second; j <= e.second; j++)
		{
			if (matrix[i][j] == '#')
			{
				result.first.first = i;
				result.first.second = j;

				int width = 0;
				while (j <= e.second && matrix[i][j] == '#')
				{
					width++;
					j++;
				}
				j = result.first.second;

				int height = 0;
				while (i <= e.first && matrix[i][j] == '#')
				{
					bool flag = true;
					for (int k = 0; k < width; k++)
					{
						if (matrix[i][j + k] != '#')
						{
							flag = false;
						}
					}
					if (flag)
					{
						height++;
						i++;
					}
					else
					{
						result.second.first = result.first.first + height - 1;
						result.second.second = result.first.second + width - 1;
						return result;
					}
				}

				result.second.first = result.first.first + height - 1;
				result.second.second = result.first.second + width - 1;
				return result;
			}
		}
	}

	return result;
}

int main()
{
	int area = 0;
	vector<vector<char>> matrix;

	int m, n;
	cin >> m >> n;
	for (int i = 0; i < m; i++)
	{
		vector<char> temp;
		for (int j = 0; j < n; j++)
		{
			char x; cin >> x; temp.push_back(x); if (x == '#') { area++; }
		}
		matrix.push_back(temp);
	}

	auto found = find(make_pair(0, 0), make_pair(m-1, n-1), matrix, m, n);
	if (found.first.first != -1 && found.first.second != -1 && found.second.first != -1 && found.second.second != -1)
	{
		if ((found.second.first - found.first.first + 1) * (found.second.second - found.first.second + 1) == area)
		{
			auto result = change_matrix_if_one(found, matrix);
			if (result)
			{
				cout << "YES\n";
				display(matrix);
				return 0;
			}
			else
			{
				cout << "NO\n";
				return 0;
			}
		}
		else
		{
			auto found_another_first = find(make_pair(found.first.first + 1, 0), make_pair(m - 1, found.first.second - 1), matrix, m, n);
			auto found_another_second = find(make_pair(found.second.first + 1, found.first.second), make_pair(m - 1, found.second.second), matrix, m, n);
			auto found_another_third = find(make_pair(found.first.first, found.second.second + 1), make_pair(m - 1, n - 1), matrix, m, n);
			auto found_another_fourth = find(make_pair(found.second.first + 1, 0), make_pair(m - 1, n - 1), matrix, m, n);
			if (found_another_first.first.first != -1 && found_another_first.first.second != -1 && found_another_first.second.first != -1 && found_another_first.second.second != -1)
			{
				if ((found.second.first - found.first.first + 1) * (found.second.second - found.first.second + 1) + (found_another_first.second.first - found_another_first.first.first + 1) * (found_another_first.second.second - found_another_first.first.second + 1) == area)
				{
					change_matrix_if_two(found, found_another_first, matrix);
					cout << "YES\n";
					display(matrix);
					return 0;
				}
			}
			if (found_another_second.first.first != -1 && found_another_second.first.second != -1 && found_another_second.second.first != -1 && found_another_second.second.second != -1)
			{
				if ((found.second.first - found.first.first + 1) * (found.second.second - found.first.second + 1) + (found_another_second.second.first - found_another_second.first.first + 1) * (found_another_second.second.second - found_another_second.first.second + 1) == area)
				{
					change_matrix_if_two(found, found_another_second, matrix);
					cout << "YES\n";
					display(matrix);
					return 0;
				}
			}
			if (found_another_third.first.first != -1 && found_another_third.first.second != -1 && found_another_third.second.first != -1 && found_another_third.second.second != -1)
			{
				if ((found.second.first - found.first.first + 1) * (found.second.second - found.first.second + 1) + (found_another_third.second.first - found_another_third.first.first + 1) * (found_another_third.second.second - found_another_third.first.second + 1) == area)
				{
					change_matrix_if_two(found, found_another_third, matrix);
					cout << "YES\n";
					display(matrix);
					return 0;
				}
			}
			if (found_another_fourth.first.first != -1 && found_another_fourth.first.second != -1 && found_another_fourth.second.first != -1 && found_another_fourth.second.second != -1)
			{
				if ((found.second.first - found.first.first + 1) * (found.second.second - found.first.second + 1) + (found_another_fourth.second.first - found_another_fourth.first.first + 1) * (found_another_fourth.second.second - found_another_fourth.first.second + 1) == area)
				{
					change_matrix_if_two(found, found_another_fourth, matrix);
					cout << "YES\n";
					display(matrix);
					return 0;
				}
			}
			if (found_another_first.first.first != -1 && found_another_first.first.second != -1 && found_another_first.second.first != -1 && found_another_first.second.second != -1 &&
				found_another_third.first.first != -1 && found_another_third.first.second != -1 && found_another_third.second.first != -1 && found_another_third.second.second != -1 &&
				found_another_second.first.first == -1 && found_another_second.first.second == -1 && found_another_second.second.first == -1 && found_another_second.second.second == -1 &&
				found_another_fourth.first.first == -1 && found_another_fourth.first.second == -1 && found_another_fourth.second.first == -1 && found_another_fourth.second.second == -1)
			{
				if ((found.second.first - found.first.first + 1) * (found.second.second - found.first.second + 1) + (found_another_first.second.first - found_another_first.first.first + 1) * (found_another_first.second.second - found_another_first.first.second + 1) + (found_another_third.second.first - found_another_third.first.first + 1) * (found_another_third.second.second - found_another_third.first.second + 1) == area)
				{
					change_matrix_if_three(found, found_another_first, found_another_third, matrix);
					cout << "YES\n";
					display(matrix);
					return 0;
				}
			}
			cout << "NO\n";
		}
	}
	else
	{
		cout << "NO\n";
	}
	return 0;
}