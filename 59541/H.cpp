#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <climits>
#include <algorithm>
#include <fstream>
#include <string>

#define PI 3.141592653589793238462643383279502884197169399375105820974944

using namespace std;

struct CustomKey {
    double angle;
    double dist;
    bool operator==(const CustomKey& other)const { return angle == other.angle && dist == other.dist; }
};

struct CustomKeyHasher {
    size_t operator()(const CustomKey& key) const
    {
        hash<double> h1;
        hash<double> h2;
        return h1(key.angle) + h2(key.dist);
    }
};

struct Point {
    int x;
    int y;
    bool operator==(const Point& other) const { return x == other.x && y == other.y; }
    bool operator!=(const Point& other) const { return !(*this == other); }
};

struct Match {
    int x1;
    int y1;
    int x2;
    int y2;
    bool operator==(const Match& other) const { return x1 == other.x1 && y1 == other.y1 && x2 == other.x2 && y2 == other.y2 || x1 == other.x2 && y1 == other.y2 && x2 == other.x1 && y2 == other.y1; }
};

double Distance(double x1, double y1, double x2, double y2)
{
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

double GetAlpha(double x1, double y1, double x2, double y2)
{
    double alpha = 0;

    if (x1 == x2 && y1 < y2)
    {
        alpha = 0;
    }
    else if (x1 > x2 && y1 < y2)
    {
        alpha = 0 + atan(abs(x1 - x2) * 1.0 / abs(y1 - y2)) * 180.0 / PI;
    }
    else if (x1 > x2 && y1 == y2)
    {
        alpha = 90;
    }
    else if (x1 > x2 && y1 > y2)
    {
        alpha = 90 + atan(abs(y1 - y2) * 1.0 / abs(x1 - x2)) * 180.0 / PI;
    }
    else if (x1 == x2 && y1 > y2)
    {
        alpha = 180;
    }
    else if (x1 < x2 && y1 > y2)
    {
        alpha = 180 + atan(abs(x1 - x2) * 1.0 / abs(y1 - y2)) * 180.0 / PI;
    }
    else if (x1 < x2 && y1 == y2)
    {
        alpha = 270;
    }
    else
    {
        alpha = 270 + atan(abs(y1 - y2) * 1.0 / abs(x1 - x2)) * 180.0 / PI;
    }

    return alpha;
}

bool ccw(Point A, Point B, Point C)
{
    return (C.y - A.y) * (B.x - A.x) > (B.y - A.y) * (C.x - A.x);
}


bool intersect(Point A, Point B, Point C, Point D)
{
    return ccw(A, C, D) != ccw(B, C, D) && ccw(A, B, C) != ccw(A, B, D);
}


int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    int n; in >> n;
    vector<Match> A(n);
    vector<Match> B(n);
    unordered_map<CustomKey, int, CustomKeyHasher> ans;
    int ma = -1;
    bool flag = false;
    for (int i = 0; i < n; i++)
    {
        int x1, y1, x2, y2; in >> x1 >> y1 >> x2 >> y2;
        A[i] = Match{ x1, y1, x2, y2 };
    }
    for (int i = 0; i < n; i++)
    {
        int x1, y1, x2, y2; in >> x1 >> y1 >> x2 >> y2;
        B[i] = Match{ x1, y1, x2, y2 };
    }

    for (const auto& a : A)
    {
        for (const auto& b : B)
        {
            if (a == b)
            {
                auto& val = ans[CustomKey{ 0, 0 }];
                val += 1;
                if (val > ma)
                {
                    ma = val;
                }
                flag = true;
            }
            else
            {
                auto ca = make_pair((a.x1 + a.x2) * 1.0 / 2, (a.y1 + a.y2) * 1.0 / 2);
                auto cb = make_pair((b.x1 + b.x2) * 1.0 / 2, (b.y1 + b.y2) * 1.0 / 2);
                auto da = Distance(a.x1, a.y1, a.x2, a.y2);
                auto db = Distance(b.x1, b.y1, b.x2, b.y2);
                auto d1 = Distance(a.x1, a.y1, b.x1, b.y1);
                auto d2 = Distance(a.x2, a.y2, b.x2, b.y2);
                auto d3 = Distance(a.x1, a.y1, b.x2, b.y2);
                auto d4 = Distance(a.x2, a.y2, b.x1, b.y1);
                auto c1 = make_pair((a.x1 + b.x1) * 1.0 / 2, (a.y1 + b.y1) * 1.0 / 2);
                auto c2 = make_pair((a.x2 + b.x2) * 1.0 / 2, (a.y2 + b.y2) * 1.0 / 2);
                auto c3 = make_pair((a.x1 + b.x2) * 1.0 / 2, (a.y1 + b.y2) * 1.0 / 2);
                auto c4 = make_pair((a.x2 + b.x1) * 1.0 / 2, (a.y2 + b.y1) * 1.0 / 2);
                if (((da == db && a.x1 == b.x1 && a.x2 == b.x2) || (da == db && a.y1 == b.y1 && a.y2 == b.y2) || (da == db && a.x1 == b.x2 && a.x2 == b.x1) || (da == db && a.y1 == b.y2 && a.y2 == b.y1)) ||
                    (d1 == d2 && c1 != c2 && c3 == c4 && !intersect(Point{ a.x1, a.y1 }, Point{ a.x2, a.y2 }, Point{ b.x1, b.y1 },
                        Point{ b.x2, b.y2 }) && da == db && Point{ a.x1, a.y1 } != Point{ b.x1, b.y1 } && Point{ a.x2, a.y2 } != Point{ b.x2, b.y2 }
                        && Point{ a.x1, a.y1 } != Point{ b.x2, b.y2 } && Point{ a.x2, a.y2 } != Point{ b.x1, b.y1 }
                        && (a.x2 - a.x1) * (b.x2 - b.x1) + (a.y2 - a.y1) * (b.y2 - b.y1) != 0) ||
                    (d3 == d4 && c3 != c4 && c1 == c2 && !intersect(Point{ a.x1, a.y1 }, Point{ a.x2, a.y2 }, Point{ b.x1, b.y1 },
                        Point{ b.x2, b.y2 }) && da == db && Point{ a.x1, a.y1 } != Point{ b.x1, b.y1 } && Point{ a.x2, a.y2 } != Point{ b.x2, b.y2 }
                        && Point{ a.x1, a.y1 } != Point{ b.x2, b.y2 } && Point{ a.x2, a.y2 } != Point{ b.x1, b.y1 }
                        && (a.x2 - a.x1) * (b.x2 - b.x1) + (a.y2 - a.y1) * (b.y2 - b.y1) != 0))
                {
                    auto alpha = GetAlpha(ca.first, ca.second, cb.first, cb.second);
                    auto dist = Distance(ca.first, ca.second, cb.first, cb.second);
                    auto& val = ans[CustomKey{ alpha, dist }];
                    val += 1;
                    if (val > ma)
                    {
                        ma = val;
                    }
                }
            }
        }
    }

    if (ans.size() > 0)
    {
        if (ma == 1)
        {
            if (flag)
            {
                out << n - 1;
            }
            else
            {
                if (ans.size() == 1)
                {
                    out << 0;
                }
                else
                {
                    out << n - 1;
                }
            }
        }
        else
        {
            out << n - ma;
        }
    }
    else
    {
        out << n;
    }

    in.close();
    out.close();
    return 0;
}