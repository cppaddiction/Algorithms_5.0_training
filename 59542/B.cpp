#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdint>
#include <climits>

using namespace std;

bool check(uint64_t n, uint64_t k)
{
    uint64_t d1 = 1;
    d1 *= k;
    d1 *= k;
    d1 *= k;
    uint64_t d2 = 1;
    d2 *= 6;
    d2 *= k;
    d2 *= k;
    uint64_t d3 = 1;
    d3 *= 5;
    d3 *= k;
    uint64_t d4 = (d1 + d2 + d3) / 6 - 1;
    if (d4 <= n)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    uint64_t n; in >> n;
    if (n == 0)
    {
        out << 0;
        return 0;
    }
    else if (n == 1)
    {
        out << 1;
        return 0;
    }
    else
    {
        uint64_t lb = 1;
        uint64_t rb = pow(ULLONG_MAX, 1.0 / 3);
        while (rb - lb > 1)
        {
            uint64_t c = lb + (rb - lb) / 2;
            auto ch = check(n, c);
            if (ch)
            {
                lb = c;
            }
            else
            {
                rb = c;
            }
        }
        if (check(n, rb))
        {
            out << rb;
        }
        else
        {
            out << lb;
        }
    }
    return 0;
}