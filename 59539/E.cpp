#include <iostream>
#include <string>

using namespace std;

string f(string val, int k, int d)
{
	for (int j = 0; j <= 9; j++)
	{
		string s = val + to_string(j);
		unsigned long long temp = stoll(s);
		if (temp % k == 0)
		{
			string tail(d - 1, '0');
			return to_string(temp) + tail;
		}
	}
	return "-1";
}

int main()
{
	int n, k, d;
	cin >> n >> k >> d;
	cout << f(to_string(n), k, d);
	return 0;
}

/*
def f(val, k, d, cd):
	if(cd > d) : return val
	for i in range(10):
		s = val + str(i)
		temp = int(s)
		if (temp % k == 0):
			cd+=1
			return f(str(temp), k, d, cd)
	return -1

n, k, d = map(int, input().split())
print(f(str(n), k, d, 1))

*/