#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
	vector<int> v;

	int n; cin >> n;
	for (int i = 0; i < n; i++)
	{
		int x; cin >> x; v.push_back(x);
	}

	int i = 0;
	while (v[i] % 2 == 0) { i++; }
	if (i == v.size() - 1)
	{
		string s(n - 1, '+');
		cout << s;
	}
	else
	{
		int j = i + 1;
		bool even_found = false;
		while (j != v.size())
		{
			if (v[j++] % 2 == 0) { even_found = true; break; }
		}
		string head(i, '+');
		char c;
		if (even_found)
		{
			c = '+';
		}
		else
		{
			c = 'x';
		}
		string tail(v.size() - 1 - i - 1, 'x');
		string result = head + c + tail;
		cout << result;
	}
	return 0;
}