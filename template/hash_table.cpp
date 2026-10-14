// https://github.com/kssaaaaaaaaaaan/kyopro
// https://github.com/ei1333/library
// pb_ds hash table テンプレート
// cc_hash_table: チェイン法。unordered_map より高速なことが多い
// gp_hash_table: オープンアドレス法。find が最速だが erase 不可
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

int main() {
    // --- cc_hash_table ---
    cc_hash_table<int, int> cc;
    cc.insert({1, 10});
    cc[2] = 20;
    if (cc.find(1) != cc.end()) cout << cc[1] << "\n"; // 10
    cc.erase(1);

    // カスタムハッシュを渡す場合
    struct MyHash {
        size_t operator()(long long v) const {
            v = (v ^ (v >> 30)) * 0xbf58476d1ce4e5b9LL;
            return v ^ (v >> 27);
        }
    };
    cc_hash_table<long long, int, MyHash> cc2;
    cc2[1LL << 40] = 42;

    // --- gp_hash_table ---
    // find が cc_hash_table より速い。erase は使えない
    gp_hash_table<int, int> gp;
    gp.insert({3, 30});
    gp[4] = 40;
    if (gp.find(3) != gp.end()) cout << gp.find(3)->second << "\n"; // 30

    return 0;
}
