#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>

using namespace std;

int main()
{
	int n; cin >> n;
	map<int, int> m;
	for (int i = 0; i < n; i++)
	{
		int x; cin >> x;
		m[x] += 1;
	}
	set<int> result;
	for (auto it = m.begin(); it != m.end(); it++)
	{
		result.insert(n - it->second);
		try
		{
			result.insert(n - (it->second + m.at(it->first + 1)));
			
		}
		catch (...)
		{

		}
		try
		{
			result.insert(n - (it->second + m.at(it->first - 1)));

		}
		catch (...)
		{

		}
	}
	if (result.size() == 0)
	{
		cout << n - 1;
	}
	else
	{
		cout << *result.begin();
	}
	return 0;
}