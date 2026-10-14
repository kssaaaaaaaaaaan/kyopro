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
    int diff = B - A;
    vector<vector<VLL>> dp(N + 1, vector<VLL>(A + 1, VLL(diff + 1, -1)));
    dp[0][0][0] = 0;
    REP(i, N) {
        REP(j, A + 1) {
            REP(k, diff + 1) {
                if (dp[i][j][k] == -1) continue;
                // 両方買わない
                chmax(dp[i + 1][j][k], dp[i][j][k]);
                // 両方買う
                if (j + C[i] <= A)
                    chmax(dp[i + 1][j + C[i]][k], dp[i][j][k] + U[i] + V[i]);
                // 片方買う
                REP(l, A - j + 1) {
                    if (C[i] <= l) break;
                    if (k + C[i] - l <= diff)
                        chmax(dp[i + 1][j + l][k + C[i] - l],
                              dp[i][j][k] + V[i]);
                }
            }
        }
    }
    ll ans = 0;
    REP(i, A + 1) { REP(j, diff + 1) chmax(ans, dp[N][i][j]); }

    cout << ans << endl;
}