// M - Brackets（2026 牛客暑期多校训练营 10）
// 高可读性 AC 实现（算法与官方/他人做法一致：线段树贪心）
// 思路概要：
//   把"可翻转位置"分成两类：
//     A 型：S[i]=')' 且 T[i]='(' —— 翻后变 '('，使 [i..n) 前缀和 +2，收益 a[i]-b[i]
//     B 型：S[i]='(' 且 T[i]=')' —— 翻后变 ')'，使 [i..n) 前缀和 -2，收益 b[i]-a[i]
//   每次必须同时翻一个 A 和一个 B（括号数才守恒）。
//   一对 (l,r) 的翻法：
//     A 在左 B 在右：中间 [l,r) 前缀 +2，安全（前缀只增不减）——bestAB
//     B 在左 A 在右：中间 [l,r) 前缀 -2，要求中间最小前缀 >= 2 才安全——bestBA_safe
//   贪心：每次取"当前收益最大的一对"翻转（收益可加，逐对最优即整体最优），
//         翻 c 对得 ret[2c]；其余 k 用"S_i==T_i 的相同位置"补足，滑动窗口取 max。
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll NEG = -(1LL << 60);
const int MAXN = 500000 + 5;

int n;
char S[MAXN], T[MAXN];
int a[MAXN], b[MAXN];
int pref[MAXN];          // S 的前缀和：'('=+1, ')'=-1
int diffCnt;             // S_i != T_i 的位置数（= 2m）

struct Pt { ll v; int pos; };          // 带位置的单点收益
struct Pr { ll v; int l, r; };         // 一对 (l, r) 的总收益

struct Node {
    int tag;            // 懒标记：对 minPref 的区间加（±1 = 前缀 ±2）
    int minPref;        // 区间最小前缀和 / 2（翻 B 需保证其 >= 1，即前缀 >= 2）

    Pt mxA, mxB;        // 区间内 A 型 / B 型单点最大收益（含位置）
    Pt bestA;           // 从"区间最小前缀位置"起的后缀中最佳 A（用于跨区间安全配对）
    Pt bestB;           // 从"区间最小前缀位置"起的后缀中最佳 B

    Pr bestAB;          // A 左 B 右对：安全（中间前缀 +2），直接可执行
    Pr bestBA_any;      // B 左 A 右对：不要求安全（仅用于合并计算）
    Pr bestBA_safe;     // B 左 A 右对：中间最小前缀 >= 2，直接可执行
} seg[MAXN * 4];

void pull(int p) {
    Node &o = seg[p], &L = seg[p << 1], &R = seg[p << 1 | 1];

    o.mxA = max(L.mxA, R.mxA, [](const Pt &x, const Pt &y) { return x.v < y.v; });
    o.mxB = max(L.mxB, R.mxB, [](const Pt &x, const Pt &y) { return x.v < y.v; });
    o.minPref = min(L.minPref, R.minPref);

    // ---- bestAB：A 左 B 右（安全） ----
    o.bestAB = max(L.bestAB, R.bestAB, [](const Pr &x, const Pr &y) { return x.v < y.v; });
    if (L.mxA.v + R.mxB.v > o.bestAB.v) {
        o.bestAB = {L.mxA.v + R.mxB.v, L.mxA.pos, R.mxB.pos};
    }

    // ---- bestBA_any：B 左 A 右（任意） ----
    o.bestBA_any = max(L.bestBA_any, R.bestBA_any,
                       [](const Pr &x, const Pr &y) { return x.v < y.v; });
    if (L.mxB.v + R.mxA.v > o.bestBA_any.v) {
        o.bestBA_any = {L.mxB.v + R.mxA.v, L.mxB.pos, R.mxA.pos};
    }

    // ---- bestBA_safe：B 左 A 右（中间前缀 >= 2 才安全） ----
    // 若右子包含全局最小前缀，则"最小位置之后"的 A 都在安全区；
    // 否则最小前缀在左子，右子整体处于较高前缀，直接取右子最大 A。
    Pt rA;
    o.bestBA_safe = {NEG, -1, -1};
    if (R.minPref == o.minPref) {
        o.bestB = R.bestB;
        rA = R.bestA;
        o.bestBA_safe = max(o.bestBA_safe, R.bestBA_safe,
                            [](const Pr &x, const Pr &y) { return x.v < y.v; });
    } else {
        o.bestB = max(L.bestB, R.mxB, [](const Pt &x, const Pt &y) { return x.v < y.v; });
        rA = R.mxA;
        o.bestBA_safe = max(o.bestBA_safe, R.bestBA_any,
                            [](const Pr &x, const Pr &y) { return x.v < y.v; });
    }
    Pt lB;
    if (L.minPref == o.minPref) {
        o.bestA = L.bestA;
        lB = L.bestB;
        o.bestBA_safe = max(o.bestBA_safe, L.bestBA_safe,
                            [](const Pr &x, const Pr &y) { return x.v < y.v; });
    } else {
        o.bestA = max(L.mxA, R.bestA, [](const Pt &x, const Pt &y) { return x.v < y.v; });
        lB = L.mxB;
        o.bestBA_safe = max(o.bestBA_safe, L.bestBA_any,
                            [](const Pr &x, const Pr &y) { return x.v < y.v; });
    }
    if (rA.v + lB.v > o.bestBA_safe.v) {
        o.bestBA_safe = {rA.v + lB.v, lB.pos, rA.pos};
    }
}

