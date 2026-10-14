// https://github.com/kssaaaaaaaaaaan/kyopro
// https://github.com/ei1333/library/tree/dca071d33d8dbfd001e450a109c55eb6c38c2ee8
#include <bits/stdc++.h>
#include <utility>
using namespace std;
struct dsu {
    int n;
    vector<int> p;
    dsu(int n = 0) : n(n), p(n, -1) {}
    int leader(int a) { return p[a] < 0 ? a : p[a] = leader(p[a]); }
    int merge(int a, int b) {
        int x = leader(a), y = leader(b);
        if (x == y) return x;
        if (-p[x] < -p[y]) swap(x, y);
        p[x] += p[y];
        p[y] = x;
        return x;
    }
    bool same(int a, int b) { return leader(a) == leader(b); }
    int size(int a) { return -p[leader(a)]; }
    vector<vector<int>> groups() {
        vector<vector<int>> g(n), res;
        for (int i = 0; i < n; i++) g[leader(i)].push_back(i);
        for (auto& v : g)
            if (!v.empty()) res.push_back(v);
        return res;
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    struct monkey {
        int a, b;
        bool is_friend;
    };

    vector<monkey> Monkeys(m);
    for (int i = 0; i < m; ++i) {
        cin >> Monkeys[i].a >> Monkeys[i].b;
        --Monkeys[i].a;
        --Monkeys[i].b;
        char c;
        cin >> c;
        Monkeys[i].is_friend = c == 'o';
    }

    dsu DSU(n);
    for (int i = 0; i < m; ++i) {
        if (Monkeys[i].is_friend) {
            DSU.merge(Monkeys[i].a, Monkeys[i].b);
        }
    }
    if (DSU.size(0) == n) {
        cout << "No\n";
        return 0;
    }

    for (int i = 0; i < m; ++i) {
        if (!Monkeys[i].is_friend) {
            if (DSU.same(Monkeys[i].a, Monkeys[i].b)) {
                cout << "No\n";
                return 0;
            }
        }
    }

    // 二部グラフかどうか判定する
    {
        vector<vector<int>> G(n);
        for (int i = 0; i < m; ++i) {
            if (!Monkeys[i].is_friend) {
                G[Monkeys[i].a].emplace_back(Monkeys[i].b);
                G[Monkeys[i].b].emplace_back(Monkeys[i].a);
            }
        }
        vector<vector<int>> leaders(n);
        for (int i = 0; i < n; i++) leaders[DSU.leader(i)].push_back(i);
        vector<int> BorW(n, -1);
        //  vector<bool> searched(n, false);
        for (int start = 0; start < n; ++start) {
            // if (searched[start]) continue;
            if (BorW[start] != -1) continue;
            BorW[start] = 0;
            queue<pair<int, int>> que;
            que.push(make_pair(start, BorW[start]));
            while (!que.empty()) {
                auto [v, color] = que.front();
                que.pop();

                for (int nv : G[v]) {
                    if (BorW[nv] != -1) {
                        if (BorW[nv] == color) {
                            cout << "No\n";
                            return 0;
                        }

                        continue;
                    }
                    for (int nww : leaders[DSU.leader(nv)]) {
                        BorW[nww] = 1 - color;
                        que.push(make_pair(nww, 1 - color));
                    }
                }
            }
        }
        for (int i = 0; i < m; i++) {
            int a = Monkeys[i].a, b = Monkeys[i].b;
            if ((BorW[a] == BorW[b]) != Monkeys[i].is_friend) {
                cout << "No" << endl;
                return 0;
            }
        }
    }
    cout << "Yes\n";

    return 0;
}
