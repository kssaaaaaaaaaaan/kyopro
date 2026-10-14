// https://github.com/kssaaaaaaaaaaan/kyopro
// https://github.com/ei1333/library/tree/dca071d33d8dbfd001e450a109c55eb6c38c2ee8
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
template <typename T1, typename T2>
inline bool chmax(T1& a, T2 b) {
    return a < b && (a = b, true);
}

template <typename T1, typename T2>
inline bool chmin(T1& a, T2 b) {
    return a > b && (a = b, true);
}
void print() { cout << '\n'; }
template <typename T>
void print(const T& t) {
    cout << t << '\n';
}

template <>
void print<double>(const double& t) {
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
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
    for (int i = 0; i < (int)v.size(); i++) {
        os << v[i] << (i + 1 != (int)v.size() ? " " : "");
    }
    return os;
}

template <typename T>
istream& operator>>(istream& is, vector<T>& v) {
    for (T& in : v) is >> in;
    return is;
}

// 配列をprintで出力しようとするとCEになるので注意！！
#include <atcoder/all>
using namespace atcoder;
typedef atcoder::modint998244353 mint;

int main() {
    string X, Y;
    cin >> X >> Y;
    int Q;
    cin >> Q;
    ll sX = X.size(), sY = Y.size();
    vector<VLL> bX(30), bY(30);
    REP(i, sX) bX[X[i] - 'a'].push_back(i);
    REP(i, sY) bY[Y[i] - 'a'].push_back(i);
    vector<pair<ll, ll>> fib(91);
    fib[0] = {1, 0};
    fib[1] = {0, 1};
    FOR(i, 2, 91)
    fib[i] = {fib[i - 1].first + fib[i - 2].first,
              fib[i - 1].second + fib[i - 2].second};
    char c;
    function<ll(ll, ll, ll, int)> dfs = [&](ll l, ll r, ll crt, int level) {
        // left .. level-1, right .. level-2
        if (level == 0) {
            //[l,r)に含まれる文字を答える
            l -= crt, r -= crt;
            l--, r--;
            int cnt = lower_bound(ALL(bX[c - 'a']), r) - bX[c - 'a'].begin();
            cnt -= lower_bound(ALL(bX[c - 'a']), l) - bX[c - 'a'].begin();
            return (ll)cnt;
        }
        if (level == 1) {
            l -= crt, r -= crt;
            l--, r--;
            int cnt = lower_bound(ALL(bY[c - 'a']), r) - bY[c - 'a'].begin();
            cnt -= lower_bound(ALL(bY[c - 'a']), l) - bY[c - 'a'].begin();
            return (ll)cnt;
        }
        // OF注意
        ll mid = fib[level - 1].first * sX + fib[level - 1].second * sY;
        if (2 * 1e18 / sX < fib[level - 1].first) mid = 2 * 1e18;
        if (2 * 1e18 / sX < fib[level - 1].second) mid = 2 * 1e18;
        ll l2 = fib[level - 2].first * sX + fib[level - 2].second * sY;
        // どちらかを完全に包含
        if (l == crt || (crt + mid) == r) {
            // level-1中の文字数
            return (ll)(bX[c - 'a'].size() * fib[level - 1].first +
                        bY[c - 'a'].size() * fib[level - 1].second);
        }
        if (l == (crt + mid) || r == (crt + mid + l2)) {
            // level-2中の文字数
            return (ll)(bX[c - 'a'].size() * fib[level - 2].first +
                        bY[c - 'a'].size() * fib[level - 2].second);
        }
        // 完全に左
        if (r < (crt + mid)) return dfs(l, r, crt, level - 1);
        // 中途半端
        else if (l <= (crt + mid))
            return dfs(l, crt + mid, crt, level - 1) +
                   dfs(crt + mid, r, crt + mid, level - 2);

        // 完全に右
        return dfs(l, r, crt + mid, level - 2);
    };
    REP(q, Q) {
        ll L, R;
        cin >> L >> R;
        cin >> c;
        cout << dfs(L, R + 1, 1, 5) << endl;
    }
}
