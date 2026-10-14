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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    cin >> N >> M;
    VLL P(N);
    REP(i, N) cin >> P[i];
    VLL Points(M, 0);
    V<VI> VA(M);
    V<VI> CP(N);
    REP(i, M) {
        int L;
        cin >> L;
        REP(j, L) {
            int A;
            cin >> A;
            A--;
            VA[i].push_back(A);
            CP[A].push_back(i);
            Points[i] += P[A];
        }
    }
    ll max = Points[0];
    V<bool> used(N, 0);
    V<bool> pushed(M, 0);
    priority_queue<int, vector<int>, greater<int>> pque;
    REP(i, M) {
        if (Points[i] <= max) {
            pque.push(i);
            pushed[i] = true;
        }
    }
    VI ans;
    while (!pque.empty()) {
        int front = pque.top();
        ans.push_back(front + 1);
        pque.pop();

        for (int i : VA[front]) {
            if (used[i]) continue;
            used[i] = true;
            for (int j : CP[i]) {
                Points[j] -= P[i];
                if (!pushed[j] && Points[j] <= max) {
                    pque.push(j);
                    pushed[j] = true;
                }
            }
        }
    }
    if (ans.size() != M) END(-1);
    REP(i, M) cout << ans[i] << " ";
    cout << endl;
}
