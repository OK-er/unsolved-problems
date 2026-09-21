#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

/*
 * 新鲜子数组（Fresh Subarrays）
 *
 * 思路：枚举右端点 r，O(n) 一遍扫描。
 *   y = 到 r 为止最靠右的前缀最大值位置（区间最大值必须来自它）
 *   p = 到 r 为止最靠右的后缀极小点（a[p] < p 右边全部元素）
 *   以 r 为右端点的合法左端点个数 = min(y, p)
 * 详见 solution.md
 */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    // suf[i] = a[i+1..n] 的最小值（i 右侧全部元素的最小值）
    // 边界：i = n 时右侧无元素，设为 +∞（排列元素最大为 n，用 n+1 即可）
    vector<int> suf(n + 2, n + 1);
    for (int i = n; i >= 1; i--) {
        suf[i] = min(suf[i + 1], a[i]);
    }

    ll ans = 0;
    int curMax = 0; // 扫描过程中遇到的前缀最大值
    int y = 0;      // 最靠右的前缀最大值下标
    int p = 0;      // 最靠右的"后缀极小点"下标（a[p] 小于其右侧全部）

    for (int i = 1; i <= n; i++) {
        // 1) 更新 y：a[i] 成为新的前缀最大值
        if (a[i] > curMax) {
            curMax = a[i];
            y = i;
        }

        // 2) 更新 p：a[i] 小于其右侧所有元素（a[i] < min(a[i+1..n])）
        if (a[i] < suf[i + 1]) {
            p = i;
        }

        // 3) 以 i 为右端点的合法左端点个数 = min(y, p)
        ans += min(y, p);
    }

    cout << ans << '\n';
    return 0;
}
