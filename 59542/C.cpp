#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <cstdint>
#include <algorithm>

using namespace std;

uint64_t check(int w, int c, uint64_t total, const vector<uint64_t>& sums, const vector<uint64_t>& back_sums)
{
    uint64_t s = 0;

    if (c != 0)
    {
        if (c + w == back_sums.size())
        {
            s = total - sums[c - 1];
        }
        else
        {
            s = total - sums[c - 1] - back_sums[c + w];
        }
    }
    else
    {
        if (w == back_sums.size())
        {
            s = back_sums[0];
        }
        else
        {
            s = total - back_sums[c + w];
        }
    }
        
    return s;
}

template<class ForwardIt, class T>
ForwardIt bs(ForwardIt first, ForwardIt last, const T& value)
{
    first = std::lower_bound(first, last, value);
    if ((!(first == last) and !(value < *first)))
    {
        return first;
    }
    else
    {
        return last;
    }
}

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    int n, m; in >> n >> m;
    uint64_t temp = 0;
    vector<uint64_t> sums;
    vector<uint64_t> back_sums;
    vector<int> data;
    for (int i = 0; i < n; i++)
    {
        int x; in >> x; data.push_back(x); temp += x; sums.push_back(temp);
    }
    back_sums.push_back(temp);
    for (int i = 0; i < n-1; i++)
    {
        back_sums.push_back(temp - sums[i]);
    }
    for (int i = 0; i < m; i++)
    {
        int width;
        uint64_t amount;
        in >> width >> amount;
        int lb = 0;
        int rb = data.size() - 1 - (width - 1);
        if (check(width, lb, temp, sums, back_sums) > amount || check(width, rb, temp, sums, back_sums) < amount)
        {
            out << -1 << '\n';
        }
        else if (width == 1)
        {
            auto it = bs(data.begin(), data.end(), amount);
            if (it != data.end())
            {
                out << distance(data.begin(), it) + 1 << '\n';
            }
            else
            {
                out << -1<< '\n';
            }
        }
        else
        {
            bool flag = false;
            int c = lb + (rb - lb) / 2;
            while (rb - lb > 1)
            {
                c = lb + (rb - lb) / 2;

                auto check_lb = check(width, lb, temp, sums, back_sums);
                auto check_rb = check(width, rb, temp, sums, back_sums);
                auto check_c = check(width, c, temp, sums, back_sums);

                if (check_c == amount)
                {
                    out << c + 1 << '\n';
                    flag = true;
                    break;
                }
                else if (check_lb == amount)
                {
                    out << lb + 1 << '\n';
                    flag = true;
                    break;
                }
                else if (check_rb == amount)
                {
                    out << rb + 1 << '\n';
                    flag = true;
                    break;
                }
                else if (check_c > amount)
                {
                    rb = c;
                }
                else
                {
                    lb = c;
                }
            }
            if (flag)
            {
                continue;
            }
            else if (width == 2 && data[lb] + data[rb] == amount)
            {
                out << lb + 1 << '\n';
            }
            else if (check(width, lb, temp, sums, back_sums) == amount)
            {
                out << lb + 1 << '\n';
            }
            else if (check(width, rb, temp, sums, back_sums) == amount)
            {
                out << rb + 1 << '\n';
            }
            else
            {
                out << -1 << '\n';
            }
        }
    }
    return 0;
}