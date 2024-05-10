#include <iostream>
#include <climits>

using namespace std;

int main()
{
	int xmi = INT_MAX;
	int xma = -INT_MAX;
	int ymi = INT_MAX;
	int yma = -INT_MAX;
	int k; cin >> k;
	for (int i = 0; i < k; i++)
	{
		int x, y; cin >> x >> y;
		if (x > xma)
		{
			xma = x;
		}
		if (x < xmi)
		{
			xmi = x;
		}
		if (y > yma)
		{
			yma = y;
		}
		if (y < ymi)
		{
			ymi = y;
		}
	}
	cout << xmi << ' ' << ymi << ' ' << xma << ' ' << yma;
	return 0;
}