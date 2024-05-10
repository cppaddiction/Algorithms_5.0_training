#include <iostream>
#include <set>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

int64_t calc_ans(const vector<pair<int64_t, pair<int, int>>>& data, int forb_i, int forb_j)
{
	int64_t ma = -INT_MAX;
	for (int i = 0; i < data.size(); i++)
	{
		if (data[i].first > ma && data[i].second.first != forb_i && data[i].second.second != forb_j)
		{
			return data[i].first;
		}
	}
	return ma;
}

int main()
{
	//n races m classes
	vector<pair<int64_t, pair<int, int>>> data;
	int n, m; cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			int64_t x; cin >> x;
			data.emplace_back(x, make_pair(i, j));
		}
	}

	sort(data.begin(), data.end(), [](const pair<int64_t, pair<int, int>>& lhs, const pair<int64_t, pair<int, int>>& rhs) {return lhs.first > rhs.first; });
	
	vector<pair<int64_t, pair<int, int>>> possible_vars;
	auto ma = data[0].first;
	int i = 0;
	while (data[i].first == ma) { possible_vars.push_back(data[i]); i++; }

	vector<pair<int64_t, pair<int, int>>> possible_outcomes;

	for (const auto& var : possible_vars)
	{
		auto first_var_race = var.second.first;

		int k = 0;
		while (data[k].second.first == first_var_race) { k++; }

		auto first_var_class = data[k].second.second;



		auto second_var_class = var.second.second;

		k = 0;
		while (data[k].second.second == second_var_class) { k++; }

		auto second_var_race = data[k].second.first;

		auto ans_first = calc_ans(data, first_var_race, first_var_class);
		auto ans_second = calc_ans(data, second_var_race, second_var_class);

		if (ans_first < ans_second)
		{
			possible_outcomes.emplace_back(ans_first, make_pair(first_var_race, first_var_class));
		}
		else
		{
			possible_outcomes.emplace_back(ans_second, make_pair(second_var_race, second_var_class));
		}
	}

	sort(possible_outcomes.begin(), possible_outcomes.end(), [](const pair<int64_t, pair<int, int>>& lhs, const pair<int64_t, pair<int, int>>& rhs) {return lhs.first < rhs.first; });

	cout << possible_outcomes[0].second.first + 1 << ' ' << possible_outcomes[0].second.second + 1;

	return 0;
}