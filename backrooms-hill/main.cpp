// D. Backrooms Hill（Codeforces Round 1123 Div.2 D）
// 思路：
//   1. 操作只交换下标距离为 2 的元素 → 奇数位之间、偶数位之间分别可任意重排，
//      但奇偶两个集合的元素互不流动。每个值最终只能落在与原位置同奇偶的位置上。
//   2. 关键引理：任意 hill 数组 b 中，数值 n, n-1, ..., i 的位置集合（对每个 i）
//      必须构成一个连续的位置段。反证：若中间夹着更小的数，就会形成局部最小值，
//      与 hill（先严格增后严格减）矛盾。
//   3. 因此判定：设 pos[v] 为值 v 在原数组中的位置，记录每个值位置的奇偶性
//      （奇数位记 1，偶数位记 0）。从值 n 往下扫描后缀：
//      后缀 v..n 中的 1 的个数与 0 的个数之差的绝对值必须 <= 1，
//      否则这些值无法排进任意一个连续位置段（连续段内奇偶位置数差至多为 1）。
//      全部后缀满足 -> YES，否则 NO。复杂度 O(n)。
#include <bits/stdc++.h>
using namespace std;

bool can_become_hill(int n, const vector<int>& a) {
    vector<int> pos(n + 1);            // pos[value] = value 在 a 中的位置（1-based）
    for (int i = 1; i <= n; i++) pos[a[i]] = i;

    int cntOdd = 0, cntEven = 0;       // 当前后缀（值 v..n）中 奇数位 / 偶数位 的数量
    for (int v = n; v >= 1; v--) {
        if (pos[v] & 1) cntOdd++;
        else cntEven++;
        if (abs(cntOdd - cntEven) > 1) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> a(n + 1);
        for (int i = 1; i <= n; i++) cin >> a[i];

        cout << (can_become_hill(n, a) ? "YES" : "NO") << '\n';
    }
    return 0;
}
