#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 200005;

int spf[MAXN]; // 最小质因子

/* 线性/埃氏筛预处理最小质因子 */
void sieve() {
    for (int i = 0; i < MAXN; i++) spf[i] = i;
    for (int i = 2; 1LL * i * i < MAXN; i++) {
        if (spf[i] == i) {
            for (int j = i * i; j < MAXN; j += i) {
                if (spf[j] == j) spf[j] = i;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    sieve();

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<int> a(n);
        int mx = 0;
        for (int i = 0; i < n; i++) { cin >> a[i]; mx = max(mx, a[i]); }

        // g[x]：把 x（及操作产生的后代）全部拆到 <= k 的最少操作次数
        // 转移：第一次操作必选 x 的某个质因子 p，
        //       花 1 次得到 p 个 x/p，每个还需 g[x/p] 次
        //       g[x] = min_{p|x} (1 + p * g[x/p])；x <= k 时为 0
        vector<ll> g(mx + 1, 0);
        for (int x = k + 1; x <= mx; x++) {
            ll best = LLONG_MAX;
            int tmp = x;
            while (tmp > 1) {
                int p = spf[tmp];                 // x 的一个（不同）质因子
                best = min(best, 1 + 1LL * p * g[x / p]);
                while (tmp % p == 0) tmp /= p;    // 去重
            }
            g[x] = best;
        }

        ll ans = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] > k) ans += g[a[i]];
        }
        cout << ans << '\n';
    }
    return 0;
}
