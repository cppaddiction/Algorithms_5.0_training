#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

set<int> possible_outcomes;

int main()
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
		while ((y > 0 || opponent_army > 0) && x > 0)
		{
			if (x >= y)
			{
				//здесь каждый раз пробуем разбить казарму и победить оставшимися силами
				
				//разбиваем казарму
				int testy = 0;
				//оставшиеся воины бьют вражеских солдат
				int test_opponent_army = opponent_army - (x - y);
				//теперь бьют нас
				int testx = x - test_opponent_army;
				//раунд прошел
				int test_round = current_round + 1;
				while ((testy > 0 || test_opponent_army > 0) && testx > 0)
				{
					if (test_opponent_army < testx)
					{
						test_opponent_army = 0;
					}
					else
					{
						test_opponent_army -= testx;
						testx -= test_opponent_army;
					}
					test_round += 1;
				}
				if (testx > 0)
				{
					possible_outcomes.insert(test_round);
				}
			}
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
			if (possible_outcomes.size() == 0)
			{
				cout << -1;
			}
			else
			{
				cout << *possible_outcomes.begin();
			}
		}
		else
		{
			cout << min(current_round, *possible_outcomes.begin());
		}
	}

	return 0;
}


/*int main()
{
	set<int> s;
	s.insert(42);
	s.insert(41);
	s.insert(46);
	s.insert(45);
	s.insert(41);
	s.insert(4);
	s.insert(489);
	cout << *s.begin();
	return 0;
}*/