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

int main() {
    int X, Y, N;
    cin >> X >> Y >> N;
    V<VI> d(N), t(N);
    V<P> classes(N);
    REP(i, N) {
        int c, p;
        cin >> c >> p;
        classes[i] = {c, p};
        REP(j, p) {
            int dd, tt;
            cin >> dd >> tt;
            d[i].push_back(dd);
            t[i].push_back(tt);
        }
    }
    int ans = INF;
    int a_bit = 0;
    REP(bit, 1 << N) {
        int C = 0;
        REP(i, N)
        if (bit & 1 << i) C += classes[i].first;
        if (C + X < Y) continue;
        set<P> check;
        bool judge = true;
        REP(i, N) {
            if (!(bit & 1 << i)) continue;
            REP(j, classes[i].second) {
                if (check.count({d[i][j], t[i][j]})) judge = false;
                check.insert({d[i][j], t[i][j]});
            }
        }
        if (judge) {
            chmin(ans, C);
            if (ans == C) a_bit = bit;
        }
    }
    if (ans == INF) END(-1);
    VI koutiku;
    REP(i, N)
    if (a_bit & 1 << i) koutiku.push_back(i + 1);
    cout << koutiku.size() << endl;
    REP(i, koutiku.size()) cout << koutiku[i] << " ";
    cout << endl;
}
