// https://github.com/kssaaaaaaaaaaan/kyopro
// https://github.com/ei1333/library/tree/dca071d33d8dbfd001e450a109c55eb6c38c2ee8
#include <bits/stdc++.h>
// Thank you for 過去の記憶！

using namespace std;
// なんか拾ったテンプレを貼っておく
using ll = long long;
using lll = __int128;
using VI = vector<int>;
using VLL = vector<ll>;
using P = pair<int, int>;
using PLL = pair<ll, ll>;
#define REP(i, n) for (int i = 0; i < (int)(n); i++)
#define FOR(i, a, b) for (ll i = a; i < (ll)(b); i++)
#define ALL(a) (a).begin(), (a).end()
constexpr int INF = 1001001001;
constexpr ll LINF = 1001001001001001001ll;
constexpr double EPS = 1e-15;
constexpr int DX[] = {1, 0, -1, 0};
constexpr int DY[] = {0, 1, 0, -1};
template <class T> using V = vector<T>;
template <typename T1, typename T2> inline bool chmax(T1& a, T2 b) {
    return a < b && (a = b, true);
}

template <typename T1, typename T2> inline bool chmin(T1& a, T2 b) {
    return a > b && (a = b, true);
}
void print() { cout << '\n'; }
template <typename T> void print(const T& t) { cout << t << '\n'; }

template <> void print<double>(const double& t) {
    cout << fixed << setprecision(10);
    cout << t << '\n';
}
template <typename Head, typename... Tail>
void print(const Head& head, const Tail&... tail) {
    cout << head << ' ';
    print(tail...);
}
#define END(...)            \
    {                       \
        print(__VA_ARGS__); \
        return 0;           \
    }
template <typename T> ostream& operator<<(ostream& os, const vector<T>& v) {
    for (int i = 0; i < (int)v.size(); i++) {
        os << v[i] << (i + 1 != (int)v.size() ? " " : "");
    }
    return os;
}

template <typename T> istream& operator>>(istream& is, vector<T>& v) {
    for (T& in : v) is >> in;
    return is;
}

// 配列をprintで出力しようとするとCEになるので注意！！
#include <atcoder/all>
using namespace atcoder;
typedef atcoder::modint998244353 mint;

int solve() {
    int N;
    cin >> N;
    string S;
    cin >> S;
    V<V<mint>> dp(N + 1, V<mint>(4, 0));
    V<V<mint>> p(N + 1, V<mint>(4, 0));
    dp[0][0] = 0;
    p[0][0] = 1;
    REP(i, N) {
        REP(j, 4) {
            if (p[i][j] == 0) continue;
            // 雨乞いなし
            if (S[i] == 'C' || j == 3) {
                if (S[i] == 'C') {
                    dp[i + 1][min(j + 1, 3)] += dp[i][j] + 1;
                    p[i + 1][min(j + 1, 3)] += p[i][j];
                } else {
                    dp[i + 1][0] += dp[i][j];
                    p[i + 1][0] += p[i][j];
                }
                continue;
            }
            // 雨乞いあり
            dp[i + 1][j + 1] += (dp[i][j] + 1) / 2;
            p[i + 1][j + 1] += p[i][j] / 2;
            dp[i + 1][0] += dp[i][j] / 2;
            p[i + 1][0] += p[i][j] / 2;
        }
    }
    mint ans = 0;
    // REP(i, 4) ans += dp[N][i] * p[N][i];
    FOR(i, 1, N + 1)
    FOR(j, 1, 4) ans += p[i][j];
    END(ans.val());
}
int main() {
    int T;
    cin >> T;
    REP(i, T) solve();
}
