#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

void solve() {
    int n, m;
    cin >> n >> m;

    vector<ull> r(m);
    for (int i = 0; i < m; i++) r[i] = rng();

    vector<ull> diff(n + 2, 0);
    for (int i = 0; i < m; i++) {
        int l, rr;
        cin >> l >> rr;
        diff[l] ^= r[i];
        diff[rr + 1] ^= r[i];
    }

    vector<ull> h(n + 1);
    ull cur = 0;
    for (int i = 1; i <= n; i++) {
        cur ^= diff[i];
        h[i] = cur;
    }

    // nxt[i] = 下一个相同签名的位置
    vector<int> nxt(n + 2, n + 1);
    unordered_map<ull, int> last;
    for (int i = n; i >= 1; i--) {
        if (last.count(h[i])) nxt[i] = last[h[i]];
        last[h[i]] = i;
    }

    // 收集区间 (i, nxt[i])
    vector<pair<int,int>> segs;
    for (int i = 1; i <= n; i++) {
        if (nxt[i] <= n) segs.push_back({i, nxt[i]});
    }

    // 去掉"包含其他区间"的区间，保留最内层叶子区间
    // 按左端点升序，从右往左保留最小右端点
    sort(segs.begin(), segs.end());
    vector<pair<int,int>> leafSegs;
    int minR = n + 1;
    for (int i = (int)segs.size() - 1; i >= 0; i--) {
        if (segs[i].second < minR) {
            leafSegs.push_back(segs[i]);
            minR = segs[i].second;
        }
    }
    reverse(leafSegs.begin(), leafSegs.end());

    int q = leafSegs.size();
    if (q == 0) {
        cout << 0 << '\n';
        return;
    }

    // 在每个叶子区间右端点前放端点 b = R - 1
    vector<int> pts;
    for (auto &s : leafSegs) {
        pts.push_back(s.second - 1);
    }
    sort(pts.begin(), pts.end());

    // 判断首区域和末区域是否有共同签名
    // 首区域 = 位置 1，末区域 = 位置 n
    // 但要注意：如果 q 偶数，需要看 h[1] 和 h[n] 是否相同
    // 更准确地说：第一个区域（最左）和最后一个区域（最右）的签名
    bool sameEnds = (h[1] == h[n]);

    vector<int> c;
    if (q % 2 == 1) {
        // 奇数：加一个端点在位置 1 前（b = 0）
        c.push_back(0);
        for (int x : pts) c.push_back(x);
    } else {
        // 偶数
        if (sameEnds) {
            // 加端点在位置 1 前（b=0）和位置 n 后（b=n）
            c.push_back(0);
            for (int x : pts) c.push_back(x);
            c.push_back(n);
        } else {
            for (int x : pts) c.push_back(x);
        }
    }

    int k = (int)c.size() / 2;
    cout << k << '\n';
    for (int i = 0; i < k; i++) {
        // 检测器覆盖 [c[i]+1, c[i+k]]
        int L = c[i] + 1;
        int R = c[i + k];
        cout << L << ' ' << R << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
}
