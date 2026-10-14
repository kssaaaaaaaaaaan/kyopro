// https://github.com/kssaaaaaaaaaaan/kyopro
// https://github.com/ei1333/library/tree/dca071d33d8dbfd001e450a109c55eb6c38c2ee8
#include <bits/stdc++.h>
using namespace std;

int main() {
    // 再帰関数の定義
    function<int(int)> sum = [&](int n) {
        if (n == 0) {
            return 0;
        }
        int s = sum(n - 1);
        return s + n;
    };

    cout << sum(3) << endl;
}