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

bool check(int c, const vector<pair<int, int>>& b, const vector<pair<int, int>>& e, int ma_x, int mi_x, const set<int>& xs)
{
    if (ma_x - mi_x + 1 <= c)
    {
        return true;
    }
    else
    {
        int t = 0;
        int k = 0;
        auto itold = xs.begin();
        for (auto lb = xs.begin(); lb!=xs.end(); lb++)
        {
            int rb = *lb + c - 1;
            if (*lb == mi_x)
            {
                auto it = itold;
                while (*it < rb + 1) { it++; k++; }
                itold = it;
                if (abs(e.at(k).first - e.at(k).second) + 1 <= c)
                {
                    return true;
                }
            }
            else
            {
                if (rb < ma_x)
                {
                    auto itrb = itold;
                    while (*itrb < rb + 1) { itrb++; k++; }
                    itold = itrb;
                    if (abs(min(b.at(t - 1).first, e.at(k).first) - max(b.at(t - 1).second, e.at(k).second)) + 1 <= c)
                    {
                        return true;
                    }
                }
                else
                {
                    int ind = xs.size() - 1;
                    auto itlb = next(xs.end(), -1);
                    while (*itlb > ma_x - c) { itlb--; ind--; }
                    if (abs(b.at(ind).first - b.at(ind).second) + 1 <= c)
                    {
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
            }
            t += 1;
        }
    }
}

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    int w, h, n;
    in >> w >> h >> n;

    int mi_x = INT_MAX;
    int ma_x = -INT_MAX;

    int mi_y_b = INT_MAX;
    int ma_y_b = -INT_MAX;

    int mi_y_e = INT_MAX;
    int ma_y_e = -INT_MAX;

    vector<pair<int, int>> data;
    vector<int> v;

    for (int i = 0; i < n; i++)
    {
        int x, y; in >> x >> y;
        data.emplace_back(x, y);
        v.push_back(x);
        if (x > ma_x)
        {
            ma_x = x;
        }
        if (x < mi_x)
        {
            mi_x = x;
        }
    }

    set<int> unique_xs(v.begin(), v.end());

    auto f = [](const pair<int, int> p1, const pair<int, int> p2) {
        return p1.first < p2.first;
        };
    sort(data.begin(), data.end(), f);

    vector<pair<int, int>> b(unique_xs.size());
    vector<pair<int, int>> e(unique_xs.size());

    int aa = 0;
    int bb = unique_xs.size() - 1;
    int lbb = 0;
    int rbb = data.size() - 1;

    while (rbb != -1 && lbb != data.size())
    {
        auto left = data[lbb];
        while (lbb != data.size() && left.first == data[lbb].first)
        {
            if (data[lbb].second > ma_y_b)
            {
                ma_y_b = data[lbb].second;
            }
            if (data[lbb].second < mi_y_b)
            {
                mi_y_b = data[lbb].second;
            }
            lbb++;
        }

        b[aa++] = make_pair(mi_y_b, ma_y_b);

        auto right = data[rbb];
        while (rbb != -1 && right.first == data[rbb].first)
        {
            if (data[rbb].second > ma_y_e)
            {
                ma_y_e = data[rbb].second;
            }
            if (data[rbb].second < mi_y_e)
            {
                mi_y_e = data[rbb].second;
            }
            rbb--;
        }
        
        e[bb--] = make_pair(mi_y_e, ma_y_e);
    }

    int lb = 1;
    int rb = ma_x - mi_x + 1;

    if (lb == rb)
    {
        out << 1;
        return 0;
    }
    else
    {
        bool flag = false;
        while (rb - lb > 1)
        {
            flag = false;
            int c = lb + (rb - lb) / 2;
            if (check(c, b, e, ma_x, mi_x, unique_xs))
            {
                rb = c;
            }
            else
            {
                lb = c;
                flag = true;
            }
        }
        if (flag)
        {
            out << rb;
        }
        else
        {
            if (check(lb, b, e, ma_x, mi_x, unique_xs))
            {
                out << lb;
            }
            else
            {
                out << rb;
            }
        }
    }

    in.close();
    out.close();
    return 0;
}