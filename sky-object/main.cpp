// P17521 [ECUSTPC 2026 Fall] 天外来物
// n 颗水晶排成一行，按任意顺序采集；采集 i 时未采的邻居 (i-1, i+1) 各取反一次。
// 求最大总得分。
//
// 思路：把每条边 (i, i+1) 定向（先采的指向后采的）。节点 i 的最终符号 = (-1)^入度，
//       入度 = 比 i 先采的邻居数。路径图任意定向都无环、都有拓扑序，故每条边独立选向。
//       DP：dp[i][d] = 处理完前 i 个节点、边 i 方向为 d 时的最大得分。
//         d=0 表示 i 先于 i+1（边 i→i+1）；d=1 表示 i+1 先于 i。
//       节点 i 的入度 = [边 i-1 方向为 i-1→i] + [边 i 方向为 i+1→i]。
#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

void solve() {
    int n;
    cin >> n;
    vector<int64> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    // dp[d]：当前边方向为 d 时（d=0: i→i+1；d=1: i+1→i）的最大得分
    // 初始化：节点 1 结算（入度 = [边1方向为1]）
    int64 dp0 = +a[1];   // d=0：节点1入度 0 → +a1
    int64 dp1 = -a[1];   // d=1：节点1入度 1 → -a1

    for (int i = 2; i <= n - 1; i++) {
        int64 ndp0 = LLONG_MIN, ndp1 = LLONG_MIN;
        // prev=0（边 i-1: i-1→i，L=1）, prev=1（边 i-1: i→i-1，L=0）
        // dir=0（边 i: i→i+1，R=0）, dir=1（边 i: i+1→i，R=1）
        // 入度 = L + R；偶数贡献 +a[i]，奇数贡献 -a[i]
        // prev=0, dir=0: L=1,R=0 → 入度1 → -a[i]
        ndp0 = max(ndp0, dp0 - a[i]);
        // prev=1, dir=0: L=0,R=0 → 入度0 → +a[i]
        ndp0 = max(ndp0, dp1 + a[i]);
        // prev=0, dir=1: L=1,R=1 → 入度2 → +a[i]
        ndp1 = max(ndp1, dp0 + a[i]);
        // prev=1, dir=1: L=0,R=1 → 入度1 → -a[i]
        ndp1 = max(ndp1, dp1 - a[i]);
        dp0 = ndp0; dp1 = ndp1;
    }

    // 结算节点 n（R=0）：
    // 边 n-1 方向 0（n-1→n，L=1）→ 入度1 → -a[n]
    // 边 n-1 方向 1（n→n-1，L=0）→ 入度0 → +a[n]
    int64 ans = max(dp0 - a[n], dp1 + a[n]);
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}
