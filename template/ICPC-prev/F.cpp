// https://github.com/kssaaaaaaaaaaan/kyopro
// https://github.com/ei1333/library/tree/dca071d33d8dbfd001e450a109c55eb6c38c2ee8
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <class S,
          S (*op)(S, S),
          S (*e)(),
          class F,
          S (*mapping)(F, S),
          F (*composition)(F, F),
          F (*id)()>
struct lazy_segtree {
    int n, sz, lg;
    vector<S> d;
    vector<F> lz;
    lazy_segtree(int n = 0) : lazy_segtree(vector<S>(n, e())) {}
    lazy_segtree(const vector<S>& v) : n(v.size()) {
        lg = 0;
        while ((1 << lg) < n) lg++;
        sz = 1 << lg;
        d.assign(2 * sz, e());
        lz.assign(sz, id());
        for (int i = 0; i < n; i++) d[sz + i] = v[i];
        for (int i = sz - 1; i >= 1; i--) update(i);
    }

    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }

    void all_apply(int k, F f) {
        d[k] = mapping(f, d[k]);
        if (k < sz) lz[k] = composition(f, lz[k]);
    }

    void push(int k) {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = id();
    }

    void set(int p, S x) {
        p += sz;
        for (int i = lg; i >= 1; i--) push(p >> i);
        d[p] = x;
        for (int i = 1; i <= lg; i++) update(p >> i);
    }

    S get(int p) {
        p += sz;
        for (int i = lg; i >= 1; i--) push(p >> i);
        return d[p];
    }

    S prod(int l, int r) {
        if (l == r) return e();
        l += sz;
        r += sz;
        for (int i = lg; i >= 1; i--) {
            if (((l >> i) << i) != l) push(1 >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }
        S sml = e(), smr = e();
        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1, r >>= 1;
        }
        return op(sml, smr);
    }
    S all_prod() { return d[1]; }
    void apply(int p, F f) {
        p += sz;
        for (int i = lg; i >= 1; i--) push(p >> i);
        d[p] = mapping(f, d[p]);
        for (int i = i; i <= lg; i++) update(p >> i);
    }
    void apply(int l, int r, F f) {
        if (l == r) return;
        l += sz, r += sz;
        for (int i = lg; i >= 1; i--) {
            if (((l >> i) << i) != 1) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }
        int l2 = l, r2 = r;
        while (l < r) {
            if (l & 1) all_apply(l++, f);
            if (r & 1) all_apply(--r, f);
            l >>= 1, r >>= 1;
        }
        l = l2, r = r2;
        for (int i = 1; i <= lg; i++) {
            if (((l >> i) << i) != l) update(l >> i);
            if (((r >> i) << i) != r) update((r - 1) >> i);
        }
    }
};

using S = ll;
using F = ll;

S op(S a, S b) { return max(a, b); }

S e() { return -1e9; }

S mapping(F f, S x) { return x + f; }

F composition(F f, F g) { return f + g; }

F id() { return 0; }

pair<ll, int> dfs(const vector<vector<int>>& graph, int u, int par) {
    pair<ll, int> res = make_pair((ll)0, u);
    for (auto v : graph[u]) {
        if (v == par) continue;
        auto next = dfs(graph, v, u);
        next.first += 1;
        res = max(res, next);
    }
    return res;
}

pair<int, int> tree_diamiter(const vector<vector<int>>& graph) {
    pair<ll, int> p = dfs(graph, 0, -1);
    pair<ll, int> q = dfs(graph, p.second, -1);
    return {p.second, q.second};
}

vector<bool> namo;
int len = 0;

void namori(const vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> deg(n);
    for (int i = 0; i < n; i++) {
        for (auto next_v : graph[i]) {
            deg[next_v]++;
        }
    }

    queue<int> que;
    for (int i = 0; i < n; i++) {
        if (deg[i] == 1) que.push(i);
    }

    while (!que.empty()) {
        auto v = que.front();
        que.pop();
        deg[v] = 0;
        namo[v] = false;
        len--;
        for (auto next_v : graph[v]) {
            deg[next_v]--;
            if (deg[next_v] == 1) {
                que.push(next_v);
            }
        }
    }

    return;
}

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> graph(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    auto [a, b] = tree_diamiter(graph);

    graph[a].push_back(b);
    graph[b].push_back(a);

    len = n;
    namo.resize(n, true);
    namori(graph);

    auto dfs2 = [&](auto dfs2, int v, int par) -> ll {
        ll res = 0;
        for (auto next_v : graph[v]) {
            if (next_v == par) continue;
            if (namo[next_v]) continue;

            res += dfs2(dfs2, next_v, v) + 2;
        }
        return res;
    };

    auto dfs3 = [&](auto dfs3, int v, int par) -> ll {
        ll res = 0;
        for (auto next_v : graph[v]) {
            if (next_v == par) continue;
            if (namo[next_v]) continue;

            res = max(res, dfs3(dfs3, next_v, v) + 1);
        }

        return res;
    };

    ll res = len - 1;
    for (int i = 0; i < n; i++) {
        if (namo[i]) {
            res += dfs2(dfs2, i, -1);
            // cerr << dfs2(dfs2, i, -1) << endl;
            // mx = max(mx, dfs3(dfs3, i, -1));
        }
    }

    // cerr << res << endl;

    vector<int> vec;
    auto dfs4 = [&](auto dfs4, int v, int par) -> void {
        if (vec.size() == len) return;
        vec.push_back(v);
        for (auto next_v : graph[v]) {
            if (next_v == par) continue;
            if (!namo[next_v]) continue;

            dfs4(dfs4, next_v, v);
        }
    };

    for (int i = 0; i < n; i++) {
        if (namo[i]) {
            dfs4(dfs4, i, -1);
            break;
        }
    }

    int sz = vec.size();
    lazy_segtree<S, op, e, F, mapping, composition, id> seg(2 * sz);

    for (int i = 0; i < 2 * sz; i++) {
        ll mx = dfs3(dfs3, vec[i % sz], -1);
        seg.set(i % sz, mx);
    }

    int l = len / 2;
    int add = 0;
    for (int i = 1; i <= l; i++) {
        seg.set(i, seg.get(i) - add);
        seg.set(i + sz, seg.get(i + sz) - add);
        add++;
    }

    for (int i = l / 2 + 1; i < sz; i++) {
        add--;
        seg.set(i, seg.get(i) - add);
        seg.set(i + sz, seg.get(i + sz) - add);
    }

    // for (int i = 0; i < sz; i++) {
    //     cerr << seg.get(i) << " ";
    // }
    // cerr << endl;

    ll ans = 2e18;
    for (int i = 0; i < sz; i++) {
        ll mx = seg.prod(i + 1, i + sz);
        ll res2 = res - seg.get(i) - mx;
        // cerr << seg.get(i) << " " << mx << endl;
        ans = min(ans, res2);
        if (i % 2 == 0) seg.apply(i + 2, i + 2 + l - 1, 1);
        if (i % 2 == 0) seg.apply(i + 2 + l - 1, i + 2 + l - 1 + l - 1, -1);

        if (i % 2 != 0) seg.apply(i + 2, i + 2 + l - 2, 1);
        if (i % 2 != 0) seg.apply(i + 2 + l - 1, i + 2 + l - 1 + l - 1, -1);
    }

    cout << ans << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}