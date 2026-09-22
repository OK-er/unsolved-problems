#include <bits/stdc++.h>
using namespace std;

/*
 * D. Falling Concrete (Codeforces 2266D)
 *
 * 思路：寻找不变量 v = 高度 - 下标。
 *   - 移动段 j -> i：新高度 a[j]-(j-i)，新下标 i，v 不变；
 *   - 被跨过的段：高度+1、下标+1，v 仍不变。
 * 因此任意操作下每块路面的 v 值守恒，可以任意重排。
 * 若干块放在连续位置 p..p+k-1 且等高，要求它们的 v 值构成连续整数。
 * 答案 = v 数组（排序去重后）最长连续段长度。
 * 详见 solution.md
 */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<long long> v(n);
        for (int i = 0; i < n; i++) {
            long long a;
            cin >> a;
            v[i] = a - (i + 1); // 1-indexed 下标
        }

        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());

        int ans = 1, cur = 1;
        for (size_t i = 1; i < v.size(); i++) {
            if (v[i] == v[i - 1] + 1) {
                cur++;
                ans = max(ans, cur);
            } else {
                cur = 1;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
