// https://github.com/kssaaaaaaaaaaan/kyopro
// https://github.com/ei1333/library
#include <iostream>

using namespace std;
// PBDSを使うためのヘッダーと名前空間
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

// std::set の代わりになる型定義
// 典型:重複を許したいときはpair{val,id}を使おう！
typedef tree<int, null_type, less<int>, rb_tree_tag,
             tree_order_statistics_node_update>
    ordered_set;

int main() {
    ordered_set s;
    s.insert(10);
    s.insert(30);
    s.insert(20);
    s.insert(50);  // 中身は自動で [10, 20, 30, 50] になる

    // 「30」未満の要素の個数を求める -> 10, 20 の 2個
    cout << s.order_of_key(30) << endl;  // 出力: 2

    // 「40」未満の要素の個数を求める -> 10, 20, 30 の 3個
    cout << s.order_of_key(40) << endl;  // 出力: 3

    // 小さい方から2番目（0オリジンなので 30）の要素を取得
    cout << *s.find_by_order(2) << endl;  // 出力: 30

    return 0;
}