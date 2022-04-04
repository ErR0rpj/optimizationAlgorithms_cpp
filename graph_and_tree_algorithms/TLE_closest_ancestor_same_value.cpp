// TLE
// https://www.hackerearth.com/practice/data-structures/trees/binary-and-nary-trees/practice-problems/algorithm/mancunian-and-colored-tree/
#include <bits/stdc++.h>
using namespace std;

void dfs(vector<int> adj[], int color[], int ans[], int now, vector<int> lowestParent)
{
    ans[now] = lowestParent[color[now]];
    lowestParent[color[now]] = now;
    // cout << now << " " << color[now] << "\n";

    for (int i = 0; i < adj[now].size(); i++)
    {
        dfs(adj, color, ans, adj[now][i], lowestParent);
    }
}

int main()
{
    int n, c;
    cin >> n >> c;

    vector<int> adj[n];
    int color[n];

    for (int i = 1; i < n; i++)
    {
        int u;
        cin >> u;
        u--;

        adj[u].push_back(i);
        // cout << u << " " << i << "\n";
    }

    for (int i = 0; i < n; i++)
    {
        int u;
        cin >> u;
        color[i] = u - 1;
    }

    int ans[n];
    memset(ans, -1, sizeof(ans));

    vector<int> lowestParent(c, -2);

    dfs(adj, color, ans, 0, lowestParent);

    for (int i = 0; i < n; i++)
    {
        cout << ans[i] + 1 << " ";
    }

    return 0;
}