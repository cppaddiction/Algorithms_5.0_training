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

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    int n, k; in >> n >> k;

    vector<int> temp;
    for (int i = 1; i <= k; i++)
    {
        temp.push_back(i);
    }

    set<int> update(temp.begin(), temp.end());

    map<int, int> timeslots_per_device_required;
    unordered_map<int, pair<set<int>, vector<int>>> devices_and_missing_parts; // device, existing update parts, missing update parts
    for (int i = 2; i <= n; i++)
    {
        timeslots_per_device_required[i];
        devices_and_missing_parts[i];
    }

    unordered_map<int, unordered_map<int, int>> value_one_for_other;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i != j)
            {
                value_one_for_other[i][j];
            }
        }
    }

    int timeslot_count = 1;

    while (true)
    {
        unordered_map<int, int> update_part_freqs;
        for (int i = 0; i < k; i++)
        {
            int t = 0;
            for (auto it = devices_and_missing_parts.begin(); it != devices_and_missing_parts.end(); it++)
            {
                const auto& value = it->second.first;
                if (value.find(temp[i]) != value.end())
                {
                    t++;
                }
            }
            update_part_freqs[temp[i]] = t + 1;
        }

        bool exit = true;
        unordered_map<int, int> devices_and_chosen_parts;
        for (auto it = devices_and_missing_parts.begin(); it != devices_and_missing_parts.end(); it++)
        {
            it->second.second.clear();
            vector<int> cur_set(it->second.first.begin(), it->second.first.end());
            set_difference(temp.begin(), temp.end(), cur_set.begin(), cur_set.end(), back_inserter(it->second.second));
            int s = it->second.second.size();
            if (s > 0)
            {
                exit = false;
                int mi = INT_MAX;
                int neo_part = -INT_MAX;
                for (auto itt = it->second.second.begin(); itt != it->second.second.end(); itt++)
                {
                    if (update_part_freqs[*itt] < mi)
                    {
                        mi = update_part_freqs[*itt];
                        neo_part = *itt;
                    }
                    else if (update_part_freqs[*itt] == mi)
                    {
                        if (*itt < neo_part)
                        {
                            neo_part = *itt;
                        }
                    }
                }
                devices_and_chosen_parts[it->first] = neo_part;
            }
        }

        if (exit)
        {
            break;
        }

        unordered_map<int, vector<int>> chosen_devices_and_requests;
        for (auto it = devices_and_chosen_parts.begin(); it != devices_and_chosen_parts.end(); it++)
        {
            int mi = INT_MAX;
            int neo_device = -INT_MAX;
            for (auto itt = devices_and_missing_parts.begin(); itt != devices_and_missing_parts.end(); itt++)
            {
                if (itt->second.first.find(it->second) != itt->second.first.end())
                {
                    int s = itt->second.first.size();
                    if (s < mi)
                    {
                        mi = s;
                        neo_device = itt->first;
                    }
                    else if (s == mi)
                    {
                        if (itt->first < neo_device)
                        {
                            neo_device = itt->first;
                        }
                    }
                }
            }
            int s = update.size();
            if (s < mi)
            {
                mi = s;
                neo_device = 1;
            }
            else if (s == mi)
            {
                if (1 < neo_device)
                {
                    neo_device = 1;
                }
            }
            chosen_devices_and_requests[neo_device].push_back(it->first);
        }

        unordered_map<int, int> chosen_devices_and_neo_devices_with_approval;
        for (auto it = chosen_devices_and_requests.begin(); it != chosen_devices_and_requests.end(); it++)
        {
            int ma = -INT_MAX;
            int neo_device_with_approval = -INT_MAX;
            for (auto itt = it->second.begin(); itt != it->second.end(); itt++)
            {
                if (value_one_for_other[it->first][*itt] > ma)
                {
                    ma = value_one_for_other[it->first][*itt];
                    neo_device_with_approval = *itt;
                }
                else if (value_one_for_other[it->first][*itt] == ma)
                {
                    int a = devices_and_missing_parts[neo_device_with_approval].first.size();
                    int b = devices_and_missing_parts[*itt].first.size();
                    if (b < a)
                    {
                        neo_device_with_approval = *itt;
                    }
                    else if (b == a)
                    {
                        if (*itt < neo_device_with_approval)
                        {
                            neo_device_with_approval = *itt;
                        }
                    }
                }
            }
            chosen_devices_and_neo_devices_with_approval[it->first] = neo_device_with_approval;
        }

        for (auto it = chosen_devices_and_neo_devices_with_approval.begin(); it != chosen_devices_and_neo_devices_with_approval.end(); it++)
        {
            devices_and_missing_parts[it->second].first.insert(devices_and_chosen_parts[it->second]);
            int a = devices_and_missing_parts[it->second].first.size();
            int b = update.size();
            if (b == a)
            {
                timeslots_per_device_required[it->second] = timeslot_count;
            }
            value_one_for_other[it->second][it->first]++;
        }

        timeslot_count++;
    }

    for (auto it = timeslots_per_device_required.begin(); it != timeslots_per_device_required.end(); it++)
    {
        out << it->second << ' ';
    }

    in.close();
    out.close();
    return 0;
}