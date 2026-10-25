#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    if (n % 2 == 1) {
        cout << -1 << '\n';
        return 0;
    }
    vector<int> p(n + 1);
    p[1] = n;
    for (int i = 2; i <= n; i++) {
        if (i % 2 == 0) p[i] = i - 1;
        else p[i] = n - (i - 1);
    }
    for (int i = 1; i <= n; i++) cout << p[i] << " \n"[i == n];
    return 0;
}
