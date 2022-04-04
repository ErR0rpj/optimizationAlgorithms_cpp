// THe solution here is wrong, do it again.
// https://www.hackerearth.com/practice/algorithms/graphs/graph-representation/practice-problems/approximate/tzp-5a83020f/

#include <bits/stdc++.h>
using namespace std;

void dfs(vector<int> adj[], int vis[], vector<int> &ans, int now)
{
    vis[now] = 1;

    for (int i = 0; i < adj[now].size(); i++)
    {
        if (vis[adj[now][i]] == 0)
        {

            dfs(adj, vis, ans, adj[now][i]);
        }
    }
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<int> adj[n + 1];

    for (int i = 0; i < m; i++)
    {
        int u, v, c, g;
        cin >> u >> v >> c >> g;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> ans;
    int vis[n + 1];
    memset(vis, 0, sizeof(vis));

    dfs(adj, vis, ans, 1);

    cout << ans.size() << "\n";
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << " ";
    }

    return 0;
}