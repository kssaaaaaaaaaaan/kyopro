// https://github.com/kssaaaaaaaaaaan/kyopro
// https://github.com/ei1333/library/tree/dca071d33d8dbfd001e450a109c55eb6c38c2ee8
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <class T> using pq_g = priority_queue<T, vector<T>, greater<T>>;

void solve() {
    int m, n;
    cin >> m >> n;
    string s;
    cin >> s;
    pq_g<tuple<ll, int, int>> que;
    for (int i = 0; i < n; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        que.push({a + b, a, c});
    }

    vector<ll> dp(m + 1);
    for (int i = 0; i < m; i++) {
        while (true) {
            auto [len, r, c] = que.top();
            if (len != i) {
                break;
            }

            que.pop();
            dp[r] = dp[r] + c;
        }

        if (s[i] == 'R') {
        } else if (s[i] == 'U') {
        } else {
        }
    }
}

int main() {
    int t = 1;
    while (t--) {
        solve();
    }
    return 0;
}