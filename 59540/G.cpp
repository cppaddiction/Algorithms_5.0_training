#include <iostream>
#include <vector>

using namespace std;

vector<int> solve(const vector<int>& data)
{
	vector<int> segment_sizes;

	int j = 0;
	while (j < data.size())
	{
		int segment_first_val = data.at(j);
		int segment_length = 1;
		if (segment_first_val == 1)
		{
			segment_sizes.push_back(segment_length);
			j += 1;
		}
		else
		{
			int mi = data.at(j);
			while (mi >= segment_length && j < data.size())
			{
				j += 1;
				segment_length += 1;
				try
				{
					if (data.at(j) < mi) { mi = data.at(j); }
				}
				catch (...)
				{
					break;
				}
			}
			segment_sizes.push_back(segment_length-1);
		}
	}

	return segment_sizes;
}



int main()
{
	int n; cin >> n;
	for (int i = 0; i < n; i++)
	{
		int k; cin >> k;
		vector<int> data;
		for (int j = 0; j < k; j++)
		{
			int x; cin >> x; data.push_back(x);
		}

		auto result = solve(data);
		cout << result.size() << '\n';
		for (int j = 0; j < result.size(); j++)
		{
			cout << result[j] << ' ';
		}
		cout << '\n';	
	}
	return 0;
}