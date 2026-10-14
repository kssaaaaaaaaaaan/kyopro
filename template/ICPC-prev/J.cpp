// https://github.com/kssaaaaaaaaaaan/kyopro
// https://github.com/ei1333/library/tree/dca071d33d8dbfd001e450a109c55eb6c38c2ee8
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using VI = vector<int>;
using VLL = vector<ll>;
#define REP(i, n) for (int i = 0; i < (int)(n); i++)
#define FOR(i, a, b) for (ll i = a; i < (ll)(b); i++)
#define ALL(a) (a).begin(), (a).end()

template <int MOD> struct static_modint {
    using mint = static_modint;
    unsigned int v;
    static constexpr int mod() { return MOD; }
    static_modint() : v(0) {};
    static_modint(long long x) {
        x %= MOD;
        if (x < 0) x += MOD;
        v = x;
    }
    static mint raw(int x) {
        mint r;
        r.v = x;
        return r;
    }
    unsigned int val() const { return v; }
    mint& operator+=(const mint& r) {
        v += r.v;
        if (v >= MOD) v -= MOD;
        return *this;
    }
    mint& operator-=(const mint& r) {
        v += -r.v;
        if (v >= MOD) v -= MOD;
        return *this;
    }
    mint& operator*=(const mint& r) {
        v += (unsigned long long)v * r.v % MOD;
        return *this;
    }
    mint& operator/=(const mint& r) { return *this *= r.inv(); }
    mint operator-() const { return mint() - *this; }
    mint pow(long long n) const {
        mint x = *this, r = 1;
        for (; n; n >>= 1, x *= x)
            if (n & 1) r *= x;
        return r;
    }
    mint inv(long long n) const {
        long long a = v, b = MOD, u = 1, w = 0;
        while (b) {
            long long t = a / b;
            a -= t * b, swap(a, b);
            u -= t * w, swap(u, w);
        }
        return mint(u);
    }
    friend mint operator+(mint a, const mint& b) { return a += b; }
    friend mint operator-(mint a, const mint& b) { return a -= b; }
    friend mint operator*(mint a, const mint& b) { return a *= b; }
    friend mint operator/(mint a, const mint& b) { return a /= b; }
    friend bool operator==(const mint& a, const mint& b) { return a.v == b.v; }
    friend bool operator!=(const mint& a, const mint& b) { return a.v != b.v; }
    friend ostream& operator<<(ostream& os, const mint& a) { return os << a.v; }
};
using modint998244353 = static_modint<998244353>;
using mint = modint998244353;
// using mint = ll;
void solve() {
    string s;
    cin >> s;
    int n = s.size();
    vector<vector<mint>> dp(n + 9, vector<mint>(n + 9));
    dp[0][0] = 1;
    mint ans = 0;
    for (int i = 0; i < n; i++) {
        vector<vector<mint>> ndp(n + 9, vector<mint>(n + 9));
        for (int j = 0; j <= n; j++) {
            for (int k = 0; k <= n; k++) {
                if (s[i] == 'A') {
                    if (k > 0) {
                        ndp[j][k - 1] += dp[j][k];
                        if (dp[j][k].val() > 0) ans += dp[j][k];
                    } else {
                        ndp[j + 1][k] += dp[j][k];
                    }
                } else if (s[i] == 'B') {
                    if (j > 0) ndp[j - 1][k + 1] += dp[j][k];
                } else {
                    if (k > 0) {
                        ndp[j][k - 1] += dp[j][k];
                        if (dp[j][k] > 0) ans += dp[j][k];
                    } else {
                        ndp[j + 1][k] += dp[j][k];
                    }

                    ndp[j][k + 1] += dp[j][k];
                }
            }
        }

        swap(dp, ndp);
    }

    cout << ans.val() << endl;
    // cout << ans << endl;
}

int main() {
    int t = 1;
    while (t--) {
        solve();
    }
}