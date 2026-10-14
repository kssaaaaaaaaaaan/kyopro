// https://github.com/kssaaaaaaaaaaan/kyopro
// https://github.com/ei1333/library/tree/dca071d33d8dbfd001e450a109c55eb6c38c2ee8
// =====================================================================
//  ACL lazy_segtree テンプレート（区間更新・区間取得）
//  g++ -std=c++17 -I ac-library で確認済み（AtCoder なら -I 不要）
//  上から順に「S/F が単純 → 番兵が要る → S に情報を足す → 非可換」の順。
// =====================================================================
#include <bits/stdc++.h>

#include <atcoder/lazysegtree>

using namespace std;
using namespace atcoder;
using ll = long long;
constexpr ll LINF = 1001001001001001001ll;
// ---------------------------------------------------------------------
//  lazy_segtree<S, op, e, F, mapping, composition, id>
//    S  : 値のモノイド        op(a, b), e()
//    F  : 作用素のモノイド     composition(f, g), id()
//    mapping(f, x)     : x に f を作用させた結果
//    composition(f, g) : g を先に、f を後に適用する合成写像（= f∘g）
//
//  満たすべき条件:
//    mapping(id(), x) == x
//    mapping(f, op(a, b)) == op(mapping(f, a), mapping(f, b))   ← これが本質
//  → 「区間まとめて作用させた結果」が計算できないなら S
//  に情報を足す（パターン3）
// ---------------------------------------------------------------------

// =====================================================================
// パターン1: 区間加算 × 区間 min    ← まずこれをコピペする
//   S も F も ll。min は区間長に依存しないので構造体が要らない最軽量ケース。
//   min→max、加算→xor など、同じ骨格のまま差し替えられる。
// =====================================================================
namespace add_min {
using S = ll;
using F = ll;

S op(S a, S b) { return min(a, b); }
S e() { return LINF; }
S mapping(F f, S x) { return x + f; }
F composition(F f, F g) { return f + g; }
F id() { return 0; }
using Lazy = lazy_segtree<S, op, e, F, mapping, composition, id>;
}  // namespace add_min

void demo_add_min() {
    add_min::Lazy seg(vector<add_min::S>{5, 3, 8, 1, 9});
    // add_min::Lazy seg(n);  // ← 全要素 e() で長さ n を作る場合

    cout << seg.prod(0, 5) << "\n";  // 半開区間 [0,5)。r は含まない → 1

    seg.apply(3, 5, 10);             // [3,5) に +10 → {5,3,8,11,19}。O(log n)
    cout << seg.prod(0, 5) << "\n";  // → 3
    cout << seg.prod(3, 5) << "\n";  // → 11

    seg.apply(1, 100);               // 一点作用の overload(p, f) → a[1] += 100
    cout << seg.get(1) << "\n";      // → 103
    cout << seg.all_prod() << "\n";  // O(1) → 5

    seg.set(0, 0);                   // 遅延を伝播したうえで代入
    cout << seg.all_prod() << "\n";  // → 0
}

// =====================================================================
// パターン2: 区間代入（update）× 区間 min
//   「何もしない」を表す番兵が要るケース。composition の向きがここで効く。
// =====================================================================
namespace update_min {
using S = ll;
using F = ll;
const F FID =
    LLONG_MAX;  // 「代入しない」を表す番兵。値域と衝突しない定数を選ぶ

S op(S a, S b) { return min(a, b); }
S e() { return LINF; }
S mapping(F f, S x) { return f == FID ? x : f; }
F composition(F f, F g) { return f == FID ? g : f; }  // 後から来た f が勝つ
F id() { return FID; }
using Lazy = lazy_segtree<S, op, e, F, mapping, composition, id>;
}  // namespace update_min

void demo_update_min() {
    update_min::Lazy seg(vector<update_min::S>{5, 3, 8, 1, 9});

    cout << seg.prod(0, 5) << "\n";  // → 1
    seg.apply(2, 5, 7);              // [2,5) を 7 に代入 → {5,3,7,7,7}
    cout << seg.prod(0, 5) << "\n";  // → 3
    cout << seg.prod(2, 5) << "\n";  // → 7

    // lazy_segtree にも max_right / min_left がある（遅延を伝播しながら降りる）
    int r = seg.max_right(0, [](update_min::S x) { return x >= 3; });
    cout << r << "\n";  // min が 3 以上でいられる最大の r → 5
}

// =====================================================================
// パターン3: 区間加算 × 区間和
//   和は区間長に依存するので S に len が要る。最頻出の罠。
// =====================================================================
namespace add_sum {
struct S {
    ll sum;
    int len;
};
using F = ll;

S op(S a, S b) { return {a.sum + b.sum, a.len + b.len}; }
S e() { return {0, 0}; }  // len=0 なので op の単位元として正しく振る舞う
S mapping(F f, S x) { return {x.sum + f * x.len, x.len}; }
F composition(F f, F g) {
    return f + g;
}  // 加算は可換なので順序を気にしなくてよい
F id() { return 0; }
using Lazy = lazy_segtree<S, op, e, F, mapping, composition, id>;

Lazy build(
    const vector<ll>& a) {  // len=1 を詰めるのを毎回書くと事故るので関数化
    vector<S> init(a.size());
    for (size_t i = 0; i < a.size(); i++) init[i] = {a[i], 1};
    return Lazy(init);
}
}  // namespace add_sum

