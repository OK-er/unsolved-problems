// 2261C - I Know About a Million Things (Codeforces Round 1128)
//
// 游戏：两人轮流删元素，合法操作 = 删一个元素，或删一组和为偶数的元素。
// 不能动者输。判断先手 Moggity 胜还是后手 Larpity 胜。
//
// SG 推导：必败态 (o,e) 只有 (0,0)、(1,1)、(3,0)、(0,3)，其余全是先手胜。
// 代码：数奇数个数 o、偶数个数 e，判断是否属于上述三个非空必败态。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int odd = 0, even = 0;
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            if (x & 1) odd++;
            else even++;
        }
        bool lose = (odd == 1 && even == 1) ||
                    (odd == 3 && even == 0) ||
                    (odd == 0 && even == 3);
        cout << (lose ? "Larpity" : "Moggity") << '\n';
    }
    return 0;
}
