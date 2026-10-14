// https://github.com/kssaaaaaaaaaaan/kyopro
// https://github.com/ei1333/library/tree/dca071d33d8dbfd001e450a109c55eb6c38c2ee8
#include <bits/stdc++.h>

using namespace std;
// なんか拾ったテンプレを貼っておく
using ll = long long;
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
#include <atcoder/all>
using namespace atcoder;

int main() {
    int N;
    cin >> N;
    VI A(N);
    REP(i, N) cin >> A[i];
    REP(i, N) A[i]--;
    VI posA(N);
    REP(i, N) posA[A[i]] = i;
    int M;
    cin >> M;
    V<P> act(M);
    V<VI> G(N);
    dsu uf(N);
    REP(i, M) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        act[i] = {a, b};
        if (uf.same(a, b)) continue;
        uf.merge(a, b);
        G[a].push_back(b);
        G[b].push_back(a);
    }
    map<P, int> map;
    REP(i, M) {
        map[act[i]] = i + 1;
        map[{act[i].second, act[i].first}] = i + 1;
    }
    VI ans;
    for (VI groups : uf.groups()) {
        set<int> se;
        for (int a : groups) se.insert(a);
        for (int a : groups)
            if (!se.count(A[a])) END(-1);
        if (groups.size() == 1) continue;
        VI pos_list(groups.size());
        int tmp = 0;
        function<void(int, int)> dfs0 = [&](int crt, int prev) {
            for (int next : G[crt]) {
                if (next == prev) continue;
                dfs0(next, crt);
            }
            pos_list[tmp] = crt;
            tmp++;
            return;
        };
        dfs0(groups[0], -1);

        for (int g : pos_list) {
            int s = posA[g];
            deque<int> path;
            V<bool> reached(N), searched(N);
            function<bool(int)> dfs = [&](int crt) {
                if (searched[crt]) return false;
                if (crt == g) return true;
                reached[crt] = true;
                for (int next : G[crt]) {
                    if (reached[next]) continue;
                    path.push_back(map[{crt, next}]);
                    if (dfs(next)) return true;
                    path.pop_back();
                }
                searched[crt] = true;
                return false;
            };
            if (!dfs(s)) END(-1);
            while (!path.empty()) {
                ans.push_back(path.front());
                swap(A[act[path.front() - 1].first],
                     A[act[path.front() - 1].second]);
                swap(posA[A[act[path.front() - 1].first]],
                     posA[A[act[path.front() - 1].second]]);
                path.pop_front();
            }
        }
    }
    cout << ans.size() << endl;
    for (int i : ans) cout << i << " ";
    cout << endl;
}
