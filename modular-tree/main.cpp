// G. Modular Tree（Codeforces Round 1122 Div.3 G）
//
// 题意：根树，节点 i 初始值 a_i、模数 b_i。操作：选节点 u，把它的值加上
//       "u 所有直接子节点当前值之和"再对 b_u 取模。任意次操作，最大化所有节点值之和。
//
// 思路（叶子向上 DP + gcd 递推）：
//   关键结论：每个节点 u 的可达值集合形如 { (a_u + g_u * x) mod b_u }，
//   其中 g_u 是某个步长。叶子没有子节点，操作不影响它，g_u = b_u（值固定）。
//   对内部节点 u：
//     - 子节点的初始值之和 S_u 可以作为"每次操作加的量"，通过操作 u 不断叠加；
//     - 每个非固定子节点 v（g_v < b_v，即可变）还能让这个叠加量在 g_v 的倍数范围内浮动；
//   故 g_u = gcd(b_u, S_u, 所有非固定子节点的 g_v)。
//   算出所有 g_u 后，每个节点能达到的最大值为
//       a_u + floor((b_u - 1 - a_u) / g_u) * g_u
//   （不超过 b_u - 1 的最大可达值），全部求和即答案。
#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

vector<vector<int>> adj;
vector<int64> a, b, g;

void dfs(int u, int fa) {
    int64 gc = 0;          // gcd 累积：先初始 0，gcd(0, x) = x
    int64 childSum = 0;    // 所有子节点初始值之和
    for (int v : adj[u]) {
        if (v == fa) continue;
        dfs(v, u);
        childSum += a[v];
        if (g[v] < b[v]) gc = gcd(gc, g[v]);   // 只有可变子节点才贡献步长
    }
    gc = gcd(gc, childSum);     // 子节点初始值和也是可叠加的步长来源
    gc = gcd(gc, b[u]);         // 模 b_u 后步长受 b_u 限制
    g[u] = gc;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        a.resize(n + 1); b.resize(n + 1); g.resize(n + 1);
        adj.assign(n + 1, {});
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) cin >> b[i];
        for (int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        dfs(1, 0);
        int64 ans = 0;
        for (int i = 1; i <= n; i++) {
            // 不超过 b_i - 1 的最大可达值
            ans += a[i] + (b[i] - 1 - a[i]) / g[i] * g[i];
        }
        cout << ans << '\n';
    }
    return 0;
}