void demo_add_sum() {
    add_sum::Lazy seg = add_sum::build({1, 2, 3, 4, 5});

    cout << seg.prod(0, 5).sum << "\n";  // → 15

    seg.apply(1, 4, 10);                 // [1,4) に +10
    cout << seg.prod(0, 5).sum << "\n";  // 15 + 10*3 → 45
    cout << seg.prod(1, 2).sum << "\n";  // 2+10 → 12

    seg.apply(0, 3);                     // → a[0] += 3
    cout << seg.get(0).sum << "\n";      // → 4
    cout << seg.all_prod().sum << "\n";  // → 48

    seg.set(0, {0, 1});                  // set は S 型で渡す。len を忘れない
    cout << seg.all_prod().sum << "\n";  // → 44
}

// =====================================================================
// パターン4: 区間 Affine（x -> a*x + b）× 区間和
//   非可換な作用素。composition の順序を逆にすると WA になる代表例。
// =====================================================================
namespace affine_sum {
constexpr ll MOD = 998244353;
struct S {
    ll sum;
    int len;
};
struct F {
    ll a, b;
};

S op(S x, S y) { return {(x.sum + y.sum) % MOD, x.len + y.len}; }
S e() { return {0, 0}; }
S mapping(F f, S x) { return {(f.a * x.sum + f.b * x.len) % MOD, x.len}; }
// f(g(x)) = f.a*(g.a*x + g.b) + f.b = (f.a*g.a)x + (f.a*g.b + f.b)
F composition(F f, F g) { return {f.a * g.a % MOD, (f.a * g.b + f.b) % MOD}; }
F id() { return {1, 0}; }
using Lazy = lazy_segtree<S, op, e, F, mapping, composition, id>;

Lazy build(const vector<ll>& a) {
    vector<S> init(a.size());
    for (size_t i = 0; i < a.size(); i++) init[i] = {a[i] % MOD, 1};
    return Lazy(init);
}
}  // namespace affine_sum

void demo_affine_sum() {
    affine_sum::Lazy seg = affine_sum::build({1, 2, 3, 4, 5});

    cout << seg.prod(0, 5).sum << "\n";  // → 15
    seg.apply(0, 3, {2, 1});             // [0,3) に x -> 2x+1 → {3,5,7,4,5}
    cout << seg.prod(0, 5).sum << "\n";  // → 24
    seg.apply(1, 4, {3, 0});             // [1,4) に x -> 3x   → {3,15,21,12,5}
    cout << seg.prod(0, 5).sum << "\n";  // → 56
    cout << seg.prod(1, 3).sum << "\n";  // → 36
}

// =====================================================================
//  作用素設計チートシート
// ---------------------------------------------------------------------
//    加算×min  : S=ll,        F=ll,        mapping=x+f          （len 不要）
//                composition=f+g,           id=0
//    代入×min  : S=ll,        F=ll(番兵),  mapping= f==ID ? x : f
//                composition= f==ID ? g : f, id=ID
//    加算×和   : S={sum,len}, F=ll,        mapping={x.sum+f*x.len, x.len}
//                composition=f+g,           id=0
//    代入×和   : S={sum,len}, F=ll(番兵),  mapping= f==ID ? x : {f*x.len,
//    x.len}
//                composition= f==ID ? g : f, id=ID
//    Affine×和 : パターン4
//    chmin×max : Segment Tree Beats が必要。ACL の lazy_segtree では扱えない
//
//  ■ ハマりどころ
//    - composition(f, g) は「g が先、f が後」。逆に書くと可換な加算では通って
//      Affine
//      や代入で落ちる。デバッグが遅れるので最初から向きを固定して覚える。
//    - mapping が区間長を要求するなら S に len を持たせる。min/max なら不要。
//    - e() は作用を受けても壊れない値にする。加算×min で e()=LLONG_MAX にすると
//      INF+f がオーバーフローするので 1e18 程度に抑えるか番兵チェックを入れる。
//    - id() は「作用しない」写像。番兵で表すときは値域と衝突しない定数を選ぶ。
//    - apply は (p, f) と (l, r, f) の 2 種類。prod / set / get / all_prod /
//    max_right
//      は segtree と同じインターフェース。all_prod だけ O(1)。
//    - MOD を取る問題では mapping / composition
//    の各積で必ず剰余を取る（オーバーフロー）。
// =====================================================================

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    cout << "--- 1: range add / range min ---\n";
    demo_add_min();
    cout << "--- 2: range update / range min ---\n";
    demo_update_min();
    cout << "--- 3: range add / range sum ---\n";
    demo_add_sum();
    cout << "--- 4: range affine / range sum ---\n";
    demo_affine_sum();
    return 0;
}