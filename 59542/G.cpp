#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <set>
#include <climits>
#include <algorithm>
#include <map>
#include <iterator>

using namespace std;

bool checkcheck(const vector<vector<char>>& matrix, int k, int i, int j, const vector<vector<int>>& ps)
{
    int subsquare = k / 3;
    if (i == 0)
    {
        if (ps[i + subsquare - 1][j + 2 * subsquare - 1] - ps[i + subsquare - 1][j + 2 * subsquare - 1 - subsquare] != subsquare * subsquare)
        {
            return false;
        }
    }
    else 
    {
        if (ps[i + subsquare - 1][j + 2 * subsquare - 1] - ps[i + subsquare - 1 - subsquare][j + 2 * subsquare - 1] - ps[i + subsquare - 1][j + 2 * subsquare - 1 - subsquare] + ps[i + subsquare - 1 - subsquare][j + 2 * subsquare - 1 - subsquare] != subsquare * subsquare)
        {
            return false;
        }
    }
    if (ps[i + 2 * subsquare - 1][j + subsquare - 1] - ps[i + 2 * subsquare - 1 - subsquare][j + subsquare - 1] - ps[i + 2 * subsquare - 1][j + subsquare - 1 - subsquare] + ps[i + 2 * subsquare - 1 - subsquare][j + subsquare - 1 - subsquare] != subsquare * subsquare)
    {
        return false;
    }
    if (ps[i + 2 * subsquare - 1][j + 2 * subsquare - 1] - ps[i + 2 * subsquare - 1 - subsquare][j + 2 * subsquare - 1] - ps[i + 2 * subsquare - 1][j + 2 * subsquare - 1 - subsquare] + ps[i + 2 * subsquare - 1 - subsquare][j + 2 * subsquare - 1 - subsquare] != subsquare * subsquare)
    {
        return false;
    }
    if (ps[i + 2 * subsquare - 1][j + 3 * subsquare - 1] - ps[i + 2 * subsquare - 1 - subsquare][j + 3 * subsquare - 1] - ps[i + 2 * subsquare - 1][j + 3 * subsquare - 1 - subsquare] + ps[i + 2 * subsquare - 1 - subsquare][j + 3 * subsquare - 1 - subsquare] != subsquare * subsquare)
    {
        return false;
    }
    if (ps[i + 3 * subsquare - 1][j + 2 * subsquare - 1] - ps[i + 3 * subsquare - 1 - subsquare][j + 2 * subsquare - 1] - ps[i + 3 * subsquare - 1][j + 2 * subsquare - 1 - subsquare] + ps[i + 3 * subsquare - 1 - subsquare][j + 2 * subsquare - 1 - subsquare] != subsquare * subsquare)
    {
        return false;
    }
    //i + subsquare - 1; j + 2 * subsquare - 1
    //i + 2 * subsquare - 1; j + subsquare - 1
    //i + 2 * subsquare - 1; j + 2 * subsquare - 1
    //i + 2 * subsquare - 1; j + 3 * subsquare - 1
    //i + 3 * subsquare - 1; j + 2 * subsquare - 1
    return true;
}

bool check(const vector<vector<char>>& matrix, int k, int n, int m, const vector<vector<int>>& ps)
{
    for (int i = 0; i <= n - k; i++)
    {
        for (int j = 0; j <= m - k; j++)
        {
            if (checkcheck(matrix, k, i, j, ps))
            {
                return true;
            }
        }
    }
    return false;
}

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    int n, m; in >> n >> m;

    vector<vector<int>> prefix_sums;
    vector<vector<char>> matrix;
    for (int i = 0; i < n; i++)
    {
        int k = 0;
        vector<int> ttemp;
        vector<char> temp;
        for (int j = 0; j < m; j++)
        {
            char x; in >> x;
            temp.push_back(x);
            if (x == '#')
            {
                k += 1;
            }
            if (i == 0)
            {
                ttemp.push_back(k);
            }
            else
            {
                ttemp.push_back(k + prefix_sums[i - 1][j]);
            }
        }
        matrix.push_back(temp);
        prefix_sums.push_back(ttemp);
    }

    int k = 3;
    int t = min(n, m);
    vector<int> possible_options;
    while (k <= t)
    {
        possible_options.push_back(k);
        k += 3;
    }

    int lb = 0;
    int rb = possible_options.size() - 1;

    while (rb - lb > 1)
    {
        int c = lb + (rb - lb) / 2;
        auto res = check(matrix, possible_options[c], n, m, prefix_sums);
        if (res)
        {
            lb = c;
        }
        else
        {
            rb = c;
        }
    }

    auto rbcheck = check(matrix, possible_options[rb], n, m, prefix_sums);
    if (rbcheck)
    {
        out << possible_options[rb] / 3;
    }
    else
    {
        out << possible_options[lb] / 3;
    }
    
    in.close();
    out.close();
    return 0;
}