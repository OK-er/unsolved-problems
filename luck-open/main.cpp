#include <bits/stdc++.h>
using namespace std;

const long long MOD = 998244353;
const int MAXT = 64;

long long modpow(long long a, long long e) {
    long long r = 1;
    while (e) { if (e & 1) r = r * a % MOD; a = a * a % MOD; e >>= 1; }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // maxX[t] = 对所有 T=t 的 j，最大分子 x_j（用 long double 比较大小）
    // 同时保存 mod 形式的 x_j
    vector<long double> maxF(MAXT + 1, -1e18); // maxF[t] = max x_j / 2^t
    vector<long long> bestXmod(MAXT + 1, 0);    // 对应的 x_j mod MOD
    vector<long long> bestXint(MAXT + 1, 0);   // 对应的 x_j（实际值，用 __int128 不好存，这里用 long double 近似）

    long double bestF = -1e18;
    int bestT = 1;
    long long bestX = 0;

    // 从后往前
    for (int i = n - 1; i >= 0; i--) {
        // dp[i] = max(只选 i: F = a[i]/2, T=1, x=a[i])
        //         接某个 T=t 的 j: F = x_j/2^t + a[i]/2^{t+1}, T = t+1, x = a[i] + 2*x_j
        long double bestFi = (long double)a[i] / 2.0L;
        int bestTi = 1;
        long long bestXi = a[i];

        for (int t = 1; t <= MAXT; t++) {
            if (maxF[t] < 0) continue;
            long double F = maxF[t] + (long double)a[i] / (1LL << (t + 1));
            if (F > bestFi) {
                bestFi = F;
                bestTi = t + 1;
                // x = a[i] + 2 * x_j，但 x_j 可能很大，用 mod 计算
                // 实际分子 = a[i] + 2 * x_j（整数）
                // 我们只需要最终的 x mod MOD 和 T
                // x mod MOD = (a[i] mod MOD + 2 * bestXmod[t]) mod MOD
                bestXi = (a[i] % MOD + 2 * bestXmod[t]) % MOD;
            }
        }

        // 更新 maxF[bestTi]
        long double newF = bestFi;
        if (newF > maxF[bestTi]) {
            maxF[bestTi] = newF;
            bestXmod[bestTi] = bestXi;
        }

        if (bestFi > bestF) {
            bestF = bestFi;
            bestT = bestTi;
            bestX = bestXi;
        }
    }

    // 答案 = x / 2^T mod MOD = x * inv(2^T) mod MOD
    long long inv2T = modpow(2, bestT);
    inv2T = modpow(inv2T, MOD - 2);
    long long ans = bestX % MOD * inv2T % MOD;
    cout << ans << '\n';
    return 0;
}
