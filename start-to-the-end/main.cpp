#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;

/*
 * J. Start to the End（2026 牛客多校 Day 9, cfz round）
 *
 * 核心公式：ans = Σ_{i>=A} Σ_{j>=B} C(n,i) C(m,j) · j^i · i^j  (mod 2^64)
 *   A = n-a, B = m-b（非零出度点个数下界）
 *
 * 加速：朴素双循环 O(nm) 不可行。
 *   用 Stirling 恒等式 + 二项式反演把截断双重和拆成左右两个独立部分，
 *   维度压到 <= 65（mod 2^64 下 k>=66 时 k! ≡ 0）。
 * 组合数：2-adic 分解（popcount 定 2 的幂次 + 奇数部分逆元），避免除以 2。
 * 详见 solution.md
 */

ull powdv(ull x, ull y = (1ull << 63) - 1) {
    ull ans = 1;
    while (y) { if (y & 1) ans = ans * x; y >>= 1; x = x * x; }
    return ans;
}

const int A = 65;        // 反演维度上限
const int N = 10000000;  // n,m 上限
ull di[N + 5], id[N + 5];

/* 预处理：di[i] = 1..i 去掉因子 2 后的奇数部分前缀积；id 为其逆元 */
void init() {
    di[0] = 1;
    for (int i = 1; i <= N; ++i) {
        int x = i >> __builtin_ctz(i);
        di[i] = di[i - 1] * x;
    }
    id[N] = powdv(di[N]);
    for (int i = N - 1; i >= 0; --i) {
        int x = (i + 1) >> __builtin_ctz(i + 1);
        id[i] = id[i + 1] * x;
    }
}

/* C(n,m) mod 2^64：C = 2^v * (奇数部分) */
inline ull C(int n, int m) {
    if (n < m || m < 0) return 0;
    int cnt = __builtin_popcount(m) + __builtin_popcount(n - m) - __builtin_popcount(n);
    if (cnt >= 64) return 0;
    return (di[n] * id[m] * id[n - m]) << cnt;
}

ull vz[66][66];   // S1 记忆化
int nn;

/* S1(x,y,t) = Σ_{j=0}^{y} C(x,j) t^j（部分二项式和） */
ull s1(int x, int y, int t) {
    if (y < 0) return 0;
    if (vz[t][nn - x] != 1145141919810ull) return vz[t][nn - x];
    if (x == nn - 65) {   // x 已降到 <=65：直接暴力（j>=64 时 C 含 2^64 因子）
        if (t % 2 == 0) {
            ull uu = 1, a1 = 0;
            for (int j = 0; j <= y && j <= 63; j++) { a1 += C(x, j) * uu; uu *= t; }
            return a1;
        }
        ull a1 = 0, a2 = powdv(t, y - min(y, 63));
        for (int j = min(y, 63); j >= 0; j--) {
            if (y - j == 0) a1 = 1;
            else a1 = (t + 1) * a1 + a2 * C(x - j - 1, y - j);
            a2 *= t;
        }
        return vz[t][nn - x] = a1;
    }
    // 帕斯卡递推：Σ_{j<=y} C(x,j)t^j = (t+1)Σ_{j<=y-1} C(x-1,j)t^j + C(x-1,y)t^y
    return vz[t][nn - x] = (t + 1) * s1(x - 1, y - 1, t) + C(x - 1, y) * powdv(t, y);
}

/* 一侧（左或右）的 F(l,t) = Σ_{i>=a} C(n,i) C(i,l) t^i */
struct Solver {
    ull f[A + 1][A + 1];
    void solve(int n, int a) {   // a = 非零点数下界
        nn = n;
        for (int l = 0; l <= A; l++)
            for (int t = 0; t <= A; t++) vz[l][t] = 1145141919810ull;
        memset(f, 0, sizeof(f));
        for (int l = 0; l <= A; ++l)
            for (int t = 0; t <= A; ++t) {
                ull az = C(n, l) * powdv(t, l);
                if (az == 0) { f[l][t] = 0; continue; }
                // F_l(t) = C(n,l) t^l [ (1+t)^{n-l} - S1(n-l, a-l-1, t) ]
                f[l][t] = az * (powdv(t + 1, n - l) - s1(n - l, a - l - 1, t));
            }
    }
} m1, m2;

ull c[A + 1][A + 1];   // 反演系数 c[k][t] = (-1)^{k-t} C(k,t)

int main() {
    init();
    for (int i = 0; i <= A; ++i)
        for (int j = 0; j <= i; ++j)
            c[i][j] = C(i, j) * ((i - j) % 2 ? -1ull : 1ull);

    int T;
    scanf("%d", &T);
    while (T--) {
        int n, m, a, b;
        scanf("%d%d%d%d", &n, &m, &a, &b);
        a = n - a;   // 转成非零点数下界
        b = m - b;
        m1.solve(n, a);
        m2.solve(m, b);
        ull ans = 0;
        for (int k = 0; k <= A; ++k)
            for (int l = 0; l <= A; ++l) {
                ull x = 0, y = 0;
                for (int t = 0; t <= k; ++t) x += c[k][t] * m1.f[l][t];
                for (int t = 0; t <= l; ++t) y += c[l][t] * m2.f[k][t];
                ans += x * y;
            }
        printf("%llu\n", ans);
    }
    return 0;
}
