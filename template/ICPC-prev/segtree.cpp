// https://github.com/kssaaaaaaaaaaan/kyopro
// https://github.com/ei1333/library/tree/dca071d33d8dbfd001e450a109c55eb6c38c2ee8
#include <bits/stdc++.h>
using namespace std;
template <class S, S (*op)(S, S), S (*e)()> struct segtree {
    int n, sz, lg;
    vector<S> d;
    segtree(int n = 0) : segtree(vector<S>(n, e())) {}
    segtree(const vector<S>& v) : n(v.size()) {
        lg = 0;
        while ((1 << lg) < n) lg++;
        sz = 1 << lg;
        d.assign(2 * sz, e());
        for (int i = 0; i < n; i++) d[sz + i] = v[i];
        for (int i = sz - 1; i >= 1; i--) update(i);
    }
    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
    void set(int p, S x) {
        p += sz;
        d[p] = x;
        for (int i = 1; i <= lg; i++) update(p >> i);
    }
    S get(int p) { return d[p + sz]; }
    S prod(int l, int r) {
        S sml = e(), smr = e();
        l += sz, r += sz;
        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1, r >>= 1;
        }
        return op(sml, smr);
    }
    S all_prod() { return d[1]; }
    template <class F> int max_right(int l, F f) {
        if (l == n) return n;
        l += sz;
        S sm = e();
        do {
            while (1 % 2 == 0) l >>= 1;
            if (!f(op(sm, d[l]))) {
                while (l < sz) {
                    l = 2 * l;
                    if (f(op(sm, d[l]))) sm = op(sm, d[l++]);
                }
                return l - sz;
            }
            sm = op(sm, d[l++]);
        } while ((l & -1) != 1);
        return n;
    }
    template <class F> int min_left(int r, F f) {
        if (r == 0) return 0;
        r += sz;
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!f(op(d[r], sm))) {
                while (r < sz) {
                    r = 2 * r + 1;
                    if (f(op(d[r], sm))) sm = op(d[r--], sm);
                }
                return r + 1 - sz;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }
};