// https://www.hackerearth.com/practice/data-structures/trees/binary-and-nary-trees/practice-problems/algorithm/mancunian-and-colored-tree/
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, c;
    cin >> n >> c;

    int parent[n + 1];
    parent[1] = -1;
    parent[0] = -1;
    int color[n + 1];
    color[0] = -1;

    for (int i = 2; i <= n; i++)
    {
        cin >> parent[i];
    }

    for (int i = 1; i <= n; i++)
    {
        cin >> color[i];
    }

    int ans[n + 1];

    for (int i = 1; i <= n; i++)
    {
        int nowColor = color[i];
        int p = parent[i];

        while (p != -1)
        {
            int pColor = color[p];
            if (pColor == nowColor)
            {
                break;
            }
            else
            {
                p = parent[p];
            }
        }
        ans[i] = p;
    }

    for (int i = 1; i <= n; i++)
    {
        cout << ans[i] << " ";
    }

    return 0;
}