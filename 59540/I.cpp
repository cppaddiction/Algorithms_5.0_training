#include <vector>
#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

vector<pair<int, int>> get_empty_cells(int n, int i, const vector<pair<int, int>>& ships_in_col)
{
	vector<pair<int, int>> empty_cells;
	vector<pair<int, int>> col_cells(n);
	for (const auto& ship : ships_in_col)
	{
		col_cells[ship.first - 1] = ship;
	}
	for (int ind = 0; ind < n; ind++)
	{
		if (col_cells[ind].first == 0 && col_cells[ind].second == 0)
		{
			empty_cells.emplace_back(ind + 1, i);
		}
	}
	return empty_cells;
}

pair<vector<pair<int, int>>, vector<pair<int, int>>> get_ships(int i, const vector<pair<int, int>>& data)
{
	vector<pair<int, int>> ships_in_col, other_ships;
	for (const auto& ship : data)
	{
		if (ship.second == i)
		{
			ships_in_col.push_back(ship);
		}
		else
		{
			other_ships.push_back(ship);
		}
	}
	return make_pair(ships_in_col, other_ships);
}

int solve(int n, const vector<pair<int, int>>& data)
{
	set<int> moves_required;
	for (int i = 1; i <= n; i++)
	{
		int s = 0;
		auto ships = get_ships(i, data);
		auto ships_in_col = ships.first;
		auto other_ships = ships.second;
		auto empty_cells = get_empty_cells(n, i, ships_in_col);
		for (int j = 0; j < empty_cells.size(); j++)
		{
			s += (abs(empty_cells[j].first - other_ships[j].first) + abs(empty_cells[j].second - other_ships[j].second));
		}
		moves_required.insert(s);
	}
	return *moves_required.begin();
}

int main()
{
	vector<pair<int, int>> data;
	int n; cin >> n;
	for (int i = 0; i < n; i++)
	{
		int row, col; cin >> row >> col;
		data.emplace_back(row, col);
	}
	sort(data.begin(), data.end(), [](const pair<int, int>& p1, const pair<int, int>& p2) {return p1.second < p2.second; });
	auto res1 = solve(n, data);
	sort(data.begin(), data.end(), [](const pair<int, int>& p1, const pair<int, int>& p2) {return p1.first< p2.first; });
	auto res2 = solve(n, data);
	cout << min(res1, res2);
	return 0;
}