// https://github.com/kssaaaaaaaaaaan/kyopro
// https://github.com/ei1333/library/tree/dca071d33d8dbfd001e450a109c55eb6c38c2ee8
#include <bits/stdc++.h>
#include <algorithm>
#include <string>

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

int calc(int x) {
    int score = 0;
    int tmp = x;
    int p2 = 1;
    int j = to_string(x).size();
    REP(k, 10 - j - 1) p2 *= 2;
    REP(k, j) {
        score += (tmp % 10) * p2;
        p2 *= 2;
        tmp /= 10;
    }
    return score;
}
int main() {
    int N;
    cin >> N;
    VI A(N);
    REP(i, N) cin >> A[i];
    V<mint> pow2(N * 10 + 9, 1);
    REP(i, N * 10 + 9 - 1) pow2[i + 1] = pow2[i] * 2;
    sort(ALL(A), [&](int a, int b) { return calc(a) < calc(b); });

    int sum = 0;
    mint ans = 0;
    // string koutiku;
    REP(i, N) {
        ll score = 0;
        ll kouho = A[i];
        int selected = to_string(kouho).size();
        ll tmp = kouho;
        int p2 = 1;
        REP(k, selected) {
            score += (tmp % 10) * p2;
            p2 *= 2;
            tmp /= 10;
        }
        //  koutiku = to_string(kouho) + koutiku;
        ans += score * pow2[sum];
        sum += selected;
    }
    // cout << koutiku << endl;
    END(ans.val());
}