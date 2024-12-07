#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstdint>

using namespace std;

struct Party {
    int voters;
    int bribe;
    int number;
    uint64_t sum;
};

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    int ma = -INT_MAX;

    vector<Party> parties;

    int party_count; in >> party_count;

    if (party_count == 1)
    {
        int voters, bribe; in >> voters >> bribe;

        out << bribe << '\n';
        out << 1 << '\n';
        out << voters;
    }
    else if (party_count == 2)
    {
        int voters1, bribe1; in >> voters1 >> bribe1;
        int voters2, bribe2; in >> voters2 >> bribe2;

        if (bribe1 != -1 && bribe2 != -1)
        {
            int delta1 = (voters2 >= voters1 ? (voters2 - voters1) / 2 + 1 : 0);
            int delta2 = (voters1 >= voters2 ? (voters1 - voters2) / 2 + 1 : 0);

            if (bribe1 + delta1 < bribe2 + delta2)
            {
                out << bribe1 + delta1 << '\n';
                out << 1 << '\n';
                out << voters1 + delta1 << ' ' << voters2 - delta1;
            }
            else
            {
                out << bribe2 + delta2 << '\n';
                out << 2 << '\n';
                out << voters1 - delta2 << ' ' << voters2 + delta2;
            }
        }
        else if (bribe1 == -1 && bribe2 != -1)
        {
            int delta = (voters1 >= voters2 ? ((voters1 - voters2) / 2 + 1) : 0);
            out << bribe2 + delta << '\n';
            out << 2 << '\n';
            out << voters1 - delta << ' ' << voters2 + delta;
        }
        else if (bribe1 != -1 && bribe2 == -1)
        {
            int delta = (voters2 >= voters1 ? ((voters2 - voters1) / 2 + 1) : 0);
            out << bribe1 + delta << '\n';
            out << 1 << '\n';
            out << voters1 + delta << ' ' << voters2 - delta;
        }
    }
    else
    {
        for (int i = 0; i < party_count; i++)
        {
            int voters, bribe; in >> voters >> bribe;

            if (voters > ma)
            {
                ma = voters;
            }

            parties.emplace_back(voters, bribe, i + 1, 0);
        }

        sort(parties.begin(), parties.end(),
            [](const Party& p1, const Party& p2)
            {
                if (p1.voters < p2.voters)
                {
                    return true;
                }
                else if (p1.voters == p2.voters)
                {
                    if (p1.bribe != -1 && p2.bribe != -1)
                    {
                        return p1.bribe < p2.bribe;
                    }
                    else if (p1.bribe == -1 && p2.bribe != -1)
                    {
                        return false;
                    }
                    else if (p1.bribe != -1 && p2.bribe == -1)
                    {
                        return true;
                    }
                }
                else
                {
                    return false;
                }
            });

        parties[0].sum = parties[0].voters;

        for (int i = 1; i < parties.size(); i++)
        {
            parties[i].sum = parties[i - 1].sum + parties[i].voters;
        }

        int ans = INT_MAX;
        int ans_party_number = INT_MAX;
        int ans_party_index = INT_MAX;
        int saveansparty = INT_MAX;
        int anscut = INT_MAX;

        for (int i = 0; i < parties.size(); i++)
        {
            if (parties[i].bribe != -1)
            {
                int lb = 0;
                int rb = ma;
                int cut = lb + (rb - lb) / 2;
                int saveparty = INT_MAX;

                while (rb - lb > 1)
                {
                    int lbb = 0;
                    int rbb = parties.size() - 1;
                    int c = lbb + (rbb - lbb) / 2;

                    while (rbb - lbb > 1)
                    {
                        if (parties[c].voters > cut)
                        {
                            rbb = c;
                        }
                        else
                        {
                            lbb = c;
                        }

                        c = lbb + (rbb - lbb) / 2;
                    }

                    if (parties[i].voters + parties[parties.size() - 1].sum - parties[lbb].sum - (parties.size() - rbb) * cut - (parties[i].voters > cut && i != lbb ? parties[i].voters - cut : 0) > cut)
                    {
                        lb = cut;
                        saveparty = parties[i].voters + parties[parties.size() - 1].sum - parties[lbb].sum - (parties.size() - rbb) * cut - (parties[i].voters > cut && i != lbb ? parties[i].voters - cut : 0);
                    }
                    else
                    {
                        rb = cut;
                    }

                    cut = lb + (rb - lb) / 2;
                }

                if (saveparty == INT_MAX)
                {
                    saveparty = parties[parties.size() - 1].sum;
                }

                int saveoldparty = saveparty;

                int delta = parties.size() - 1 - (i + 1) + 1;;

                if (saveparty > cut + 2 && delta > 0)
                {
                    saveparty = saveparty - (saveparty - (cut + 2));
                }

                if (parties[i].bribe + saveparty - parties[i].voters < ans)
                {
                    ans = parties[i].bribe + saveparty - parties[i].voters;
                    ans_party_number = parties[i].number;
                    ans_party_index = i;
                    saveansparty = saveoldparty;
                    anscut = cut;
                }
            }
        }

        int k = ans_party_index;

        bool flag = true;

        for (int i = k + 1; i < parties.size(); i++)
        {
            if (parties[i].voters > anscut)
            {
                parties[i].voters = anscut;

                if (parties[i].voters + 1 < saveansparty - 1 && flag)
                {
                    parties[i].voters++;
                    saveansparty--;
                }
                else
                {
                    flag = false;
                }
            }
        }

        parties[k].voters = saveansparty;

        sort(parties.begin(), parties.end(), [](const Party& p1, const Party& p2) {return p1.number < p2.number; });

        out << ans << '\n';
        out << ans_party_number << '\n';

        for (int i = 0; i < parties.size(); i++)
        {
            out << parties[i].voters << ' ';
        }
    }

    in.close();
    out.close();

    return 0;
}