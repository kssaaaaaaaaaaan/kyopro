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

int main() {
    int N, Q;
    cin >> N >> Q;
    VI lastR(N, -1);
    VI lastC(N, 0);
    fenwick_tree<int> fC(Q + 9), fR(Q + 9);
    ll ans = 0;
    FOR(q, 1, Q + 1) {
        int t;
        cin >> t;
        if (t == 1) {
            int R;
            cin >> R;
            R--;
            if (lastR[R] == -1) {
                ans += N;
            } else {
                ll tmp = fC.sum(lastR[R], Q + 9);
                ans += tmp;
                fR.add(lastR[R], -1);
            }
            lastR[R] = q;
            fR.add(q, 1);
        } else {
            int C;
            cin >> C;
            C--;
            ll tmp = fR.sum(lastC[C], Q + 9);
            ans -= tmp;
            fC.add(lastC[C], -1);

            lastC[C] = q;
            fC.add(q, 1);
        }
        cout << ans << endl;
    }
}
