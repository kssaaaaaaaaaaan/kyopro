// https://github.com/kssaaaaaaaaaaan/kyopro
// https://github.com/ei1333/library
#include <bits/stdc++.h>
#include <atcoder/all>

using namespace std;

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
    cout << fixed << setprecision(15);
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

using namespace atcoder;
typedef atcoder::modint998244353 mint;

typedef pair<mint, mint> MP;
int main() {
    string N;
    int M;
    cin >> N >> M;

    VI C(M);
    REP(i, M) cin >> C[i];
    sort(ALL(C));
    // V<mint> pow10(N.size() + 1, 1);
    // REP(i, N.size()) pow10[i + 1] = pow10[i] * 10;
    V<V<V<MP>>> dp(N.size() + 1, V<V<MP>>(1 << 10, V<MP>(2, {0, 0})));

    REP(k, 10) {
        if (k > (N[0] - '0')) break;
        if (k == (N[0] - '0')) {
            dp[1][(1 << k)][1].first += k;
            dp[1][(1 << k)][1].second = 1;
        } else {
            dp[1][(1 << k)][0].first += k;
            if (k != 0)
                dp[1][(1 << k)][0].second = 1;
            else
                dp[1][0][0].second = 1;
        }
    }
    FOR(i, 1, N.size()) {
        REP(j, 1 << 10) {
            REP(k, 10) {
                if (j != 0 || k != 0) {
                    dp[i + 1][j | (1 << k)][0].first +=
                        dp[i][j][0].first * 10 + k * dp[i][j][0].second;
                    dp[i + 1][j | (1 << k)][0].second += dp[i][j][0].second;
                } else {
                    ovi dp[i + 1][0][0].first +=
                        dp[i][0][0].first * 10 + k * dp[i][j][0].second;
                    dp[i + 1][0][0].second += dp[i][j][0].second;
                }
                if (k > (N[i] - '0')) continue;
                if (k == (N[i] - '0')) {
                    dp[i + 1][j | (1 << k)][1].first +=
                        dp[i][j][1].first * 10 + k * dp[i][j][1].second;
                    dp[i + 1][j | (1 << k)][1].second += dp[i][j][1].second;
                } else {
                    dp[i + 1][j | (1 << k)][0].first +=
                        dp[i][j][1].first * 10 + k * dp[i][j][1].second;
                    dp[i + 1][j | (1 << k)][0].second += dp[i][j][1].second;
                }
            }
        }
    }
    int mask = 0;
    REP(i, M) mask += 1 << C[i];
    mint ans = 0;
    REP(i, 1 << 10) {
        if ((i & mask) != mask) continue;
        ans += dp[N.size()][i][0].first;
        ans += dp[N.size()][i][1].first;
    }
    END(ans.val());
}