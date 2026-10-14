// https://github.com/kssaaaaaaaaaaan/kyopro
// https://github.com/ei1333/library
// rope テンプレート
// split/insert/erase が O(log n)。巨大文字列の中間操作に使う
// crope は rope<char> の typedef
#include <bits/stdc++.h>
#include <ext/rope>
using namespace std;
using namespace __gnu_cxx;

int main() {
    rope<char> r("hello");
    r.push_back('!');               // "hello!"
    r += " world";                  // "hello! world"

    // insert(pos, str): pos の直前に挿入 O(log n + len)  n=rope長, len=挿入文字列長
    r.insert(0, "oh ");             // "oh hello! world"
    cout << r << "\n";

    // substr(pos, len): O(log n + len) で部分文字列を取得
    rope<char> sub = r.substr(3, 5);
    cout << sub << "\n";            // "hello"

    // erase(pos, len): O(log n)
    r.erase(0, 3);                  // "hello! world"
    cout << r << "\n";

    // 連結
    rope<char> a("foo"), b("bar");
    rope<char> c = a + b;           // "foobar"
    cout << c << "\n";

    // 添字アクセス・サイズ
    cout << r[0] << " " << r.size() << "\n"; // h 12

    // crope は rope<char> の別名
    crope cr("crope alias");
    cout << cr << "\n";

    return 0;
}
