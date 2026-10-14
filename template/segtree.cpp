// https://github.com/kssaaaaaaaaaaan/kyopro
// https://github.com/ei1333/library/tree/dca071d33d8dbfd001e450a109c55eb6c38c2ee8
// =====================================================================
//  ACL segtree テンプレート（一点更新・区間取得・区間二分探索）
//  g++ -std=c++17 -I ac-library で確認済み（AtCoder なら -I 不要）
// =====================================================================
#include <bits/stdc++.h>

#include <atcoder/segtree>

using namespace std;
using namespace atcoder;
using ll = long long;

// ---------------------------------------------------------------------
//  template <class S, S (*op)(S, S), S (*e)()> class segtree;
//  op / e は「関数ポインタ」テンプレート引数なのでラムダは直接渡せない。
//  名前付き関数として定義し、用途ごとに namespace で包むのが実戦的。
//  （max_right / min_left の述語だけは実行時引数なのでラムダ可）
// ---------------------------------------------------------------------

// =====================================================================
// パターン1: 区間 max
// =====================================================================
namespace rmax {
using S = ll;
S op(S a, S b) { return max(a, b); }
S e() {
    return LLONG_MIN / 2;
}  // 単位元 = op で必ず負ける値。オーバーフロー保険で /2
using Seg = segtree<S, op, e>;
}  // namespace rmax

void demo_basic() {
    vector<ll> a = {3, 1, 4, 1, 5, 9, 2, 6};

    rmax::Seg seg(a);  // vector から O(n) 構築
    // rmax::Seg seg(8);  // ← 全要素 e() で長さ 8 を作る場合

    // prod(l, r) は半開区間 [l, r)。r は含まない。O(log n)
    cout << seg.prod(2, 5) << "\n";  // a[2..4] = {4,1,5} → 5
    cout << seg.prod(3, 4) << "\n";  // 1 要素でも OK → 1
    cout << seg.prod(2, 2) << "\n";  // 空区間は e() が返る（例外ではない）

    cout << seg.all_prod() << "\n";  // 全体。これだけ O(1) → 9

    // set(p, x) は「代入」であって加算ではない。O(log n)
    seg.set(1, 100);
    cout << seg.get(1) << "\n";      // get は O(1) → 100
    cout << seg.all_prod() << "\n";  // → 100

    // 一点加算をしたいときは get してから set する定番ムーブ
    seg.set(1, seg.get(1) + 5);
    cout << seg.get(1) << "\n";  // → 105
}

// =====================================================================
// パターン2: 区間和 + 区間二分探索（max_right / min_left）
//   これが segtree を使う最大の理由。使えると解ける問題が増える。
// =====================================================================
namespace rsum {
using S = ll;
S op(S a, S b) { return a + b; }
S e() { return 0; }
using Seg = segtree<S, op, e>;
}  // namespace rsum

void demo_binary_search() {
    vector<ll> a = {2, 3, 1, 4, 1, 5};  // 非負なので l 固定で prod は単調増加
    rsum::Seg seg(a);

    // max_right(l, f): f(prod(l, r)) が true になる最大の r を返す。O(log n)
    //   条件: f(e()) == true、かつ f が単調（true...true, false...false）
    //   r == n なら最後まで true だったということ。
    ll X = 6;
    int r = seg.max_right(0, [&](rsum::S x) { return x <= X; });
    cout << r << "\n";               // 2+3=5<=6, +1=6<=6, +4=10>6 → 3
    cout << seg.prod(0, r) << "\n";  // → 6

    // min_left(r, f): f(prod(l, r)) が true になる最小の l を返す。右端固定版。
    int l = seg.min_left(6, [&](rsum::S x) { return x <= 6; });
    cout << l << "\n";               // 5+1=6<=6, +4=10>6 → 4
    cout << seg.prod(l, 6) << "\n";  // → 6

    // 【頻出】「累積和が X を超える最初の位置」= max_right(0, x <= X)
    //   BIT の二分探索の代わりに使える。座圧 + 個数の segtree で k
    //   番目取得も同型。
}

// =====================================================================
// パターン3: 非可換なモノイド（最大部分和）
//   op(a, b) の a が左側・b が右側。順序を入れ替えると壊れる型の練習。
// =====================================================================
namespace max_subarray {
struct S {
    ll sum, pref, suf, best;  // 総和 / 左端から / 右端まで / 区間内最大
};
S op(S a, S b) {
    return S{a.sum + b.sum, max(a.pref, a.sum + b.pref),
             max(b.suf, b.sum + a.suf), max({a.best, b.best, a.suf + b.pref})};
}
S e() { return S{0, LLONG_MIN / 4, LLONG_MIN / 4, LLONG_MIN / 4}; }
S single(ll x) { return S{x, x, x, x}; }
using Seg = segtree<S, op, e>;
}  // namespace max_subarray

void demo_noncommutative() {
    vector<ll> a = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    vector<max_subarray::S> init;
    for (ll x : a) init.push_back(max_subarray::single(x));
    max_subarray::Seg seg(init);

    cout << seg.all_prod().best << "\n";  // {4,-1,2,1} → 6
    seg.set(3, max_subarray::single(-10));
    cout << seg.all_prod().best << "\n";  // → 4
}

// =====================================================================
//  モノイド設計チートシート
// ---------------------------------------------------------------------
//    区間和   : S=ll, op=a+b,      e=0
//    区間min  : S=ll, op=min(a,b), e=INF
//    区間max  : S=ll, op=max(a,b), e=-INF
//    区間gcd  : S=ll, op=gcd(a,b), e=0        （gcd(0,x)=x なので 0 が単位元）
//    区間xor  : S=ll, op=a^b,      e=0
//    行列積   : S=Matrix, op=a*b, e=単位行列   （非可換。左右を間違えない）
//    最大部分和: パターン3
//
//  ■ ハマりどころ
//    - prod は半開区間 [l, r)。閉区間で考えていると必ず 1 ずれる。
//    - サイズは構築時に固定。push_back 不可なので最初に n を確定させる。
//    - e() は「op で無視される値」。min の e に 0 を置くと当然壊れる。
//    - max_right の述語は f(e()) == true が必須。外すと assert で落ちる。
//    - 述語が単調でないと返り値は無意味（assert では検出されない）。
//    - 遅延評価（区間更新）が要るなら lazy_segtree 側を使う。
// =====================================================================

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    cout << "--- basic ---\n";
    demo_basic();
    cout << "--- max_right / min_left ---\n";
    demo_binary_search();
    cout << "--- non-commutative ---\n";
    demo_noncommutative();
    return 0;
}