#include <iostream>
#include <vector>

using namespace std;

const char symbol = '$';

struct Position
{
	int i;
	int j;
};

void R(vector<vector<char>>& data, Position pos)
{
	int i, j;

	//going right
	i = pos.i;
	j = pos.j;
	j++;
	while (j < 8 && data[i][j] != 'R' && data[i][j] != 'B')
	{
		data[i][j] = symbol;
		j++;
	}

	//going left
	i = pos.i;
	j = pos.j;
	j--;
	while (j >=0 && data[i][j] != 'R' && data[i][j] != 'B')
	{
		data[i][j] = symbol;
		j--;
	}

	//going up
	i = pos.i;
	j = pos.j;
	i--;
	while (i >= 0 && data[i][j] != 'R' && data[i][j] != 'B')
	{
		data[i][j] = symbol;
		i--;
	}

	//going down
	//going up
	i = pos.i;
	j = pos.j;
	i++;
	while (i < 8 && data[i][j] != 'R' && data[i][j] != 'B')
	{
		data[i][j] = symbol;
		i++;
	}
}

void B(vector<vector<char>>& data, Position pos)
{
	int i, j;
	
	//going ru
	i = pos.i;
	j = pos.j;
	i--;
	j++;
	while (j < 8 && i >= 0 && data[i][j] != 'R' && data[i][j] != 'B')
	{
		data[i][j] = symbol;
		i--;
		j++;
	}

	//going rd
	i = pos.i;
	j = pos.j;
	i++;
	j++;
	while (j < 8 && i < 8 && data[i][j] != 'R' && data[i][j] != 'B')
	{
		data[i][j] = symbol;
		i++;
		j++;
	}

	//going lu
	i = pos.i;
	j = pos.j;
	i--;
	j--;
	while (j >= 0 && i >= 0 && data[i][j] != 'R' && data[i][j] != 'B')
	{
		data[i][j] = symbol;
		i--;
		j--;
	}

	//going ld
	i = pos.i;
	j = pos.j;
	i++;
	j--;
	while (j >= 0 && i < 8 && data[i][j] != 'R' && data[i][j] != 'B')
	{
		data[i][j] = symbol;
		i++;
		j--;
	}
	return;
}

int main()
{
	vector<vector<char>> vec;
	for (int i = 0; i < 8; i++)
	{
		vector<char> v;
		for (int j = 0; j < 8; j++)
		{
			v.push_back(cin.get());
		}
		cin.get();
		vec.push_back(v);
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (vec[i][j] == 'R')
			{
				R(vec, Position{ i, j });
			}
			if (vec[i][j] == 'B')
			{
				B(vec, Position{ i, j });
			}
		}
	}

	int k = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (vec[i][j] == '*')
			{
				k++;
			}
		}
	}
	
	cout << k;

	return 0;
}