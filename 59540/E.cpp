#include <iostream>
#include <set>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

int main()
{
	vector<pair<int, pair<int64_t, int64_t>>> v;
	vector<pair<int, pair<int64_t, int64_t>>> rest;
	int n; cin >> n;
	for (int i = 0; i < n; i++)
	{
		int64_t up, down; cin >> up >> down;
		if (up - down > 0)
		{
			v.emplace_back(i + 1, make_pair(up, down));
		}
		else if (up - down == 0)
		{
			v.emplace_back(i + 1, make_pair(up, down));
			rest.emplace_back(i + 1, make_pair(up, down));
		}
		else
		{
			rest.emplace_back(i + 1, make_pair(up, down));
		}
	}
	
	auto f = [](const pair<int, pair<int64_t, int64_t>>& p1, const pair<int, pair<int64_t, int64_t>>& p2)
		{
			if (p1.second.first != p2.second.first)
			{
				return p1.second.first < p2.second.first;
			}
			else
			{
				return p1.second.second < p2.second.second;
			}
		};
	sort(v.begin(), v.end(), f);
	sort(rest.begin(), rest.end(), [](const pair<int, pair<int64_t, int64_t>>& p1, const pair<int, pair<int64_t, int64_t>>& p2) {return p1.second.first > p2.second.first; });
	int64_t ma = -INT_MAX;
	int64_t max_height = 0;
	for (const auto& item : v)
	{
		max_height += item.second.first;
		max_height -= item.second.second;
	}
	vector<int> result;
	int64_t max_height_first_block_modified;
	for (int i=0; i<v.size(); i++)
	{
		max_height_first_block_modified = max_height - v[i].second.first + v[i].second.second;
		if (max_height_first_block_modified + v[i].second.first > ma)
		{
			ma = max_height_first_block_modified + v[i].second.first;
			result.push_back(v[i].first);
		}
	}
	if (rest.size() > 0)
	{
		max_height += rest[0].second.first;
	}
	
	cout << max(max_height, ma) << '\n';

	bool first = ma > max_height ? true : false;

	if (first)
	{
		vector<int> erasing;
		for (int i = 0; i < rest.size(); i++)
		{
			if (rest[i].second.first == rest[i].second.second)
			{
				erasing.push_back(i);
			}
		}
		for (int i = 0; i < erasing.size(); i++)
		{
			rest.erase(rest.begin() + erasing[i]);
		}

		for (const auto& item : v)
		{
			if (item.first != result[result.size() - 1])
			{
				cout << item.first << ' ';
			}
		}

		cout << result[result.size() - 1] << ' ';

		for (const auto& item : rest)
		{
			cout << item.first << ' ';
		}
	}
	else
	{
		vector<int> erasing;
		for (int i = 0; i < v.size(); i++)
		{
			if (v[i].second.first == v[i].second.second)
			{
				erasing.push_back(i);
			}
		}
		for (int i = 0; i < erasing.size(); i++)
		{
			v.erase(v.begin() + erasing[i]);
		}

		for (const auto& item : v)
		{
			cout << item.first << ' ';
		}

		for (const auto& item : rest)
		{
			cout << item.first << ' ';
		}
	}

	
	return 0;
}
//сложить только положительные разности пар
//максимальная высота - макс(полож разности) - отсортированные + макс(оставшиеся)
//или
/*
6
822889311 446755913
715477619 181424399
61020590 573085537
480845266 448565595
135599877 389312924
160714711 449656269
*/