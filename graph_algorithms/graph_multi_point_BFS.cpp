// MULTIPOINT BFS
//  https://www.geeksforgeeks.org/multi-source-shortest-path-in-unweighted-graph/ : Almost Same
#include <bits/stdc++.h>
using namespace std;

void multiPointBfs(queue<int> &nodeQueue, vector<int> adj[], int hospitalDistance[], bool visited[])
{

    if (nodeQueue.empty())
    {
        return;
    }
    int now = nodeQueue.front();
    if (visited[now] == true)
    {
        cout << "Now in: " << now << " " << visited[now] << "\n";
        return;
    }
    visited[now] = true;
    cout << "Now in: " << now + 1 << "\n";
    nodeQueue.pop();

    for (int i = 0; i < adj[now].size(); i++)
    {
        int next = adj[now][i];
        cout << "Next in adj: " << next + 1 << "\n";

        if (hospitalDistance[next] == -1)
        {
            cout << "Next in queue: " << next + 1 << "\n";

            hospitalDistance[next] = hospitalDistance[now] + 1;
            nodeQueue.push(next);
        }
    }

    multiPointBfs(nodeQueue, adj, hospitalDistance, visited);
}

int main()
{
    int cities, edges;
    cin >> cities >> edges;

    vector<int> adj[cities];

    for (int i = 0; i < edges; i++)
    {
        int in, out;
        cin >> in >> out;

        adj[in - 1].push_back(out - 1);
        adj[out - 1].push_back(in - 1);
    }

    int hostpital_count;
    cin >> hostpital_count;

    bool isHospitalPresent[cities] = {false};
    queue<int> nodeQueue;
    int hospitalDistance[cities];

    for (int i = 0; i < cities; i++)
    {
        hospitalDistance[i] = -1;
        isHospitalPresent[i] = false;
    }

    for (int i = 0; i < hostpital_count; i++)
    {
        int location;
        cin >> location;
        nodeQueue.push(location - 1);
        hospitalDistance[location - 1] = 0;
    }

    multiPointBfs(nodeQueue, adj, hospitalDistance, isHospitalPresent);

    int ans = 0;
    for (int i = 0; i < cities; i++)
    {
        if (hospitalDistance[i] > ans)
        {
            ans = hospitalDistance[i];
        }
    }

    cout << ans << "\n";

    return 0;
}