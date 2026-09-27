// E. Clean Substrings（Codeforces Round 1123 Div.2 E）
//
// 核心推导：
//   1. beauty(t)：把二进制串 t 变成全同（clean）所需最少操作数。
//      一次操作翻转一个 clean 子串（即某个连续 run 的一段），每次最多改变两个
//      "相邻不同"的边界；目标是消除所有 d(t) 个边界。可证 beauty(t) = ceil(d(t)/2)，
//      其中 d(t) = t 中相邻字符不同的边界数。
//   2. power(s) = Σ 所有子串 t 的 beauty(t)
//               = Σ ceil(d(t)/2)
//               = ( Σ d(t) + Σ(d(t) mod 2) ) / 2
//      其中：
//        - Σ d(t)：对每个边界 i（s[i]!=s[i+1]，1<=i<=n-1），含该边界的子串数 = i*(n-i)；
//        - Σ(d(t) mod 2)：d(t) 的奇偶性等于子串两端是否不同（异或累加：
//          d mod 2 = s[l] XOR s[r]），即 = cnt0 * cnt1（一个 0 位置配一个 1 位置的子串数）。
//      故 power = (Σ_{断点i} i*(n-i) + cnt0*cnt1) / 2。
//   3. 单点翻转 s[pos]：只影响两条边界 (pos-1,pos) 与 (pos,pos+1)，
//      每条断点状态取反，贡献 += 或 -= 对应 i*(n-i)；再更新 cnt0/cnt1。O(1)。
#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n, q;
        string s;
        cin >> n >> q >> s;

        vector<int> pr(n + 1, 0);   // pr[i]=1 表示边界 i 是断点（s[i-1]!=s[i]，i=1..n-1）
        int64 sumBreak = 0;         // Σ 断点贡献：Σ i*(n-i)
        for (int i = 1; i <= n - 1; ++i) {
            if (s[i - 1] != s[i]) {
                pr[i] = 1;
                sumBreak += 1LL * i * (n - i);
            }
        }
        int cnt0 = 0, cnt1 = 0;
        for (char c : s) (c == '0' ? cnt0 : cnt1)++;

        auto power = [&]() -> int64 {
            return (sumBreak + 1LL * cnt0 * cnt1) / 2;
        };

        cout << power();
        while (q--) {
            int pos;               // 1-based 翻转位置
            cin >> pos;
            // 翻转边界 (pos-1, pos)
            if (pos != 1) {
                int i = pos - 1;
                pr[i] ^= 1;
                sumBreak += pr[i] ? 1LL * i * (n - i) : -1LL * i * (n - i);
            }
            // 翻转边界 (pos, pos+1)
            if (pos != n) {
                int i = pos;
                pr[i] ^= 1;
                sumBreak += pr[i] ? 1LL * i * (n - i) : -1LL * i * (n - i);
            }
            // 更新字符与计数
            if (s[pos - 1] == '0') {
                s[pos - 1] = '1'; cnt0--; cnt1++;
            } else {
                s[pos - 1] = '0'; cnt1--; cnt0++;
            }
            cout << ' ' << power();
        }
        cout << '\n';
    }
    return 0;
}
