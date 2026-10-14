// https://github.com/kssaaaaaaaaaaan/kyopro
// https://github.com/ei1333/library/tree/dca071d33d8dbfd001e450a109c55eb6c38c2ee8
#include <bits/stdc++.h>
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