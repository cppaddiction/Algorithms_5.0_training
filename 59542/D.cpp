#include <iostream>
#include <fstream>
#include <vector>
#include <climits>

using namespace std;

int check_left(int c, const vector<int>& fp)
{
    int i = 0;
    int lc = 0;
    int lh = 1;

    while (i < fp.size())
    {
        if (lc + fp[i] <= c)
        {
            lc += fp[i];
            i++;
        }
        else
        {
            lc = 0;
            lh++;
        }
        if (lc != 0 && lc + 1 <= c)
        {
            lc++;
        }
    }

    return lh;
}

int check_right(int c, int w, const vector<int>& sp)
{
    int i = 0;
    int rc = c;
    int rh = 1;

    while (i < sp.size())
    {
        if (rc + sp[i] <= w)
        {
            rc += sp[i];
            i++;
        }
        else
        {
            rc = c;
            rh++;
        }
        if (rc != c && rc + 1 <= w)
        {
            rc++;
        }
    }

    return rh;
}


int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    int mi = INT_MAX;
    int ma_first = -INT_MAX;
    int ma_second = -INT_MAX;
    int w, n, m; in >> w >> n >> m;
    vector<int> first_part;
    for (int i = 0; i < n; i++)
    {
        int x; in >> x; first_part.push_back(x); if (x > ma_first) { ma_first = x; }
    }
    vector<int> second_part;
    for (int i = 0; i < m; i++)
    {
        int x; in >> x; second_part.push_back(x); if (x > ma_second) { ma_second = x; }
    }
    int lb = ma_first;
    int rb = w - ma_second;
    int c = lb + (rb - lb) / 2;

    while (rb - lb > 1)
    {
        c = lb + (rb - lb) / 2;
        int lres = check_left(c, first_part);
        int rres = check_right(c, w, second_part);
        auto max_height = max(lres, rres);
        if (max_height < mi)
        {
            mi = max_height;
        }
        if (lres == rres)
        {
            out << lres << '\n';
            return 0;
        }
        else if (lres > rres)
        {
            lb = c;
        }
        else
        {
            rb = c;
        }
    }
    int lresl = check_left(lb, first_part);
    int rresl = check_right(lb, w, second_part);
    int lresr = check_left(rb, first_part);
    int rresr = check_right(rb, w, second_part);
    auto max_height = min(max(lresl, rresl), max(lresr, rresr));
    if (max_height < mi)
    {
        mi = max_height;
    }
    out << mi << '\n';
    in.close();
    out.close();
    return 0;
}