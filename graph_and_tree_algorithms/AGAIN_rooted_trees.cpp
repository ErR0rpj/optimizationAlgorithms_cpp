// showing wrong answer
// https://www.hackerearth.com/practice/algorithms/graphs/graph-representation/practice-problems/

#include <bits/stdc++.h>
using namespace std;

void dfs(vector<int> adj[], int x, int y, int now, int values[])
{
    for (int i = 0; i < adj[now].size(); i++)
    {
        if (values[i] < y)
        {
            values[i] = values[i] + x;
        }
        dfs(adj, x, y, adj[now][i], values);
    }
}

void createAdj(vector<int> adj_temp[], vector<int> adj[], int vis[], int now)
{
    vis[now] = 1;

    for (int i = 0; i < adj_temp[now].size(); i++)
    {
        if (vis[adj_temp[now][i]] == 0)
        {
            adj[now].push_back(adj_temp[now][i]);
            createAdj(adj_temp, adj, vis, adj_temp[now][i]);
        }
    }
}

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        int n, y, q;
        cin >> n >> q >> y;

        int values[n];
        memset(values, 0, sizeof(values));
        vector<int> adj_temp[n];
        int vis[n];
        memset(vis, 0, sizeof(vis));

        for (int i = 0; i < n - 1; i++)
        {
            int u, v;
            cin >> u >> v;
            u--;
            v--;
            adj_temp[u].push_back(v);
            adj_temp[v].push_back(u);
        }

        vector<int> adj[n];
        createAdj(adj_temp, adj, vis, 0);

        while (q--)
        {
            int in;
            cin >> in;
            if (in == 0)
            {
                int v, x;
                cin >> v >> x;
                v--;

                dfs(adj, x, y, v, values);
            }
            else
            {
                int v;
                cin >> v;
                v--;
                cout << values[v] << "\n";
            }
        }
    }

    return 0;
}