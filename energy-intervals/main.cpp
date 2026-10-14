// 2269E - KiaKio and Energy Intervals (Codeforces Round 1124)
//
// 区间值 = (p_{l-1} ^ p_r) & max(a_l..a_r)，求所有 l<r 区间的最大值。
// 做法：按位贪心 18 位 + 最大笛卡尔树（LCA = 区间最大值位置）+ 小到大合并
//       维护前缀 XOR 频率数组，检查是否存在 s_x ^ s_y = M。
// 代码基于官方题解，加中文注释。
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 100, lg = 18;
int t, n, a[N], par[lg][N], pref[N], cnt[N * 2], answ = 0, maxi = 0;

// ST 表求 [l,r] 内最大值位置
int getmx(int l, int r) {
    int res = l;
    for (int i = lg - 1; i >= 0; i--) {
        if (l + (1 << i) - 1 <= r) {
            res = (a[par[i][l]] > a[res] ? par[i][l] : res);
            l += (1 << i);
        }
    }
    return res;
}

// 笛卡尔树分治：[l,r] 段，检查是否存在端点对 s_x^s_y = answ
// cnt 维护当前较大子树的前缀频率
void divide(int l, int r) {
    if (l > r) return;
    if (l == r) { cnt[pref[l]]++; return; }
    if (l == r - 1) {
        cnt[pref[l]]++; cnt[pref[r]]++;
        if ((max(a[l], a[r]) & answ) == answ)
            maxi = max(maxi, pref[l - 1] ^ pref[r]);
        return;
    }
    int mid = getmx(l, r);   // 区间最大值位置 = LCA

    if (r - mid > mid - l) {
        // 右子树更大：保留右子树频率，遍历左侧
        divide(l, mid - 1);
        for (int i = l; i < mid; i++) cnt[pref[i]]--;
        divide(mid + 1, r);
        for (int i = mid - 1; i >= l - 1; i--) {
            if (cnt[(answ ^ pref[i])] > 0 && (a[mid] & answ) == answ) maxi = answ;
            if (i == mid - 1) cnt[pref[mid]]++;   // 排除单点 (v-1,v)：先查再插 pref[mid]
        }
        for (int i = mid - 1; i >= l; i--) cnt[pref[i]]++;
    } else {
        // 左子树更大
        divide(mid + 1, r);
        for (int i = mid + 1; i <= r; i++) cnt[pref[i]]--;
        divide(l, mid - 1);
        cnt[pref[mid - 1]]--;
        cnt[pref[l - 1]]++;
        for (int i = mid; i <= r; i++) {
            if (cnt[(answ ^ pref[i])] > 0 && (a[mid] & answ) == answ) maxi = answ;
            if (i == mid) cnt[pref[mid - 1]]++;
        }
        cnt[pref[l - 1]]--;
        for (int i = mid; i <= r; i++) cnt[pref[i]]++;
    }
}

bool check() {
    maxi = 0;
    for (int j = 1; j <= n; j++) pref[j] = pref[j - 1] ^ (a[j] & answ);
    divide(1, n);
    for (int i = 1; i <= n; i++) cnt[pref[i]] = 0;
    return maxi == answ;
}

void work() {
    cin >> n;
    int mxtmp = 0, anstmp = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        mxtmp = max(mxtmp, a[i]);
        par[0][i] = i;
    }
    for (int i = 1; i <= n; i++) anstmp ^= (a[i] & mxtmp);

    // ST 表预处理
    for (int i = n; i >= 1; i--)
        for (int j = 1; j < lg; j++) {
            int x = par[j - 1][i];
            int y = par[j - 1][min(n, i + (1 << (j - 1)))];
            par[j][i] = (a[x] > a[y] ? x : y);
        }

    // 按位贪心
    for (int i = lg - 1; i >= 0; i--) {
        answ += (1 << i);
        if (!check()) answ -= (1 << i);
    }
    cout << max(answ, anstmp) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while (t--) {
        work();
        answ = 0;
        for (int i = 1; i <= n; i++) a[i] = 0, pref[i] = 0;
    }
    return 0;
}
