// https://github.com/kssaaaaaaaaaaan/kyopro
// https://github.com/ei1333/library
#include <bits/stdc++.h>
#include <atcoder/convolution.hpp>

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

int main() {
    ll N, A, B, C;
    ll X;
    cin >> N >> A >> B >> C >> X;
    ll cnt = 0;
    FOR(i, 1, N + 1) {
        FOR(j, 1, N + 1) {
            ll tmp = X - A * i - B * j;
            if (tmp % C != 0) continue;
            if (1 <= tmp / C && tmp / C <= N) {
                cnt++;
                // cerr << i << " " << j << " " << tmp / C << endl;
            }
        }
    }
    END(cnt);
}