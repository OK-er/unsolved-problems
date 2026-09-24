#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n, k;
        cin >> n >> k;
        string s;
        cin >> s;
        vector<pair<int, int>> obs(k);
        for (auto &[x, y] : obs) cin >> x >> y;

        // 前缀信息：
        // dx[i], dy[i]：前 i 步中 U/D/L/R 造成的确定位移（N 不计入）
        // cn[i]：前 i 步中 N 的数量
        vector<int> dx(n + 1), dy(n + 1), cn(n + 1);
        for (int i = 1; i <= n; i++) {
            dx[i] = dx[i - 1]; dy[i] = dy[i - 1]; cn[i] = cn[i - 1];
            char c = s[i - 1];
            if (c == 'U') dx[i]--;        // (x,y) -> (x-1,y)
            else if (c == 'D') dx[i]++;   // (x,y) -> (x+1,y)
            else if (c == 'L') dy[i]--;   // (x,y) -> (x,y-1)
            else if (c == 'R') dy[i]++;   // (x,y) -> (x,y+1)
            else cn[i]++;                 // N：自由选向或原地
        }

        // 关键观察：
        // 前 i 步后，确定性部分停在 (dx[i], dy[i])；每个 N 可自由移动一步或原地，
        // 因此 N 部分可产生的额外位移 (a,b) 恰为所有满足 |a|+|b| <= cn[i] 的向量
        // （多余的 N 步原地不动即可，无奇偶约束）。
        // 故障碍物 (X,Y) 在前缀 i 撞上  <=>  |X-dx[i]| + |Y-dy[i]| <= cn[i]
        bool ok = false;
        for (auto [X, Y] : obs) {
            for (int i = 1; i <= n; i++) {
                int d = abs(X - dx[i]) + abs(Y - dy[i]);
                if (d <= cn[i]) { ok = true; break; }
            }
            if (ok) break;
        }
        cout << (ok ? "Yes" : "No") << '\n';
    }
    return 0;
}
