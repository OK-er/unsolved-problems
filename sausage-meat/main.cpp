// 2269D - What a SauSaGe! It's All Meat (Codeforces Round 1124)
//
// 题意：长度 n 的数组 a_i（0..15，4-bit）。操作：选相邻 i，同时把 a_i、a_{i+1}
//       异或上 3^k（k=0..4，即 mask 3,6,12,9,15）。"All-Meat" 值为 0,3,6,9,12,15
//       （均为偶 popcount）。问最多能让多少元素变成 All-Meat？带 q 次单点更新。
//
// 思路：
//   1. 所有 mask popcount 为偶 → 异或不改变 popcount 奇偶性 → 奇 popcount 元素永不可能
//      成为 All-Meat（上界 = popcount 偶的元素数）。
//   2. 可把 mask 施加到任意两元素（非相邻通过相邻传递，中间元素被 XOR 两次抵消）。
//   3. 任意偶 popcount 的 4-bit 数都能合成 mask（5=3^6, 10=3^9）。
//   4. 存在奇 popcount 元素时，以它为缓冲，把每个偶 popcount 元素自身异或成 0；
//      全偶时把 a_1 作缓冲清零其余，剩余 x 仅可能是 5/10，再用 3 修正即可。
//   → 上界总可达到：答案 = popcount(a_i) 为偶数的元素数。更新 O(1)。
#include <bits/stdc++.h>
using namespace std;

inline bool good(int x) { return __builtin_popcount(x) % 2 == 0; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tc;
    cin >> tc;
    while (tc--) {
        int n, q;
        cin >> n >> q;
        vector<int> a(n);
        int ans = 0;
        for (int &x : a) {
            cin >> x;
            ans += good(x);
        }
        cout << ans << '\n';
        while (q--) {
            int p, x;
            cin >> p >> x;
            --p;
            ans -= good(a[p]);
            a[p] = x;
            ans += good(a[p]);
            cout << ans << '\n';
        }
    }
    return 0;
}
