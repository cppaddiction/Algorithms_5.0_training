#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

int main()
{
	int n; cin >> n;
	vector<set<string>> v;
	for (int i = 0; i < n; i++)
	{
		set<string> temp;
		int k; cin >> k;
		for (int i = 0; i < k; i++)
		{
			string str; cin >> str; temp.insert(str);
		}
		v.push_back(temp);
	}
	set<string> res = v[0];
	for (int i = 1; i < n; i++)
	{
		vector<string> temp;
		set_intersection(res.begin(), res.end(), v[i].begin(), v[i].end(), std::back_inserter(temp));
		res = set<string>(temp.begin(), temp.end());
	}
	cout << res.size() << '\n';
	for (auto it = res.begin(); it != res.end(); it++)
	{
		cout << *it << ' ';
	}
	return 0;
}