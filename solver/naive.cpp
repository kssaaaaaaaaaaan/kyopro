// https://github.com/kssaaaaaaaaaaan/kyopro
// https://github.com/ei1333/library
#include <bits/stdc++.h>
#include <atcoder/all>

using namespace std;

namespace atcoder {
template <class T, internal::is_modint_t<T>* = nullptr>
ostream& operator<<(ostream& os, const T& x) {
    return os << x.val();
}
}  // namespace atcoder

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

using namespace atcoder;
typedef atcoder::modint998244353 mint;

int main() {
    int N;
    cin >> N;
    int M;
    cin >> M;
    VI C(M);
    REP(i, M) cin >> C[i];
    sort(ALL(C));
    mint ans = 0;
    int mask = 0;
    REP(i, M) mask += 1 << C[i];

    REP(i, N + 1) {
        int tmp = i;
        int check = 0;
        while (tmp != 0) {
            int k = tmp % 10;
            tmp /= 10;
            check = check | (1 << k);
        }
        if ((mask & check) != mask) continue;
        cerr << i << endl;
        ans += i;
    }
    END(ans.val());
}