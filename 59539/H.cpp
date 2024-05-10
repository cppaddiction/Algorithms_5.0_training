#include <iostream>
#include <cfloat>

using namespace std;

int main()
{
	int64_t L, x1, v1, x2, v2;
	cin >> L >> x1 >> v1 >> x2 >> v2;

	if (x1 == x2) // same point at start
	{
		cout << "yes" << '\n';
		cout << 0;
		return 0;
	}
	if (x1 < x2)
	{
		if (x1 == L - x2) // same distance at start
		{
			cout << "yes" << '\n';
			cout << 0;
			return 0;
		}
	}
	if (x1 > x2)
	{
		if (x2 == L - x1) // same distance at start
		{
			cout << "yes" << '\n';
			cout << 0;
			return 0;
		}
	}
	if (v1 == 0 && v2 == 0) // zero speed at start and not same distance
	{
		cout << "no";
		return 0;
	}

	int64_t relative_speed;

	if (v1 == 0)
	{
		relative_speed = abs(v2);
	}
	if (v2 == 0)
	{
		relative_speed = abs(v1);
	}
	if (v1 * v2 < 0)
	{
		relative_speed = abs(v1) + abs(v2);
	}
	if (v1 * v2 > 0)
	{
		relative_speed = abs(v1 - v2);
	}

	double meeting_time = DBL_MAX;

	if (x1 < x2)
	{
		if (v1 >= 0 && v2 <= 0)
		{
			meeting_time = abs(x1 - x2) * 1.0 / relative_speed;
		}
		if (v1 <= 0 && v2 >= 0)
		{
			meeting_time = (L - abs(x1 - x2)) * 1.0 / relative_speed;
		}
		if (v1 >= 0 && v2 >= 0)
		{
			if (v1 != v2)
			{
				if (v1 > v2)
				{
					meeting_time = abs(x1 - x2) * 1.0 / relative_speed;
				}
				if (v1 < v2)
				{
					meeting_time = (L - abs(x1 - x2)) * 1.0 / relative_speed;
				}
			}
		}
		if (v1 <= 0 && v2 <= 0)
		{
			if (v1 != v2)
			{
				if (abs(v1) > abs(v2))
				{
					meeting_time = (L - abs(x1 - x2)) * 1.0 / relative_speed;
				}
				if (abs(v1) < abs(v2))
				{
					meeting_time = abs(x1 - x2) * 1.0 / relative_speed;
				}
			}
		}
	}
	if (x1 > x2)
	{
		if (v1 >= 0 && v2 <= 0)
		{
			meeting_time = (L - abs(x1 - x2)) * 1.0 / relative_speed; 
		}
		if (v1 <= 0 && v2 >= 0)
		{
			meeting_time = abs(x1 - x2) * 1.0 / relative_speed;
		}
		if (v1 >= 0 && v2 >= 0)
		{
			if (v1 != v2)
			{
				if (v1 > v2)
				{
					meeting_time = (L - abs(x1 - x2)) * 1.0 / relative_speed; 
				}
				if (v1 < v2)
				{
					meeting_time = abs(x1 - x2) * 1.0 / relative_speed;
				}
			}
		}
		if (v1 <= 0 && v2 <= 0)
		{
			if (v1 != v2)
			{
				if (abs(v1) > abs(v2))
				{
					meeting_time = abs(x1 - x2) * 1.0 / relative_speed; 
				}
				if (abs(v1) < abs(v2))
				{
					meeting_time = (L - abs(x1 - x2)) * 1.0 / relative_speed;
				}
			}
		}
	}

	double center_coord = 0;

	if (x1 < x2)
	{
		center_coord = x1 + abs(x1 - x2) * 1.0 / 2;
	}
	if (x1 > x2)
	{
		center_coord = x2 + abs(x1 - x2) * 1.0 / 2;
	}

	double half = L * 1.0 / 2;
	double center_time = DBL_MAX;

	if (v1 >= 0 && v2 <= 0)
	{
		if ((v1 < v2 && center_coord > half) || (v1 > v2 && center_coord < half))
		{
			center_time = abs(center_coord - half) * 1.0 / (abs(v1 - v2) * 1.0 / 2);
			if (!(center_time < abs(x1 - half) * 1.0 / v1 && center_time < abs(x2 - half) / v2))
			{
				center_time = DBL_MAX;
			}
		}
	}
	if (v1 <= 0 && v2 >= 0)
	{
		if ((v1 < v2 && center_coord < half) || (v1 > v2 && center_coord > half))
		{
			center_time = abs(center_coord - half) * 1.0 / (abs(v1 - v2) * 1.0 / 2);
			if (!(center_time < abs(x1 - half) * 1.0 / v1 && center_time < abs(x2 - half) / v2))
			{
				center_time = DBL_MAX;
			}
		}
	}
	if (v1 >= 0 && v2 >= 0)
	{
		if (center_coord < half && center_coord > 0)
		{
			center_time = abs(center_coord - half) * 1.0 / (abs(v1 + v2) * 1.0 / 2);
		}
		if (center_coord > half && center_coord < L)
		{
			center_time = abs(center_coord - L) * 1.0 / (abs(v1 + v2) * 1.0 / 2);
		}
	}
	if (v1 <= 0 && v2 <= 0)
	{
		if (center_coord < half && center_coord > 0)
		{
			center_time = abs(center_coord) * 1.0 / (abs(v1 + v2) * 1.0 / 2);
		}
		if (center_coord > half && center_coord < L)
		{
			center_time = abs(center_coord - half) * 1.0 / (abs(v1 + v2) * 1.0 / 2);
		}
	}

	cout.precision(100);
	cout << "yes" << '\n';
	cout << min(meeting_time, center_time);

	return 0;
}