void build(int p, int l, int r) {
    seg[p].tag = 0;
    if (l == r) {
        Node &o = seg[p];
        o.minPref = pref[l] / 2;
        o.bestAB = o.bestBA_any = o.bestBA_safe = {NEG, l, l};
        o.mxA = o.mxB = o.bestB = o.bestA = {NEG, l};
        if (S[l] != T[l]) {
            if (S[l] == '(')          // B 型：翻 '（' 为 ')'，收益 b-a
                o.mxB = {b[l] - a[l], l};
            else                      // A 型：翻 ')' 为 '('，收益 a-b
                o.mxA = o.bestA = {a[l] - b[l], l};
        }
    } else {
        int mid = (l + r) >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
        pull(p);
    }
}

void apply(int p, int v) {          // 区间前缀 ±2（minPref ±1）
    seg[p].tag += v;
    seg[p].minPref += v;
}

void push(int p) {
    if (seg[p].tag) {
        apply(p << 1, seg[p].tag);
        apply(p << 1 | 1, seg[p].tag);
        seg[p].tag = 0;
    }
}

void rangeAdd(int p, int l, int r, int ql, int qr, int v) {
    if (ql > qr) return;
    if (ql == l && qr == r) { apply(p, v); return; }
    push(p);
    int mid = (l + r) >> 1;
    if (qr <= mid) rangeAdd(p << 1, l, mid, ql, qr, v);
    else if (ql > mid) rangeAdd(p << 1 | 1, mid + 1, r, ql, qr, v);
    else {
        rangeAdd(p << 1, l, mid, ql, mid, v);
        rangeAdd(p << 1 | 1, mid + 1, r, mid + 1, qr, v);
    }
    pull(p);
}

void removePoint(int p, int l, int r, int x) {   // 删除位置 x（该点不能再翻）
    if (l == r) {
        seg[p].mxA = seg[p].mxB = seg[p].bestB = seg[p].bestA = {NEG, l};
    } else {
        push(p);
        int mid = (l + r) >> 1;
        if (x <= mid) removePoint(p << 1, l, mid, x);
        else removePoint(p << 1 | 1, mid + 1, r, x);
        pull(p);
    }
}

ll answer[MAXN];        // answer[2c] = 恰好翻 c 对的最大总收益（其余位置为 NEG）
int monoQ[MAXN];        // 单调队列：滑动窗口内取 ret 最大值

void solve() {
    if (scanf("%d", &n) != 1) return;
    scanf("%s", S + 1);
    scanf("%s", T + 1);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++) scanf("%d", &b[i]);

    diffCnt = 0;
    ll wt = 0;                       // 初始：S 的权重（k=0 答案）
    for (int i = 1; i <= n; i++) {
        pref[i] = pref[i - 1] + (S[i] == '(' ? 1 : -1);
        diffCnt += S[i] != T[i];
        wt += (S[i] == '(' ? a[i] : b[i]);
    }

    build(1, 1, n);
    for (int i = 0; i <= n; i++) answer[i] = NEG;
    answer[0] = wt;

    // 最多可翻 diffCnt/2 = m 对；每次贪心取全局收益最大的一对
    for (int i = 0; i < diffCnt / 2; i++) {
        ll dAB = seg[1].bestAB.v, dBA = seg[1].bestBA_safe.v;
        int l, r;
        if (dAB > dBA) {             // A 左 B 右：中间前缀 +2
            l = seg[1].bestAB.l;
            r = seg[1].bestAB.r;
            rangeAdd(1, 1, n, l, r - 1, 1);
        } else {                     // B 左 A 右：中间前缀 -2
            l = seg[1].bestBA_safe.l;
            r = seg[1].bestBA_safe.r;
            rangeAdd(1, 1, n, l, r - 1, -1);
        }
        removePoint(1, 1, n, l);     // 用过的点删除，避免重复翻
        removePoint(1, 1, n, r);
        wt += max(dAB, dBA);
        answer[(i + 1) * 2] = wt;
    }

    // 对每个 k：翻 c 对 + 用 (n-diffCnt) 个"相同位置"补足到恰好 k 个
    // 即 c ∈ [max(0,(k-(n-diffCnt))/2), k/2]，滑动窗口取 answer[2c] 最大
    int h = 1, tail = 0;
    for (int i = 0; i <= n; i++) {
        while (h <= tail && answer[i] > answer[monoQ[tail]]) tail--;
        monoQ[++tail] = i;
        while (h <= tail && i - monoQ[h] > n - diffCnt) h++;
        printf("%lld ", answer[monoQ[h]]);
    }
    puts("");
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) solve();
    return 0;
}
