// P17518 [ECUSTPC 2026 Fall] 凸包
// n 个开口向下的二次不等式 a_i x^2 + b_i x + c_i > 0，问是否存在整数 x 同时满足。
// 思路：每个不等式解集为 (r1_i, r2_i)（开区间）；全部取交集 (L, R)，
//       L = max r1_i，R = min r2_i。判断开区间内是否有整数，候选 x = floor(L)+1
//       （若该值 < R），再用精确整数运算代入验证，杜绝浮点边界误差。
#include <bits/stdc++.h>
using namespace std;
using int64 = long long;
using ld = long double;

void solve() {
    int n;
    cin >> n;
    vector<int64> a(n), b(n), c(n);
    ld L = -1e18L, R = 1e18L;
    bool impossible = false;
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i] >> c[i];
        int64 d = b[i] * b[i] - 4 * a[i] * c[i];   // 判别式
        if (d <= 0) { impossible = true; continue; } // 开口向下且无实根 → 恒负
        ld sd = sqrtl((ld)d);
        // a < 0：小根 = (-b + sqrt(d)) / (2a)，大根 = (-b - sqrt(d)) / (2a)
        ld r1 = ((ld)-b[i] + sd) / (2.0L * a[i]);
        ld r2 = ((ld)-b[i] - sd) / (2.0L * a[i]);
        L = max(L, r1);
        R = min(R, r2);
    }
    if (impossible) { cout << "NO\n"; return; }
    // 候选整数：严格大于 L 的最小整数
    int64 x = (int64)floorl(L) + 1;
    if ((ld)x >= R) { cout << "NO\n"; return; }      // 候选不在交集中
    // 精确验证（兜底浮点边界误差）
    for (int i = 0; i < n; i++) {
        int64 val = a[i] * x * x + b[i] * x + c[i];
        if (val <= 0) { cout << "NO\n"; return; }
    }
    cout << "YES\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}
