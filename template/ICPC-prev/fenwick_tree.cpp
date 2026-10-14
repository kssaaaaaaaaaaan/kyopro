// https://github.com/kssaaaaaaaaaaan/kyopro
// https://github.com/ei1333/library/tree/dca071d33d8dbfd001e450a109c55eb6c38c2ee8
#include <bits/stdc++.h>
using namespace std;

template <class T> struct fenwick_tree {
    int n;
    vector<T> d;
    fenwick_tree(int n = 0) : n(n), d(n, 0) {}
    void add(int p, T x) {
        for (p++; p <= n; p += p & -p) d[p - 1] += x;
    }
    T sum(int r) {
        T s = 0;
        for (; r > 0; r -= r & -r) s += d[r - 1];
        return s;
    }
    T sum(int l, int r) { return sum(r) - sum(l); }
};