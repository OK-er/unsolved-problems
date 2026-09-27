// F. MEX Replacement（Codeforces Round 1122 Div.3 F）
//
// 题意：多重集以压缩形式给出（值 x_i 出现 y_i 次）。一次操作选任意非空子集，
//       删除它们并插入它们的 MEX。问任意过程中能出现的最大数。
//
// 思路（二分答案 + 反向需求推导）：
//   检查目标值 M 是否可达。反向看：要造出 1 个 M，就需要 0..M-1 各至少 1 份。
//   设 q = 当前值需要的副本数（初始 q=1，即要 1 个 M），从大到小处理每个值 x：
//     - 若初始有 c >= q 个 x：用掉 q 个，多余 c-q 存为 extra；
//     - 若 c < q：缺 q-c 个 x，每缺一个 x 副本，就又需要 0..x-1 各 1 份，
//       故 q ← q + (q-c) = 2q - c。
//   连续缺失 d 个值时 q 直接乘 2^d。多余的正数可单独取其子集把 MEX 变成 0（攒 extra）。
//   处理到 0 时：初始 0 的数量 + 所有 extra >= q 则 M 可达。
//   若 M 可达，则所有更小值都可达（造 M 的过程中必然经过它们），可二分。
#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

// 检查目标值 mid 是否可达；total = 初始多重集元素总数（need 超过 total 即不可行）
bool canMake(int64 mid, vector<pair<int64, int64>>& a, int64 total) {
    int64 need = 1;          // 需要的当前值副本数
    int64 extra = 0;         // 多余副本数（可全部 MEX 成 0）
    int64 prev = mid;        // 上一个处理的值
    for (auto [x, c] : a) {
        // 中间缺失 (prev - x - 1) 个值：每缺一个，需求翻倍
        if (prev > x) {
            int64 gap = prev - x - 1;
            if (gap > 0) {
                // 翻倍后需求超过总元素数则不可行，同时防溢出
                if (gap >= 60 || need > total >> gap) return false;
                need <<= gap;
            }
        }
        if (x == 0) {        // 处理到 0
            extra += c;
            break;
        }
        if (c >= need) {
            extra += c - need;   // 够用，攒多余
        } else {
            need = need * 2 - c; // 不足：q = 2q - c
            if (need > total) return false;
        }
        prev = x;
    }
    return extra >= need;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<pair<int64, int64>> a(n);
        int64 lo = 0, total = 0;
        for (int i = 0; i < n; i++) {
            cin >> a[i].first >> a[i].second;
            lo = max(lo, a[i].first);   // 至少能出现当前最大值
            total += a[i].second;
        }
        sort(a.rbegin(), a.rend());     // 按值从大到小
        if (a.back().first != 0) a.push_back({0, 0});  // 补一个 0 计数

        int64 hi = lo + 100;            // bonus：远超 max_x 后需求爆炸，只需搜附近
        while (lo < hi) {
            int64 mid = (lo + hi + 1) / 2;
            if (canMake(mid, a, total)) lo = mid;
            else hi = mid - 1;
        }
        cout << lo << '\n';
    }
    return 0;
}
