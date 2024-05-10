#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdint>

using namespace std;

void solve(uint64_t n, ostream& out)
{
    double k = 1;
    k *= 8;
    k *= n;
    k += 1;
    uint64_t max_integer_x = (sqrt(k) - 1) / 2;
    uint64_t res = max_integer_x * (max_integer_x + 1) / 2;
   
    if (res == n)
    {
        if (max_integer_x % 2 == 0)
        {
            out << 1 << '/' << max_integer_x << '\n';
        }
        else
        {
            out << max_integer_x << '/' << 1 << '\n';
        }
    }
    else
    {
        uint64_t delta = n - res;
        if (max_integer_x % 2 == 0)
        {
            out << 1 + delta - 1 << '/' << max_integer_x + 1 - (delta - 1) << '\n';
        }
        else
        {
            out << max_integer_x + 1 - (delta - 1) << '/' << 1 + delta - 1 << '\n';
        }
    }
}

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    uint64_t n; in >> n;
    solve(n, out);
    return 0;
}