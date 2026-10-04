// P17515 [ECUSTPC 2026 Fall] 一分为二 2
// 选 k 拼接 c = a[1..k] + b[k+1..n]，从 c 选 m 个互不相邻元素，最大化最小选中值。
//
// 思路：二分答案 p。对固定 p：
//   - preNo[k] / preYes[k]：a[1..k] 最大不相邻选数，且 a_k 不选 / 选（<p 则不可选）。
//   - sufYes[j] / sufNo[j]：b[j..n] 最大不相邻选数，且 b_j 选 / 不选。
//   - 拼接 k 处 a_k 与 b_{k+1} 相邻，不能同选：
//       最大可选 = max(preYes[k] + sufNo[k+1],   // a_k 选，b_{k+1} 不选
//                       preNo[k] + max(sufYes[k+1], sufNo[k+1]))
//   - 边界 k=0 用 sufYes[1]（不限制 b_1），k=n 用 preL[n]。
#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

int n, m;
vector<int64> a, b;

bool check(int64 p) {
    vector<int> preNo(n + 2, 0), preYes(n + 2, 0);
    // preNo[k]: a[1..k] 最大选数且 a_k 不选；preYes[k]: 且 a_k 选
    for (int k = 1; k <= n; k++) {
        preNo[k] = max(preNo[k-1], preYes[k-1]);          // a_k 不选 = 前 k-1 最大
        if (a[k] >= p) preYes[k] = preNo[k-1] + 1;       // a_k 选 = 前 k-1 不选 a_{k-1} 基础 +1
        else preYes[k] = -1e9;                            // a_k < p 不可选
    }
    vector<int> sufYes(n + 2, 0), sufNo(n + 2, 0);
    for (int j = n; j >= 1; j--) {
        sufNo[j] = max(sufYes[j+1], sufNo[j+1]);
        if (b[j] >= p) sufYes[j] = sufNo[j+1] + 1;
        else sufYes[j] = -1e9;
    }
    // 边界 k=0：c = b[1..n]
    if (max(sufYes[1], sufNo[1]) >= m) return true;
    // 边界 k=n：c = a[1..n]
    if (max(preNo[n], preYes[n]) >= m) return true;
    // 中间 k：a[1..k] + b[k+1..n]
    for (int k = 1; k < n; k++) {
        int opt = max(preYes[k] + sufNo[k+1],
                      preNo[k] + max(sufYes[k+1], sufNo[k+1]));
        if (opt >= m) return true;
    }
    return false;
}

void solve() {
    cin >> n >> m;
    a.assign(n + 2, 0); b.assign(n + 2, 0);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    int64 lo = -1e9, hi = 1e9;
    while (lo < hi) {
        int64 mid = lo + (hi - lo + 1) / 2;
        if (check(mid)) lo = mid;
        else hi = mid - 1;
    }
    cout << lo << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}
