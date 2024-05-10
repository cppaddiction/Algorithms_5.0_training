#include <iostream>
#include <fstream>
#include <unordered_map>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    //unordered_map<int, int> storage;
    vector<int> data;
    int n; in >> n;
    for (int i = 0; i < n; i++)
    {
        int x; in >> x;
        data.push_back(x);
    }
    sort(data.begin(), data.end());
    int k; in >> k;
    for (int i = 0; i < k; i++)
    {
        int a, b; in >> a >> b;
        auto lower = std::lower_bound(data.begin(), data.end(), a);
        auto upper = std::upper_bound(data.begin(), data.end(), b);
        advance(upper, -1);
        out << distance(lower, upper) + 1 << ' ';
    }
    return 0;
}