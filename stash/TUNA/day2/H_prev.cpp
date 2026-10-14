// https://github.com/kssaaaaaaaaaaan/kyopro
// https://github.com/ei1333/library/tree/dca071d33d8dbfd001e450a109c55eb6c38c2ee8
#include <bits/stdc++.h>
using namespace std;

#define For(i, a, b) for (int i = (a); i < (b); i++)
#define rep(i, n) For(i, 0, n)
#define rFor(i, a, b) for (int i = (a); i >= (b); i--)
#define ALL(v) (v).begin(), (v).end()
#define rALL(v) (v).rbegin(), (v).rend()
#define SZ(v) ((int)(v).size())

using lint = long long;
using ld = long double;

const int INF = 1001001001;
const lint LINF = 4004004003094073385LL;
// 真上から反時計回り
const int di[] = {-1, 0, 1, 0};
const int dj[] = {0, -1, 0, 1};
const int di8[] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int dj8[] = {0, -1, -1, -1, 0, 1, 1, 1};

struct SetupIo {
    SetupIo() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout << fixed << setprecision(15);
        cerr << fixed << setprecision(15);
    }
} setupio;

namespace tatsumr {

template <class T> bool chmin(T& a, const T& b) { return a > b ? a = b, 1 : 0; }
template <class T> bool chmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }
template <class T> T div_floor(T a, T b) {
    assert(b != 0);
    if (b < 0) {
        a = -a;
        b = -b;
    }
    return (a >= 0 ? a / b : (a + 1) / b - 1);
}
template <class T> T div_ceil(T a, T b) {
    assert(b != 0);
    if (b < 0) {
        a = -a;
        b = -b;
    }
    return (a > 0 ? (a - 1) / b + 1 : a / b);
}
template <class T> T mypow(T a, T b) {
    T res = 1;
    while (b) {
        if (b & 1) {
            res *= a;
        }
        a *= a;
        b >>= 1;
    }
    return res;
}
template <class T> T modpow(T a, T b, T mod) {
    T res = 1;
    while (b) {
        if (b & 1) {
            res = (res * a) % mod;
        }
        a = (a * a) % mod;
        b >>= 1;
    }
    return res;
}

}  // namespace tatsumr

using namespace tatsumr;

struct Class {
    int c, p;
    vector<int> d, t;
};

int main() {
    int X, Y, N;
    cin >> X >> Y >> N;
    vector<Class> classes;
    rep(i, N) {
        Class cl;
        cin >> cl.c >> cl.p;
        cl.d.resize(cl.p);
        cl.t.resize(cl.p);
        rep(j, cl.p) { cin >> cl.d[j] >> cl.t[j]; }
        classes.emplace_back(cl);
    }
    int get = INF;
    vector<int> ans;
    rep(bit, 1 << N) {
        int tanni = 0;
        vector<int> id;
        rep(i, N) {
            if (bit & (1 << i)) {
                id.emplace_back(i);
                tanni += classes[i].c;
            }
        }
        if (tanni + X < Y) {
            continue;
        }
        bool res = false;
        auto dfs = [&](auto dfs, int i, set<pair<int, int>> st) -> void {
            if (i == SZ(id)) {
                res = true;
                return;
            }
            if (res) return;
            rep(j, SZ(classes[id[i]].d)) {
                if (res) return;
                int day = classes[id[i]].d[j];
                int jigen = classes[id[i]].t[j];
                if (!st.count({day, jigen})) {
                    if (res) return;
                    st.insert({day, jigen});
                    dfs(dfs, i + 1, st);
                    st.erase({day, jigen});
                    if (res) return;
                }
            }
            if (res) return;
        };
        dfs(dfs, 0, {});
        if (res) {
            if (chmin(get, tanni)) {
                ans = id;
            }
        }
    }
    if (SZ(ans) == 0) {
        cout << -1 << "\n";
        return 0;
    }
    cout << SZ(ans) << "\n";
    rep(i, SZ(ans)) {
        cout << ans[i] + 1;
        if (i < SZ(ans) - 1) cout << " ";
    }
    cout << "\n";
}