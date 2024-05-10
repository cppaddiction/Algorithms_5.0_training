#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int64_t collides(int64_t speed, int64_t k)
{
	if (speed <= k) { return 0; }
	if (speed % k == 0) { return speed / k - 1; }
	else { return speed / k; }
}

int64_t spin(int dir, const vector<int>& wheel, int64_t collisions)
{
	int64_t delta = collisions % wheel.size();
	if (delta == 0) { return wheel[0]; }
	else
	{
		if (dir == 0)
		{
			return wheel[delta];
		}
		else
		{
			return wheel[wheel.size() - 1 - (delta - 1)];
		}
	}
}

int main()
{
	int n; cin >> n;
	vector<int> wheel;
	for (int i = 0; i < n; i++)
	{
		int x; cin >> x;
		wheel.push_back(x);
	}
	int64_t a, b, k;
	cin >> a >> b >> k;

	int ma = -INT_MAX;

	auto lb = collides(a, k);
	auto rb = collides(b, k);
	if (rb - lb > wheel.size()) { cout << *max_element(wheel.begin(), wheel.end()); }
	else
	{
		for (auto i = lb; i <= rb; i++)
		{
			auto res = max(spin(0, wheel, i), spin(1, wheel, i));
			if (res > ma) { ma = res; }
		}
		cout << ma;
	}
	return 0;
}