#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;
    int s, t;
    cin >> s >> t;

    vector<vector<pair<int, int>>> g(n);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].push_back({b, c});
        g[b].push_back({a, c});   // 双向航线
    }

    // dist[v][used]：从 s 到 v，已经免费使用了 used 条航线的最少花费
    vector<vector<int>> dist(n, vector<int>(k + 1, INF));
    priority_queue<tuple<int, int, int>,
                   vector<tuple<int, int, int>>,
                   greater<tuple<int, int, int>>> pq;

    dist[s][0] = 0;
    pq.push({0, s, 0});

    while (!pq.empty()) {
        auto [d, v, used] = pq.top();
        pq.pop();
        if (d != dist[v][used]) continue;   // 过期状态
        for (auto [to, w] : g[v]) {
            // 1) 付费搭乘这条航线
            if (dist[to][used] > d + w) {
                dist[to][used] = d + w;
                pq.push({dist[to][used], to, used});
            }
            // 2) 使用一次免费额度搭乘这条航线
            if (used < k && dist[to][used + 1] > d) {
                dist[to][used + 1] = d;
                pq.push({dist[to][used + 1], to, used + 1});
            }
        }
    }

    // 免费次数可以少于 k，取所有使用次数下的最小值
    int ans = INF;
    for (int u = 0; u <= k; u++) ans = min(ans, dist[t][u]);
    cout << ans << '\n';
    return 0;
}
