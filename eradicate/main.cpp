// P17517 [ECUSTPC 2026 Fall] 根除
// f(n) = n 去掉所有平方因子后的平方自由部分。
// 求 Σ_{i=l}^r f(i) mod 998244353，l,r ≤ 1e12，q ≤ 500。
//
// 思路：
//   n = a*b²（a 平方自由）⟺ f(n)=a。对固定 a，b 可取 1..floor(sqrt(N/a))。
//   S(N) = Σ_{n=1}^N f(n) = Σ_{b=1}^{⌊√N⌋} G(⌊N/b²⌋)，
//   其中 G(M) = Σ_{a≤M, a平方自由} a。
//   莫比乌斯反演：[a平方自由] = Σ_{d²|a} μ(d)，
//     G(M) = Σ_{d≤√M} μ(d) d² · T(⌊M/d²⌋)，T(x)=x(x+1)/2。
//   b 分块 + G(M) 缓存。
#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

const int MOD = 998244353;
const int MAXD = 1000005;           // √(1e12) = 1e6
int mu[MAXD];
int64 mu_d2[MAXD];                  // μ(d)·d² mod MOD
bool comp[MAXD];
vector<int> primes;

void sieve() {
    mu[1] = 1;
    for (int i = 2; i < MAXD; i++) {
        if (!comp[i]) { primes.push_back(i); mu[i] = -1; }
        for (int p : primes) {
            if ((int64)i * p >= MAXD) break;
            comp[i * p] = true;
            if (i % p == 0) { mu[i * p] = 0; break; }
            else mu[i * p] = -mu[i];
        }
    }
    for (int d = 1; d < MAXD; d++) {
        int64 d2 = (int64)d * d % MOD;
        mu_d2[d] = (mu[d] == 0 ? 0 : (mu[d] == 1 ? d2 : MOD - d2));
    }
}

int64 T(int64 x) {                  // x(x+1)/2 mod MOD
    if (x <= 0) return 0;
    return (x % MOD) * ((x + 1) % MOD) % MOD * ((MOD + 1) / 2) % MOD;
}

unordered_map<int64, int64> gcache;
int64 G(int64 M) {
    if (M <= 0) return 0;
    auto it = gcache.find(M);
    if (it != gcache.end()) return it->second;
    int64 res = 0;
    int64 lim = (int64)sqrtl((long double)M);
    while (lim * lim > M) lim--;
    while ((lim + 1) * (lim + 1) <= M) lim++;
    for (int64 d = 1; d <= lim; d++) {
        if (mu_d2[d] == 0) continue;
        res = (res + mu_d2[d] * T(M / (d * d))) % MOD;
    }
    gcache[M] = res;
    return res;
}

int64 S(int64 N) {
    if (N <= 0) return 0;
    int64 res = 0;
    int64 b = 1;
    while (b * b <= N) {
        int64 M = N / (b * b);
        int64 maxb = (int64)sqrtl((long double)N / M);
        while (maxb * maxb > N / M) maxb--;
        while ((maxb + 1) * (maxb + 1) <= N / M) maxb++;
        int64 cnt = (maxb - b + 1) % MOD;
        res = (res + cnt * G(M)) % MOD;
        b = maxb + 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    sieve();
    int q;
    cin >> q;
    while (q--) {
        int64 l, r;
        cin >> l >> r;
        int64 ans = (S(r) - S(l - 1) + MOD) % MOD;
        cout << ans << '\n';
    }
    return 0;
}
