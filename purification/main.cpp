// P17524 [ECUSTPC 2026 Fall] 净化行动 3
// 炮在平面上，同行/同列隔一个炮即互相攻击。每次摧毁一个"当前未被任何炮攻击"的炮，
// 问能否全部摧毁。
//
// 思路：一个炮未被攻击 ⟺ 行内孤立 AND 列内孤立。
//   行/列内孤立判定（当前该方向有 k 个炮，按坐标排序）：
//     k ≤ 2：全孤立；k = 3：仅中间那个孤立；k ≥ 4：无孤立。
//   删一个炮会改变它所在行/列的结构，可能产生新的双孤立炮 → BFS 队列。
#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    map<int, set<int>> row, col;          // row[y] = 该行所有 x；col[x] = 该列所有 y
    vector<pair<int,int>> pts(n);
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        pts[i] = {x, y};
        row[y].insert(x);
        col[x].insert(y);
    }

    auto rowAlone = [&](int y, int x) -> bool {
        auto& s = row[y];
        int sz = (int)s.size();
        if (sz <= 2) return true;
        if (sz == 3) {                       // 仅中间孤立
            auto it = s.find(x);
            return it != s.begin() && next(it) != s.end();
        }
        return false;                        // sz ≥ 4
    };
    auto colAlone = [&](int x, int y) -> bool {
        auto& s = col[x];
        int sz = (int)s.size();
        if (sz <= 2) return true;
        if (sz == 3) {
            auto it = s.find(y);
            return it != s.begin() && next(it) != s.end();
        }
        return false;
    };

    set<pair<int,int>> alive, q;
    for (auto p : pts) alive.insert(p);
    auto tryPush = [&](int x, int y) {
        if (alive.count({x, y}) && rowAlone(y, x) && colAlone(x, y))
            q.insert({x, y});
    };
    for (auto [x, y] : pts) tryPush(x, y);

    int removed = 0;
    while (!q.empty()) {
        auto [x, y] = *q.begin();
        q.erase(q.begin());
        if (!alive.count({x, y})) continue;
        alive.erase({x, y});
        removed++;
        row[y].erase(x);
        col[x].erase(y);
        // 重新检查这行和这列的所有炮
        for (int nx : row[y]) tryPush(nx, y);
        for (int ny : col[x]) tryPush(x, ny);
    }
    cout << (removed == n ? "YES" : "NO") << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}
