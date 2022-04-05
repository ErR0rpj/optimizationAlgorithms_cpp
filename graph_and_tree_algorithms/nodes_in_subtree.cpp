#include <bits/stdc++.h>
using namespace std;

void dfs(vector<int> adj[], string &s, int now, int parent, vector<vector<int>> &dp)
{
    dp[now][s[now] - 'a']++;

    for (int i = 0; i < adj[now].size(); ++i)
    {
        if (adj[now][i] == parent)
        {
            continue;
        }
        dfs(adj, s, adj[now][i], now, dp);

        for (int j = 0; j < 26; j++)
        {
            dp[now][j] += dp[adj[now][i]][j];
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q;
    cin >> n >> q;

    string s;
    cin >> s;
    s = "0" + s;

    vector<int> adj[n + 1];

    for (int i = 1; i < n; ++i)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<vector<int>> dp(n + 1, vector<int>(26, 0));

    dfs(adj, s, 1, 0, dp);

    while (q--)
    {
        int u;
        char c;
        cin >> u >> c;

        cout << dp[u][c - 'a'] << "\n";
    }
    return 0;
}
