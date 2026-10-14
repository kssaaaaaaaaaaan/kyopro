// https://github.com/kssaaaaaaaaaaan/kyopro
// https://github.com/ei1333/library/tree/dca071d33d8dbfd001e450a109c55eb6c38c2ee8
#include <bits/stdc++.h>
#include <algorithm>

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

double d(pair<double, double> u, pair<double, double> v) {
    return sqrt((v.first - u.first) * (v.first - u.first) +
                (v.second - u.second) * (v.second - u.second));
}

P op1(P a, P b) {
    if (a.second < b.second)
        return a;
    else
        return b;
}
P e1() { return {INF, INF}; }
double op2(double a, double b) { return a + b; }
double e2() { return 0; }
int main() {
    int N;
    cin >> N;
    V<pair<double, double>> Points(N);
    REP(i, N) {
        double X, Y;
        cin >> X >> Y;
        Points[i] = {X, Y};
    }
    vector<VI> G(N);
    double sum = 0;
    REP(i, N - 1) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        G[u].push_back(v);
        G[v].push_back(u);
        sum += 2 * d(Points[u], Points[v]);
    }

    // オイラーツアーをやりたい！
    V<int> visit(2 * N), depth(N), in(N, INF), out(N, INF);
    V<double> ecost1(2 * N), ecost2(2 * N);
    function<int(int, int, int, int)> dfs = [&](int time, int crt, int prev,
                                                int dep) {
        visit[time] = crt;
        depth[crt] = dep;
        if (prev != -1) {
            ecost1[time] = d(Points[crt], Points[prev]);
            ecost2[time] = d(Points[crt], Points[prev]);
        }
        in[crt] = time;
        for (int next : G[crt]) {
            if (next == prev) continue;
            time = dfs(time + 1, next, crt, dep + 1);
            visit[time] = crt;
        }
        if (prev != -1) ecost2[time + 1] = -d(Points[crt], Points[prev]);
        out[crt] = time + 1;
        return time + 1;
    };
    dfs(0, 0, -1, 0);
    segtree<P, op1, e1> LCA_seg(2 * N);
    segtree<double, op2, e2> ecost2_seg(2 * N);
    REP(i, 2 * N) {
        LCA_seg.set(i, {visit[i], depth[visit[i]]});
        ecost2_seg.set(i, ecost2[i]);
    }
    int Q;
    cin >> Q;
    function<double(int)> pe = [&](int x) {
        return ecost2_seg.prod(0, in[x] + 1);
    };
    REP(query, Q) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        double ans = sum;
        int LCA = LCA_seg.prod(min(in[u], in[v]), max(out[u], out[v])).first;
        double cost = pe(u) + pe(v) - 2 * pe(LCA);
        ans -= cost;
        ans += min(cost, d(Points[u], Points[v]));
        cout << fixed << setprecision(15);
        cout << ans << endl;
    }
}
