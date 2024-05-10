#include <iostream>

using namespace std;

int main()
{
	char c;
	int firstfirst, secondfirst;
	int firstsecond, secondsecond;
	int guestflag;
	cin >> firstfirst >> c >> secondfirst;
	cin >> firstsecond >> c >> secondsecond;
	cin >> guestflag;
	//how many balls 1st team need to score to win?
	int first_total = firstfirst + firstsecond;
	int second_total = secondfirst + secondsecond;
	int delta = second_total - first_total;
	if (guestflag == 1)
	{
		//guest match is being played
		if (delta < 0)
		{
			cout << 0;
		}
		else
		{
			if (firstsecond + delta <= secondfirst)
			{
				cout << delta + 1;
			}
			else
			{
				cout << delta;
			}
		}
	}
	if (guestflag == 2)
	{
		//guest match has alrdy been played
		//cin >> firstfirst >> c >> secondfirst;
		//cin >> firstsecond >> c >> secondsecond;
		if (delta < 0)
		{
			cout << 0;
		}
		else
		{
			if (firstfirst > secondsecond)
			{
				cout << delta;
			}
			else
			{
				cout << delta + 1;
			}
		}
	}
	return 0;
}