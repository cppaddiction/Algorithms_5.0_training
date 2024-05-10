#include <iostream>
#include <cmath>
#include <vector>
#include <unordered_set>
#include <climits>
#include <algorithm>
#include <fstream>

#define PI 3.141592653589793238462643383279502884197169399375105820974944

using namespace std;

struct FreePoints {
    pair<pair<int, int>, pair<int, int>> first_pair;
    pair<pair<int, int>, pair<int, int>> second_pair;
};

double Distance(int x1, int y1, int x2, int y2)
{
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

FreePoints GetFreePoints(int x1, int y1, int x2, int y2)
{
    double d = Distance(x1, y1, x2, y2);
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

    auto fp = make_pair(make_pair(round(x1 - d * cos(alpha * PI / 180)), round(y1 - d * sin(alpha * PI / 180))), make_pair(round(x2 - d * cos(alpha * PI / 180)), round(y2 - d * sin(alpha * PI / 180))));
    auto sp = make_pair(make_pair(round(x1 + d * cos(alpha * PI / 180)), round(y1 + d * sin(alpha * PI / 180))), make_pair(round(x2 + d * cos(alpha * PI / 180)), round(y2 + d * sin(alpha * PI / 180))));

    return { fp, sp };
}

struct CustomKey {
    CustomKey(pair<int, int> p) { coords = p; }
    pair<int, int> coords;
    bool operator==(const CustomKey& other) const { return coords.first == other.coords.first && coords.second == other.coords.second; }
};

struct CustomKeyHasher {
    size_t operator()(const CustomKey& key) const
    {
        hash<int> h1;
        hash<int> h2;
        return h1(key.coords.first) + h2(key.coords.second);
    }
};

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    int n; in >> n;
    vector<CustomKey> data;
    for (int i = 0; i < n; i++)
    {
        int x, y; in >> x >> y; data.emplace_back(make_pair(x, y));
    }

    unordered_set<CustomKey, CustomKeyHasher> s(data.begin(), data.end());

    if (n == 1)
    {
        out << 3 << '\n';
        out << data[0].coords.first + 1 << ' ' << data[0].coords.second << '\n';
        out << data[0].coords.first + 1 << ' ' << data[0].coords.second - 1 << '\n';
        out << data[0].coords.first << ' ' << data[0].coords.second - 1 << '\n';
    }
    else if (n == 2)
    {
        out << 2 << '\n';
        auto points = GetFreePoints(data[0].coords.first, data[0].coords.second, data[1].coords.first, data[1].coords.second);
        out << points.first_pair.first.first << ' ' << points.first_pair.first.second << '\n';
        out << points.first_pair.second.first << ' ' << points.first_pair.second.second << '\n';
    }
    else
    {
        CustomKey k{ make_pair(INT_MAX, INT_MAX) };
        for (int i = 0; i < data.size(); i++)
        {
            for (int j = 0; j < data.size(); j++)
            {
                if (i != j)
                {
                    auto free_points = GetFreePoints(data[i].coords.first, data[i].coords.second, data[j].coords.first, data[j].coords.second);
                    bool fp_f_in_s = s.find(CustomKey{ free_points.first_pair.first }) == s.end() ? false : true;
                    bool fp_s_in_s = s.find(CustomKey{ free_points.first_pair.second }) == s.end() ? false : true;
                    bool sp_f_in_s = s.find(CustomKey{ free_points.second_pair.first }) == s.end() ? false : true;
                    bool sp_s_in_s = s.find(CustomKey{ free_points.second_pair.second }) == s.end() ? false : true;
                    if (fp_f_in_s && fp_s_in_s)
                    {
                        out << 0 << '\n';
                        return 0;
                    }
                    else if (sp_f_in_s && sp_s_in_s)
                    {
                        out << 0 << '\n';
                        return 0;
                    }
                    else if (fp_f_in_s)
                    {
                        k = CustomKey{ free_points.first_pair.first };
                    }
                    else if (fp_s_in_s)
                    {
                        k = CustomKey{ free_points.first_pair.second };
                    }
                    else if (sp_f_in_s)
                    {
                        k = CustomKey{ free_points.second_pair.first };
                    }
                    else if (sp_s_in_s)
                    {
                        k = CustomKey{ free_points.second_pair.second };
                    }
                }
            }
        }
        if (k.coords.first != INT_MAX && k.coords.second != INT_MAX)
        {
            out << 1 << '\n';
            out << k.coords.first << ' ' << k.coords.second << '\n';
        }
        else
        {
            out << 2 << '\n';
            auto points = GetFreePoints(data[0].coords.first, data[0].coords.second, data[1].coords.first, data[1].coords.second);
            out << points.first_pair.first.first << ' ' << points.first_pair.first.second << '\n';
            out << points.first_pair.second.first << ' ' << points.first_pair.second.second << '\n';
        }
    }

    in.close();
    out.close();
    return 0;
}