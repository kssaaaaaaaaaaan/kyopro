// https://github.com/kssaaaaaaaaaaan/kyopro
// https://github.com/ei1333/library/tree/dca071d33d8dbfd001e450a109c55eb6c38c2ee8
#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
// python3 expander.py main.cpp
// export CPLUS_INCLUDE_PATH="/path/to/ac-library-master"

using ll = long long;
using ld = long double;
using lll = __int128_t;
using ull = __uint128_t;

// using mint = modint; //mint::set_mod(M);
// using mint = modint998244353;
// using mint = modint1000000007;

template <class T> using pq = priority_queue<T>;  // 大きい順
template <class T>
using pq_g = priority_queue<T, vector<T>, greater<T>>;  // 小さい順

#define vec_unique(v) v.erase(unique(v.begin(), v.end()), v.end())  // 重複削除
#define vec_iota(v) \
    iota(v.begin(), v.end(), 0)  // 0, 1, 2, 3, ..., n - 1にセット
#define concat(a, b) a.insert(a.end(), b.begin(), b.end())
#define debug(x) cerr << #x << " = " << x << endl
#define maxvalue(array) *max_element(array.begin(), array.end())
#define minvalue(array) *min_element(array.begin(), array.end())
#define sumvalue(array) accumulate(array.begin(), array.end(), 0ll)
#define popcount(x) __builtin_popcountll(x)

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
// int dx[8] = {1, 1, 0, -1, -1, -1, 0, 1};
// int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};

#define INF 2e18
#define INF2 2e9

struct S {
    // int n;
    // int u;
    // int p;
    // int c;
    ll nu_sum;
    ll up_sum;
    ll pc_sum;
    ll cn_sum;
    ll nu_min;
    ll up_min;
    ll pc_min;
    ll cn_min;
};

using F = ll;

S op(S a, S b) {
    S res;
    // res.n = a.n + b.n;
    // res.u = a.u + b.u;
    // res.p = a.p + b.p;
    // res.c = a.c + b.c;

    res.nu_sum = a.nu_sum + b.nu_sum;
    res.up_sum = a.up_sum + b.up_sum;
    res.pc_sum = a.pc_sum + b.pc_sum;
    res.cn_sum = a.cn_sum + b.cn_sum;

    res.nu_min = min(a.nu_min, a.nu_sum + b.nu_min);
    res.up_min = min(a.up_min, a.up_sum + b.up_min);
    res.pc_min = min(a.pc_min, a.pc_sum + b.pc_min);
    res.cn_min = min(a.cn_min, a.cn_sum + b.cn_min);

    return res;
}

S e() { return {0, 0, 0, 0, 0, 0, 0, 0}; }

S mapping(F f, S x) {
    if (f == 1) {
        return {x.up_sum, x.pc_sum, x.cn_sum, x.nu_sum,
                x.up_min, x.pc_min, x.cn_min, x.nu_min};
    } else if (f == 2) {
        return {x.pc_sum, x.cn_sum, x.nu_sum, x.up_sum,
                x.pc_min, x.cn_min, x.nu_min, x.up_min};
    } else if (f == 3) {
        return {x.cn_sum, x.nu_sum, x.up_sum, x.pc_sum,
                x.cn_min, x.nu_min, x.up_min, x.pc_min};
    } else {
        return x;
    }
}

F composition(F f, F g) { return (f + g) % 4; }

F id() { return 0; }

void solve() {
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;

    lazy_segtree<S, op, e, F, mapping, composition, id> seg(n + 10);

    for (int i = 0; i < n; i++) {
        if (s[i] == 'N') {
            seg.set(i, {1, 0, 0, -1, 0, 0, 0, -1});
        } else if (s[i] == 'U') {
            seg.set(i, {-1, 1, 0, 0, -1, 0, 0, 0});
        } else if (s[i] == 'P') {
            seg.set(i, {0, -1, 1, 0, 0, -1, 0, 0});
        } else {
            seg.set(i, {0, 0, -1, 1, 0, 0, -1, 0});
        }
    }

    while (q--) {
        // cerr << q << endl;
        int type, l, r;
        cin >> type >> l >> r;
        l--;

        // cerr << type << " " << l << " " << r << endl;

        if (type == 1) {
            seg.apply(l, r, 1);
        } else {
            auto res = seg.prod(l, r);
            if (res.nu_sum == 0 && res.up_sum == 0 && res.pc_sum == 0) {
                if (res.nu_min >= 0 && res.up_min >= 0 && res.pc_min >= 0) {
                    cout << "Yes" << endl;
                } else {
                    cout << "No" << endl;
                }
            } else {
                cout << "No" << endl;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    while (t--) {
        solve();
    }
    // cout << fixed << setprecision(15) << << endl;
    return 0;
}