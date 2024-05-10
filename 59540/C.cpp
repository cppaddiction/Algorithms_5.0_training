#include <iostream>
#include <set>
#include <vector>
#include <climits>

using namespace std;

int main()
{
	int ma = -INT_MAX;
	int s = 0;
	int n; cin >> n;
	for (int i = 0; i < n; i++)
	{
		int x; cin >> x; s += x; if (x > ma) { ma = x; }
	}
	s -= ma;
	if (ma - s > 0)
	{
		cout << ma - s;
	}
	else
	{
		cout << ma + s;
	}
	return 0;
}