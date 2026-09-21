#include <bits/stdc++.h>
using namespace std;

/*
 * 删除连通点集（牛客周赛 Round 162）
 *
 * 思路：最大化保留节点数，答案 = n - 最大保留数。
 * 核心：枚举"分界边"。若子树 u 包含全部 R（或全部 B），
 *       则子树外部全部是另一种颜色、天然单色可整侧保留；
 *       子树内部先递归处理成单色块。
 * dfs(u) 返回子树 u 内部处理后能保留的节点数。
 * 详见 solution.md
 */
const int MAXN = 2e5 + 10;

int n;
string s;
vector<int> G[MAXN];

int s0, s1;        // 整棵树 R / B 的总数
int C0[MAXN], C1[MAXN]; // 子树中 R / B 的个数
int cnt[MAXN];     // 子树节点总数
int ans = 0;       // 最大保留节点数

int dfs(int u, int pre)
{
    // 统计自身颜色
    if (s[u] == 'R') C0[u]++;
    else C1[u]++;
    cnt[u] = 1;

    int sum = 0; // 子树内部处理后能保留的节点数
    for (int v : G[u])
    {
        if (v == pre) continue;
        sum += dfs(v, u);
        C0[u] += C0[v];
        C1[u] += C1[v];
        cnt[u] += cnt[v];
    }

    // 关键：子树包含全部 R 或全部 B
    // => 子树外全是另一种颜色，天然单色，整侧保留
    if (C0[u] == s0 || C1[u] == s1)
    {
        int total_save = (n - cnt[u]) + sum;
        ans = max(ans, total_save);
    }

    // 当前整棵子树单色：整块保留，向父节点提供 1 个单色块
    if (C0[u] == 0 || C1[u] == 0)
        sum++;

    return sum;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> s;
    s = " " + s; // 下标从 1 开始

    for (int i = 1; i <= n; i++)
    {
        if (s[i] == 'R') s0++;
        else s1++;
    }

    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    dfs(1, 0);
    cout << n - ans << '\n';
    return 0;
}
