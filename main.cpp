// https://github.com/kssaaaaaaaaaaan/kyopro
// https://github.com/ei1333/library/tree/dca071d33d8dbfd001e450a109c55eb6c38c2ee8
#include <bits/stdc++.h>
#include <atcoder/all>

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
using S = V<mint>;
S op(S a, S b) {
    S result(5);
    REP(i, 5) result[i] = a[i] + b[i];
    return result;
}
S e() { return {0, 0, 0, 0, 0}; }
V<mint> mapping(mint f, S x) {
    S result(5);
    mint f2 = f * f, f3 = f2 * f, f4 = f3 * f;
    result[0] = x[0];
    result[1] = x[1] + f * x[0];
    result[2] = x[2] + 2 * f * x[1] + f2 * x[0];
    result[3] = x[3] + 3 * f * x[2] + 3 * f2 * x[1] + f3 * x[0];
    result[4] = x[4] + 4 * f * x[3] + 6 * f2 * x[2] + 4 * f3 * x[1] + f4 * x[0];
    return result;
}
mint composition(mint f, mint g) { return f + g; }
mint id() { return 0; }
int main() {
    int N, Q;
    cin >> N >> Q;
    lazy_segtree<S, op, e, mint, mapping, composition, id> seg(N);
    REP(i, N) {
        int Ai;
        cin >> Ai;
        mint t = Ai;
        seg.set(i, {1, t, t * t, t * t * t, t * t * t * t});
    }
    REP(q, Q) {
        int type;
        cin >> type;
        if (type == 1) {
            int l, r, x;
            cin >> l >> r >> x;
            seg.apply(--l, r, x);
        } else if (type == 2) {
            int l, r, k;
            cin >> l >> r >> k;
            V<mint> ans = seg.prod(--l, r);
            cout << ans[k].val() << endl;
        }
    }
}