#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>

using namespace std;

vector<string> split(const string& s)
{
	vector<string> result;
	string temp;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] != ' ')
		{
			temp += s[i];
		}
		else
		{
			if (temp != "")
			{
				result.push_back(temp);
				temp = "";
			}
		}
	}
	if (temp != "")
	{
		result.push_back(temp);
	}
	return result;
}

int main()
{
	string s1, s2;
	getline(cin, s1);
	getline(cin, s2);
	vector<string> raw_keys = split(s1);
	set<string> keys(raw_keys.begin(), raw_keys.end());
	vector<string> words = split(s2);
	for (const auto& word : words)
	{
		char sym = word[0];
		auto start = find_if(keys.begin(), keys.end(), [sym] (const string& str) {return str[0] == sym;});
		while (start != keys.end() && word.substr(0, static_cast<int>((*start).size())) != (*start) && (*start)[0] == sym)
		{
			start++;
		}
		if (start == keys.end() || (*start)[0] != sym)
		{
			cout << word << ' ';
		}
		else
		{
			cout << *start << ' ';
		}
	}
	return 0;
}