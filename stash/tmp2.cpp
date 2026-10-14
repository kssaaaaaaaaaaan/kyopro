// https://github.com/kssaaaaaaaaaaan/kyopro
// https://github.com/ei1333/library/tree/dca071d33d8dbfd001e450a109c55eb6c38c2ee8
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using VI = vector<int>;
#define REP(i, n) for (int i = 0; i < (int)(n); i++)
#define FOR(i, a, b) for (int i = a; i < (int)(b); i++)
const int MOD = 998244353;
vector<ll> kaizyo(2000000, 1);

pair<ll, ll> inv_gcd(ll a, ll b) {
    a = (a % b + b) % b;
    if (a == 0) return {b, 0};
    ll s = b, t = a, m0 = 0, m1 = 1;
    while (t) {
        ll u = s / t;
        s -= t * u, m0 -= m1 * u;
        swap(s, t), swap(m0, m1);
    }
    if (m0 < 0) m0 += b / s;
    return {s, m0};
}
ll inv_mod(ll x, ll m) { return inv_gcd(x, m).second; }
ll binom(int a, int b) {
    return (((kaizyo[a] * inv_mod(kaizyo[b], MOD)) % MOD) *
            inv_mod(kaizyo[a - b], MOD)) %
           MOD;
}

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    ll ans = 1;
    int cntCK = 0;
    int cntP = 0;
    FOR(i, 1, 2000000) kaizyo[i] = (kaizyo[i - 1] * i) % MOD;
    REP(i, n) {
        if (s[i] == 'P')
            cntP++;
        else if (s[i] == 'C') {
            if (i + 1 < n && s[i + 1] == 'K') {
                i += 1;
                cntCK++;
            } else if (i + 2 < n && s[i + 1] == 'P' && s[i + 2] == 'K') {
                i += 2;
                cntCK++;
                cntP++;
            } else {
                ll ttmp = 0;
                REP(j, cntP + 1) {
                    if (cntCK < j) break;
                    ll tmp = binom(cntCK, j);
                    tmp %= MOD;
                    tmp *= kaizyo[cntCK + cntP - j];
                    tmp %= MOD;
                    tmp *= inv_mod(kaizyo[cntCK], MOD);
                    tmp %= MOD;
                    tmp *= inv_mod(kaizyo[cntP - j], MOD);
                    tmp %= MOD;
                    ttmp += tmp;
                    ttmp %= MOD;
                }
                if (ttmp == 0) continue;
                ans *= ttmp;
                ans %= MOD;
                cntP = 0;
                cntCK = 0;
            }
        } else {
            ll ttmp = 0;
            REP(j, cntP + 1) {
                if (cntCK < j) break;
                ll tmp = binom(cntCK, j);
                tmp %= MOD;
                tmp *= kaizyo[cntCK + cntP - j];
                tmp %= MOD;
                tmp *= inv_mod(kaizyo[cntCK], MOD);
                tmp %= MOD;
                tmp *= inv_mod(kaizyo[cntP - j], MOD);
                tmp %= MOD;
                ttmp += tmp;
                ttmp %= MOD;
            }
            if (ttmp == 0) continue;
            ans *= ttmp;
            ans %= MOD;
            cntP = 0;
            cntCK = 0;
        }
    }
    ll ttmp = 0;
    REP(j, cntP + 1) {
        if (cntCK < j) break;
        ll tmp = binom(cntCK, j);
        tmp %= MOD;
        tmp *= kaizyo[cntCK + cntP - j];
        tmp %= MOD;
        tmp *= inv_mod(kaizyo[cntCK], MOD);
        tmp %= MOD;
        tmp *= inv_mod(kaizyo[cntP - j], MOD);
        tmp %= MOD;
        ttmp += tmp;
        ttmp %= MOD;
    }
    if (ttmp != 0) ans *= ttmp;
    ans %= MOD;
    cntP = 0;
    cntCK = 0;

    cout << ans << endl;
}

int main() {
    int t = 1;
    while (t--) {
        solve();
    }
}