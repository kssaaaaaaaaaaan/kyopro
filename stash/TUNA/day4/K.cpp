// https://github.com/kssaaaaaaaaaaan/kyopro
// https://github.com/ei1333/library/tree/dca071d33d8dbfd001e450a109c55eb6c38c2ee8
#include <bits/stdc++.h>
#include <algorithm>
#include <queue>

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

int main() {
    int N, M, K;
    cin >> N >> M >> K;
    int A, B;
    cin >> A >> B;
    VLL C(K);
    REP(i, K) cin >> C[i];
    VI MST_edge;
    V<pair<int, P>> edges(M);
    REP(i, M) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        chmin(w, A);
        edges[i] = {w, {u, v}};
    }
    sort(ALL(edges));
    dsu uf(N);
    ll cost0 = 0;
    REP(i, M) {
        P edge;
        int w;
        tie(w, edge) = edges[i];
        int u, v;
        tie(u, v) = edge;
        if (uf.same(u, v)) continue;
        uf.merge(u, v);
        cost0 += w;
        MST_edge.push_back(w);
    }
    reverse(ALL(MST_edge));
    VLL diff(N - 1, 0);
    VLL edge_sum(N, 0);
    V<lll> diff_sum(N, 0);
    int diff_r = N;
    REP(i, N - 1) {
        diff[i] = (ll)B * MST_edge[i] - A;
        if (diff[i] <= 0) {
            diff_r = i;
            break;
        }
    }
    REP(i, N - 1) edge_sum[i + 1] = edge_sum[i] + MST_edge[i];
    REP(i, N - 1) diff_sum[i + 1] = diff_sum[i] + diff[i];
    for (ll Ci : C) {
        if (B == 1) {
            cout << max(cost0 - Ci, 0ll) << endl;
            continue;
        }
        ll ok = 0, ng = cost0 + 1;
        while (abs(ok - ng) > 1) {
            lll mid = (ok + ng) / 2;
            lll tmp = B * mid;
            lll tmp0 = tmp;
            int r = upper_bound(ALL(edge_sum), mid) - edge_sum.begin();
            if (r > diff_r) r = diff_r + 1;
            int l = r - 1;
            if (l >= 0) chmin(tmp, tmp0 - diff_sum[l]);
            if (l != diff_r && r != N)
                chmin(tmp, tmp0 - diff_sum[r] - edge_sum[r] + mid +
                               (lll)B * (edge_sum[r] - mid));
            if (tmp <= Ci)
                ok = mid;
            else
                ng = mid;
        }
        cout << cost0 - ok << endl;
    }
}
