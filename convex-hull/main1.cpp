
#include<bits/stdc++.h>
#define int ll
#define a first
#define b second
#define pb push_back
#define popb pop_back()
#define bg begin()
#define ed end()
#define all(x) (x).bg,(x).ed
#define lc(x) ((x)<<1LL)
#define rc(x) (((x)<<1LL)|1LL)

#define rng(i, a, b) for (int i = int (a); i < int (b); i++)
#define rep(i, b) rng(i, 0, b)

#ifdef LOCAL
#define dmp(x) cerr << __LINE__ << " " << #x << " " << x  << endl
#else
#define dmp(x) void(0);
#endif

using namespace std;using ll = long long;
using ull = uint64_t;
using pii = pair<int, int>;
template<typename T>
    using vc = vector<T>;
/**/
ostream &operator<<(ostream &os, const pii &p){
    return os << "{" << p.a << "," << p.b << "}";
}
template<typename T>ostream &operator<<(ostream &os, const vc<T> &v){
    os<<'{';
    for(auto i:v)os<<i<<',';
    return os<<'}';
}


constexpr int maxn = 1e6+5;



int n;
int a, b, c;
int f(int x){return a*x*x+b*x+c;}
void slv (){
    cin >> n;

    int lx = LLONG_MIN, rx = LLONG_MAX;
    bool fg = 0;
    rep(_,n){
        cin >> a >> b >> c;
        if(fg)continue;
        int dt = b * b - 4*a*c;
        if(dt < 0) {fg = 1; continue;}
        int x1 = floor((-b + sqrt(dt)) / 2 / a);
        // dmp(x1);
        int x2 = ceil((-b - sqrt(dt)) / 2 / a);
        // dmp(x2);
        if(f(x1) > 0) lx = max(lx, x1);
        else if(f(++x1) > 0) lx = max(lx, x1);
        else {fg = 1;continue;}
        if(f(x2) > 0) rx = min(rx, x2);
        else if(f(--x2) > 0) rx = min(rx, x2);
        else {fg = 1;continue;}
    }
    // dmp(lx);dmp(rx);
    if(fg || lx > rx){
        cout << "No"<<'\n';
    }else{
        cout << "Yes" << '\n';
    }
}

signed main (){
    cin.tie(0)->sync_with_stdio(0);
    int _ = 1;
    cin >> _;
    while (_--){
        slv();
    }
    
}
