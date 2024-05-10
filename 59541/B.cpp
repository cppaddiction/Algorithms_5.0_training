#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>

using namespace std;

int main()
{
	string s1, s2;
	cin >> s1 >> s2;
	map<char, int> temp1;
	map<char, int> temp2;
	for (const auto& item : s1)
	{
		temp1[item]++;
	}
	for (const auto& item : s2)
	{
		temp2[item]++;
	}
	auto res = temp1 == temp2 ? true : false;
	if (res)
		cout << "YES";
	else
		cout << "NO";
	return 0;
}