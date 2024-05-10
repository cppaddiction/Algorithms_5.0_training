#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <climits>

using namespace std;

unordered_map<string, int> months_days = { {"January", 31}, {"February", 28}, {"March", 31}, {"April", 30}, {"May", 31}, {"June", 30}, {"July", 31}, {"August", 31}, {"September", 30}, {"October", 31}, {"November", 30}, {"December", 31} };
vector<string> week = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };
vector<string> months = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };

string GetDayOfWeek(int day, string month, int year, bool is_fucked, int delta) {
	if (is_fucked)
	{
		months_days["February"] = 29;
	}
	else
	{
		months_days["February"] = 28;
	}
	int i = 0;
	while (months[i] != month) { delta += months_days[months[i]]; i++; }
	delta += day;
	delta -= 1;
	return week[delta % 7];
}

int main()
{
	int n; cin >> n;
	int year; cin >> year;
	bool is_fucked = ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0)) ? true : false;
	vector<pair<int, string>> gos_weekends;
	for (int i = 0; i < n; i++)
	{
		int x; string s;
		cin >> x >> s;
		gos_weekends.emplace_back(x, s);
	}
	string first_day_of_the_year; cin >> first_day_of_the_year;
	int delta = std::distance(week.begin(), std::find(week.begin(), week.end(), first_day_of_the_year));
	string next_day = ""; if (is_fucked) { next_day = week[(delta + 1) % 7];}
	map<string, int> gos_weekends_freq = { {"Monday", 0}, {"Tuesday", 0}, {"Wednesday", 0}, {"Thursday", 0}, {"Friday", 0}, {"Saturday", 0}, {"Sunday", 0} };
	for (const auto& item : gos_weekends)
	{
		gos_weekends_freq[GetDayOfWeek(item.first, item.second, year, is_fucked, delta)]++;
	}
	string mas = "";
	string mis = "";
	int ma = -1;
	int mi = INT_MAX;
	for (const auto& item : gos_weekends_freq)
	{
		if (item.second > ma)
		{
			ma = item.second;
			mas = item.first;
		}
		if (item.second < mi)
		{
			mi = item.second;
			mis = item.first;
		}
	}
	if (is_fucked)
	{
		if (gos_weekends_freq[first_day_of_the_year] == mi)
		{
			mis = first_day_of_the_year;
		}
		if (gos_weekends_freq[next_day] == mi)
		{
			mis = next_day;
		}
		if (gos_weekends_freq[first_day_of_the_year] == ma)
		{
			for (const auto& item : gos_weekends_freq)
			{
				if (item.second == ma && item.first != first_day_of_the_year && item.first != next_day)
				{
					mas = item.first;
				}
			}
		}
		if (gos_weekends_freq[next_day] == ma)
		{
			for (const auto& item : gos_weekends_freq)
			{
				if (item.second == ma && item.first != first_day_of_the_year && item.first != next_day)
				{
					mas = item.first;
				}
			}
		}
	}
	else
	{
		if (gos_weekends_freq[first_day_of_the_year] == mi)
		{
			mis = first_day_of_the_year;
		}
		if (gos_weekends_freq[first_day_of_the_year] == ma)
		{
			for (const auto& item : gos_weekends_freq)
			{
				if (item.second == ma && item.first != first_day_of_the_year)
				{
					mas = item.first;
				}
			}
		}
	}
	cout << mis << ' ' << mas;
	/*
	auto cmp = [](const pair<string, int> & lhs, const pair<string, int>& rhs)
	{
		return lhs.second != rhs.second ? lhs.second < rhs.second : lhs.first < rhs.first;
	};
	std::sort(gos_weekends_freq.begin(), gos_weekends_freq.end(), cmp);
	int i = 0;
	for (const auto& item : gos_weekends_freq)
	{
		if (i == 0)
		{
			cout << item.first << ' ';
		}
		if (i == gos_weekends_freq.size() - 1)
		{
			cout << item.second;
		}
		i++;
	}
	cout << GetDayOfWeek(17, "October", 2023, "Sunday");*/
	return 0;
}




























































































/*int main()
{
	int current_round = 0;
	int x, y, p;
	cin >> x >> y >> p;
	
	y -= x;
	if (y <= 0)
	{
		current_round += 1;//round 1 was played
		cout << current_round;
	}
	else
	{
		int opponent_army = p;
		current_round += 1;//round 1 was played
		while ((y > 0 || opponent_army > 0)&&x>0)
		{
			if (opponent_army < x)
			{
				if (y > 0)
				{
					y -= (x - opponent_army);//building dmg
					opponent_army = 0;//kill them all
					//cant kill my army
				}
				else
				{
					opponent_army = 0;
				}
			}
			else
			{
				if (y > 0)
				{
					y -= 1;//1 solider doing building dmg
					opponent_army -= (x - 1);//killing x-1 opponent soliders
					x -= opponent_army;//he kills opponent_army my soliders
				}
				else
				{
					opponent_army -= x;
					x -= opponent_army;
				}
			}
			if (y > 0)
			{
				opponent_army += p;//spawned after round n
			}
			current_round += 1;//round n was played
		}
		if (x <= 0)
		{
			cout << -1;
		}
		else
		{
			cout << current_round;
		}
	}

	return 0;
}*/