// https://github.com/kssaaaaaaaaaaan/kyopro
// =====================================================================
//  IntervalSet: 互いに素な半開区間 [l, r) の集合を std::map で管理
//  隣接・重なる区間は自動でマージされる。各操作は償却 O(log n)
// =====================================================================
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <class T = ll>
struct IntervalSet {
    map<T, T> mp;  // key = l, value = r で [l, r) を保持
    T total = 0;   // 覆われている長さの合計

    // x を含む区間のイテレータ。なければ end()
    auto find(T x) const {
        auto it = mp.upper_bound(x);
        if (it == mp.begin()) return mp.end();
        --it;
        return it->second > x ? it : mp.end();
    }

    bool contains(T x) const { return find(x) != mp.end(); }

    // [l, r) を丸ごと含む区間があるか
    bool covered(T l, T r) const {
        if (l >= r) return true;
        auto it = find(l);
        return it != mp.end() && it->second >= r;
    }

    // x を含む区間 [l, r)。なければ {x, x}
    pair<T, T> get(T x) const {
        auto it = find(x);
        if (it == mp.end()) return {x, x};
        return {it->first, it->second};
    }

    // [l, r) を追加する。接する区間（[0,2) と [2,5) など）も結合する
    void insert(T l, T r) {
        if (l >= r) return;
        auto it = mp.upper_bound(l);
        if (it != mp.begin() && prev(it)->second >= l) {
            --it;
            l = it->first;
            r = max(r, it->second);
        }
        while (it != mp.end() && it->first <= r) {
            r = max(r, it->second);
            total -= it->second - it->first;
            it = mp.erase(it);
        }
        mp[l] = r;
        total += r - l;
    }

    // [l, r) を取り除く。区間の途中で切れる場合は分割する
    void erase(T l, T r) {
        if (l >= r) return;
        auto it = mp.upper_bound(l);
        if (it != mp.begin() && prev(it)->second > l) --it;
        while (it != mp.end() && it->first < r) {
            auto [a, b] = *it;
            total -= b - a;
            it = mp.erase(it);
            if (a < l) mp[a] = l, total += l - a;
            if (r < b) mp[r] = b, total += b - r, it = mp.find(r);
        }
    }

    // x 以上で区間に含まれない最小の値（mex）
    T mex(T x = 0) const {
        auto it = find(x);
        return it == mp.end() ? x : it->second;
    }

    int size() const { return (int)mp.size(); }  // 区間の個数
};

// =====================================================================
//  ハマりどころ
//    - すべて半開区間 [l, r)。閉区間 [l, r] の入力なら insert(l, r + 1)。
//    - insert は「接する区間」も結合する。[0,2) と [3,5) は別区間のまま。
//      整数の閉区間で [0,1] と [2,3] を同一視したいなら +1 で半開にすれば
//      [0,2) と [2,4) になり、自然に結合される。
//    - for (auto [l, r] : s.mp) で区間を昇順に列挙できる。
// =====================================================================

int main() {
    IntervalSet<ll> s;
    s.insert(1, 3);
    s.insert(5, 8);
    s.insert(3, 5);  // [1,3) [3,5) [5,8) が結合して [1,8)
    for (auto [l, r] : s.mp) cout << "[" << l << "," << r << ") ";
    cout << "\n";                           // [1,8)
    cout << s.total << "\n";                // 7

    s.erase(4, 6);                          // [1,4) [6,8)
    for (auto [l, r] : s.mp) cout << "[" << l << "," << r << ") ";
    cout << "\n";
    cout << s.contains(4) << s.contains(6) << "\n";  // 01
    cout << s.covered(1, 4) << s.covered(1, 5) << "\n";  // 10
    auto [l, r] = s.get(7);
    cout << l << " " << r << "\n";          // 6 8
    cout << s.mex(0) << " " << s.mex(1) << " " << s.mex(6) << "\n";  // 0 4 8
    cout << s.total << " " << s.size() << "\n";  // 5 2
    return 0;
}
