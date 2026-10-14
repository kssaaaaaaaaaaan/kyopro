// https://github.com/kssaaaaaaaaaaan/kyopro
// https://github.com/ei1333/library/tree/dca071d33d8dbfd001e450a109c55eb6c38c2ee8
// __builtin_* テンプレート
// GCC/Clang 共通のコンパイラ組み込み関数。include 不要
#include <bits/stdc++.h>
using namespace std;

int main() {
    // --- ビットカウント系 ---
    // __builtin_popcount(x)  : 1-bit の個数 (unsigned int)
    // __builtin_popcountl(x) : unsigned long 版
    // __builtin_popcountll(x): unsigned long long 版
    cout << __builtin_popcount(0b1011)       << "\n"; // 3
    cout << __builtin_popcountll(~0ULL)      << "\n"; // 64

    // __builtin_clz(x)  : 上位の連続 0 の個数 (x > 0 必須, unsigned int 想定)
    // __builtin_clzl(x) / __builtin_clzll(x): l / ll 版
    cout << __builtin_clz(1)                 << "\n"; // 31
    cout << __builtin_clzll(1ULL)            << "\n"; // 63

    // __builtin_ctz(x)  : 下位の連続 0 の個数 (x > 0 必須)
    // __builtin_ctzl(x) / __builtin_ctzll(x)
    cout << __builtin_ctz(8)                 << "\n"; // 3
    cout << __builtin_ctzll(1ULL << 40)      << "\n"; // 40

    // __builtin_parity(x): 1-bit が奇数個なら 1, 偶数個なら 0
    cout << __builtin_parity(0b1011)         << "\n"; // 1

    // --- よく使う派生計算 ---
    unsigned int x = 12;

    // floor(log2(x))  ← x > 0 必須
    int fl = 31 - __builtin_clz(x);    // 3
    // long long 版: 63 - __builtin_clzll(x)

    // ceil(log2(x))   ← x > 1 の場合
    int cl = x <= 1 ? 0 : 32 - __builtin_clz(x - 1); // 4

    // x 以上の最小の 2 の冪 (bit_ceil 相当)
    unsigned int bc = x <= 1 ? 1u : 1u << (32 - __builtin_clz(x - 1)); // 16

    cout << fl << " " << cl << " " << bc << "\n"; // 3 4 16

    // --- その他 ---
    // __builtin_expect(expr, expected): 分岐予測ヒント
    //   likely(x)   → __builtin_expect(!!(x), 1)
    //   unlikely(x) → __builtin_expect(!!(x), 0)
    int v = 42;
    if (__builtin_expect(v > 0, 1)) cout << "positive\n";

    // __builtin_bswap32(x) / __builtin_bswap64(x): バイトスワップ
    cout << hex << __builtin_bswap32(0x12345678) << "\n"; // 78563412

    return 0;
}
