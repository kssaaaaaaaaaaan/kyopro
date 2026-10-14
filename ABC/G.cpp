// https://github.com/kssaaaaaaaaaaan/kyopro
// https://github.com/ei1333/library
#include <bits/stdc++.h>
using namespace std;
// なんか拾ったテンプレを貼っておく
using ll = long long;
using VI = vector<int>;
using VLL = vector<ll>;
using P = pair<int, int>;
#define REP(i, n) for (int i = 0; i < (int)(n); i++)
#define FOR(i, a, b) for (ll i = a; i < (ll)(b); i++)
#define ALL(a) (a).begin(), (a).end()
constexpr int INF = 1001001001;
constexpr ll LINF = 1001001001001001001ll;
constexpr int DX[] = {1, 0, -1, 0};
constexpr int DY[] = {0, 1, 0, -1};
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
ll op(ll a, ll b) {
    if (a < 0 || b < 0) return -1;
    return a + b;
}
ll e() { return 0; }
int main() {
    int N;
    cin >> N;
    segtree<ll, op, e> segt(N + 9);
    segtree<ll, op, e> seg_odd(N + 9);
    segtree<ll, op, e> seg_even(N + 9);
    REP(i, N + 9) segt.set(i, -1);
    int Q;
    cin >> Q;
    REP(dfds, Q) {
        int T, X, Y, V;
        cin >> T >> X >> Y >> V;
        if (T == 0) {
            segt.set(X, V);
            if (X % 2 == 0)
                seg_even.set(X, V);
            else
                seg_odd.set(X, V);
        }
        if (T == 1) {
            if (X == Y) {
                cout << V << endl;
                continue;
            }
            bool flag = false;
            if (X > Y) {
                flag = true;
                swap(X, Y);
            }
            ll sum = segt.prod(X, Y);
            if (sum == -1) {
                cout << "Ambiguous" << endl;
                continue;
            }
            if ((X + 1) % 2 == 1)
                sum -= 2LL * seg_odd.prod(X + 1, Y);
            else
                sum -= 2LL * seg_even.prod(X + 1, Y);
            if ((X - Y + 1) % 2 == 0)
                cout << sum - V << endl;
            else if (flag)
                cout << sum + V << endl;
            else
                cout << V - sum << endl;
            // else if (Y == X + 1)
            //     cout << segt.prod(X, X + 1) - V << endl;
            // else
            //     cout << V - 2LL * segt.prod(X, X + 1) + sum << endl;
            // else {
            //     ll sum = segt.prod(Y, X);
            //     if (sum == -1)
            //         cout << "Ambiguous" << endl;
            //     else if (X == Y + 1)
            //         cout << segt.prod(Y, Y + 1) - V << endl;
            //     else
            //         cout << V + 2LL * segt.prod(Y, Y + 1) - sum << endl;
            // }
        }
    }
}
