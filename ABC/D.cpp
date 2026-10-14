// https://github.com/kssaaaaaaaaaaan/kyopro
// https://github.com/ei1333/library
#include <bits/stdc++.h>

#include <functional>
#include <queue>
using namespace std;

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
// PBDSを使うためのヘッダーと名前空間
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

int main() {
    vector<VI> A(4, VI(4, 0));
    int Ain = 0;
    REP(i, 4) {
        REP(j, 4) {
            cin >> A[i][j];
            Ain += A[i][j] << (i * 4 + j);
        }
    }
    // vector<VI> G(4, VI(4, 0));
    int ans = 0;
    set<int> s;
    REP(i, 1 << 16) {
        int tmp = i;
        if ((Ain & tmp) != Ain) continue;
        dsu uf(16);
        int cnt = 0;
        int end = -1;
        REP(j, 16) {
            if ((tmp & 1) != 0) {
                cnt++;
                if (j % 4 != 3 && (tmp & 2) != 0) uf.merge(j, j + 1);
                if (j < 12 && (tmp & 16) != 0) uf.merge(j, j + 4);
                end = j;
            }
            tmp /= 2;
        }
        if (end == -1 || uf.size(end) != cnt) continue;
        tmp = i;
        // REP(i, 4) {
        //     REP(j, 4) {
        //         if ((tmp & 1) != 0)
        //             cout << 1 << " ";
        //         else
        //             cout << 0 << " ";
        //         tmp /= 2;
        //     }
        //     cout << endl;
        // }
        ans++;
    }
    END(ans);
}