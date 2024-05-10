#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>

using namespace std;

int main()
{
	int n, k; cin >> n >> k;
	map<int, vector<int>> m;
	for (int i = 0; i < n; i++)
	{
		int x; cin >> x;
		if (m[x].size() == 0)
		{
			m[x].push_back(i);
		}
		else
		{
			m[x].push_back(i - m[x][m[x].size() - 1]);
		}
	}
	for (auto it = m.begin(); it != m.end(); it++)
	{
		int s = it->second.size();
		if (s > 1)
		{
			for (int i = 1; i < s; i++)
			{
				if (it->second[i] <= k)
				{
					cout << "YES";
					return 0;
				}
			}
		}
	}
	cout << "NO";
	return 0;
}