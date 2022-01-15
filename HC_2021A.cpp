#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
    ifstream input;
    input.open("e.txt");
    ofstream output;
    output.open("outputE.txt");

    int D, I, S, V, F;
    // D = duration of simulation.
    // I = No of intersection.
    // S = no of streets.
    // V = number of cars.
    // F = points of car.
    input >> D >> I >> S >> V >> F;
    unordered_map<string, pair<int, pair<int, int>>> streets;
    vector<string> inters[I];
    for (int i = 0; i < S; i++)
    {
        int B, E, L;
        string sname;
        input >> B >> E >> sname >> L;
        streets[sname] = make_pair(L, make_pair(B, E));
    }

    vector<string> path[V];
    unordered_set<string> ache;
    int ans = 0;
    unordered_set<int> lp;

    int sum = 0;

    for (int i = 0; i < V; i++)
    {
        sum = 0;
        int P;
        input >> P;
        while (P--)
        {
            string sname;
            input >> sname;
            path[i].push_back(sname);
            sum = sum + streets[sname].first;

            // if(ache.find(sname) == ache.end()){
            //     ache.insert(sname);
            //     int q = streets[sname].second.second;
            //     inters[streets[sname].second.second].push_back(sname);
            //     if(lp.find(q) == lp.end()){
            //         lp.insert(q);
            //         ans++;
            //     }
            // }
        }
        if (sum <= D)
        {
            for (int j = 0; j < path[i].size(); j++)
            {
                string sname = path[i][j];
                if (ache.find(sname) == ache.end())
                {
                    ache.insert(sname);
                    int q = streets[sname].second.second;
                    inters[streets[sname].second.second].push_back(sname);
                    if (lp.find(q) == lp.end())
                    {
                        lp.insert(q);
                        ans++;
                    }
                }
            }
        }
    }

    output << ans << "\n";
    for (int i = 0; i < I; i++)
    {
        int l = inters[i].size();
        if (l > 0)
        {
            output << i << "\n";
            output << l << "\n";
            for (int j = l - 1; j >= 0; j--)
            {

                output << inters[i][j] << " "
                       << "1\n";
            }
        }
    }

    return 0;
}