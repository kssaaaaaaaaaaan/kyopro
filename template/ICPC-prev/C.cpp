// https://github.com/kssaaaaaaaaaaan/kyopro
// https://github.com/ei1333/library/tree/dca071d33d8dbfd001e450a109c55eb6c38c2ee8
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
using ll = long long;
using VI = vector<int>;
using VLL = vector<ll>;
#define REP(i, n) for (int i = 0; i < (int)(n); i++)
#define FOR(i, a, b) for (ll i = a; i < (ll)(b); i++)
#define ALL(a) (a).begin(), (a).end()

template <typename T1, typename T2> inline bool chmax(T1& a, T2 b) {
    return a < b && (a = b, true);
}
int main() {
    int N, A, B;
    cin >> N >> A >> B;
    VI C(N);
    VLL U(N), V(N);
    REP(i, N) cin >> C[i] >> U[i] >> V[i];
    if (A > B) {
        swap(A, B);
        swap(U, V);
    }
    ll ans = 0;
    REP(both, A + 1) {
        // 両方買うを求める
        vector<bool> flag(N, false);
        vector<VLL> dp(N + 1, VLL(both + 1, 0));
        dp[0][0] = 0;
        REP(i, N) {
            REP(j, both + 1) {
                if (dp[i][j] == -1) continue;
                // 両方買う
                if (j + C[i] <= both)
                    chmax(dp[i + 1][j + C[i]], dp[i][j] + U[i] + V[i]);
            }
        }
        ll check = 0;
        int s = 0;
        REP(i, both + 1) {
            chmax(check, dp[N][i]);
            if (check == dp[N][i]) s = check;
        };
        for (int i = N; i > 0; i--) {
        }
    }
    cout << ans << endl;
}
