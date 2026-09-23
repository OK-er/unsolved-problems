#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 998244353;
const int MAXS = 60;          // 每人最多去 3 家店，每家最多 20 => 总金额 <= 60
const int SZ = 2 * MAXS + 1;  // 金额差范围 [-60,60]
const int OFF = MAXS;         // 偏移

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, P, Q, M;
    cin >> N >> P >> Q >> M;
    vector<pair<int,int>> range(N);
    for (int i = 0; i < N; i++) cin >> range[i].first >> range[i].second;

    auto compute = [&](int P, int Q) -> ll {
        // dp[t][a][s]：处理完已扫描的店后，高桥 t 家、青木 a 家、
        // 金额差(高-青) = s-OFF 的方案数
        static ll dp[4][4][SZ], ndp[4][4][SZ], pref[SZ];
        memset(dp, 0, sizeof(dp));
        dp[0][0][OFF] = 1;
        for (auto [L, R] : range) {
            memset(ndp, 0, sizeof(ndp));
            for (int t = 0; t <= P; t++) {
                for (int a = 0; a <= Q; a++) {
                    // 前缀和：pref[i] = sum_{j<=i} dp[t][a][j]
                    pref[0] = dp[t][a][0];
                    for (int i = 1; i < SZ; i++) pref[i] = (pref[i-1] + dp[t][a][i]) % MOD;
                    auto seg = [&](int lo, int hi) -> ll {  // [lo,hi] 闭区间和
                        if (lo > hi) return 0;
                        lo = max(lo, 0); hi = min(hi, SZ-1);
                        if (lo > hi) return 0;
                        ll res = pref[hi];
                        if (lo > 0) res = (res - pref[lo-1] + MOD) % MOD;
                        return res;
                    };
                    // 状态继承（无人购物）
                    for (int s = 0; s < SZ; s++) ndp[t][a][s] = (ndp[t][a][s] + dp[t][a][s]) % MOD;
                    // 高桥在这家店购物：差 +w (w in [L,R])，t+1
                    if (t < P) {
                        for (int s = 0; s < SZ; s++) {
                            ll add = seg(s - R, s - L);      // 旧差 s-w ∈ [s-R, s-L]
                            if (add) ndp[t+1][a][s] = (ndp[t+1][a][s] + add) % MOD;
                        }
                    }
                    // 青木在这家店购物：差 -w (w in [L,R])，a+1
                    if (a < Q) {
                        for (int s = 0; s < SZ; s++) {
                            ll add = seg(s + L, s + R);      // 旧差 s+w ∈ [s+L, s+R]
                            if (add) ndp[t][a+1][s] = (ndp[t][a+1][s] + add) % MOD;
                        }
                    }
                }
            }
            memcpy(dp, ndp, sizeof(dp));
        }
        return dp[P][Q][OFF];
    };

    // 修改是累积的：应用修改后整棵 DP 重算
    // 复杂度：每次 O(N * (P+1)(Q+1) * SZ)，总 O(N*M*(P+1)(Q+1)*SZ) <= 2000*16*121 ≈ 3.9e6
    for (int j = 0; j < M; j++) {
        int x, A, B;
        cin >> x >> A >> B;
        range[x-1] = {A, B};
        cout << compute(P, Q) << '\n';
    }
    return 0;
}
