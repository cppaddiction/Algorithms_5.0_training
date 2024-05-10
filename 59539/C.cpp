#include <iostream>

using namespace std;

unsigned long long f(unsigned long long x)
{
	if (x == 0)
	{
		return 0;
	}
	else if (x == 1)
	{
		return 1;
	}
	else if (x == 2)
	{
		return 2;
	}
	else if (x == 3)
	{
		return 2;
	}
	else if (x == 4)
	{
		return 1;
	}
	else
	{
		unsigned long long tabs = x / 4;
		int rest = x % 4;
		if (rest == 0)
		{
			return tabs;
		}
		else if (rest == 1)
		{
			return tabs + 1;
		}
		else if (rest == 2)
		{
			return tabs + 2;
		}
		else if (rest == 3)
		{
			return tabs + 2;
		}
	}
}
int main()
{
	int n;
	cin >> n;
	unsigned long long s = 0;
	for (int i = 0; i < n; i++)
	{
		unsigned long long x; cin >> x; s += f(x);
	}
	cout << s;
	return 0;
}