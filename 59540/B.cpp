#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main()
{
	set<int> storage;

	vector<int> prices;
	int n, k; cin >> n >> k;

	for (int i = 0; i < n; i++)
	{
		int x; cin >> x; prices.push_back(x);
	}

	for (int i = 0; i < n; i++)
	{
		if (i + k < n)
		{
			for (int j = i; j <= i + k; j++)
			{
				storage.insert(prices[j]-prices[i]);
			}
		}
		else
		{
			for (int j = i; j < n; j++)
			{
				storage.insert(prices[j] - prices[i]);
			}
		}
	}

	if (storage.size() > 0)
	{
		auto x = *next(storage.end(), -1);
		if (x >= 0)
		{
			cout << x;
		}
		else
		{
			cout << 0;
		}
	}
	else
	{
		cout << 0;
	}

	return 0;
}