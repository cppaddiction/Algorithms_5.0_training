#include <iostream>

using namespace std;

int main()
{
	int pos1, t1;
	int pos2, t2;
	cin >> pos1 >> t1 >> pos2 >> t2;
	
	//пересек если 1ый содерж во 2м или 2ой содерж в 1м или перекрытие
	int rightest = pos1 + t1 >= pos2 + t2 ? pos1 + t1 : pos2 + t2;
	int leftest = pos1 - t1 <= pos2 - t2 ? pos1 - t1 : pos2 - t2;
	if ((pos1 - t1 <= pos2 - t2 && pos2 - t2 <= pos1 + t1 || pos1 - t1 <= pos2 + t2 && pos2 + t2 <= pos1 + t1) ||
		(pos1 - t1 <= pos2 - t2 && pos1 + t1 >= pos2 + t2) ||
		(pos2 - t2 <= pos1 - t1 && pos2 + t2 >= pos1 + t1))
	{
		cout << rightest - leftest + 1;
	}
	else
	{
		cout << 2 * t1 + 1 + 2 * t2 + 1;
	}
	return 0;
}