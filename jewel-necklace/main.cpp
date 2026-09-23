#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    /*
     * 关键结论：K 恒等于 2，答案恒为 N - 2。
     *
     * 证明：
     * 设 G 为最大可达 gcd，存在集合 S*（|S*| >= 2）使 gcd(S*) = G。
     * S* 中任意两颗宝石 u, v：
     *   - 都是 G 的倍数（gcd(S*) = G） => gcd(u,v) >= G；
     *   - 若 gcd(u,v) > G，则 {u,v} 本身就是 gcd 更大的合法项链，
     *     与 G 是最大值矛盾 => gcd(u,v) <= G。
     * 故 gcd(u,v) = G，即任取 S* 中两颗即可达到最大美观度 G，
     * 又因题目要求至少选 2 颗，K 的最小可能值就是 2。
     */
    cout << n - 2 << '\n';
    return 0;
}
