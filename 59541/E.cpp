#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>

using namespace std;

int main()
{
	vector<set<int>> v(3);
	for (int i = 0; i < 3; i++)
	{
		set<int> s;
		int k; cin >> k;
		for (int j = 0; j < k; j++)
		{
			int x; cin >> x; s.insert(x);
		}
		v[i] = s;
	}
	vector<int> res1;
	vector<int> res2;
	vector<int> res3;
	set_intersection(v[0].begin(), v[0].end(), v[1].begin(), v[1].end(), back_inserter(res1));
	set_intersection(v[0].begin(), v[0].end(), v[2].begin(), v[2].end(), back_inserter(res2));
	set_intersection(v[1].begin(), v[1].end(), v[2].begin(), v[2].end(), back_inserter(res3));
	set<int> result;
	for (const auto& item : res1)
	{
		result.insert(item);
	}
	for (const auto& item : res2)
	{
		result.insert(item);
	}
	for (const auto& item : res3)
	{
		result.insert(item);
	}
	for (auto it=result.begin(); it!=result.end(); it++)
	{
		cout << *it << ' ';
	}
	return 0;
}