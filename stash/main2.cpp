// https://github.com/kssaaaaaaaaaaan/kyopro
// https://github.com/ei1333/library/tree/dca071d33d8dbfd001e450a109c55eb6c38c2ee8
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    int n;
    cin >> n;
    vector<int> x(n);
    vector<int> y(n);

    vector<int> x_odd;
    vector<int> x_even;
    for (int i = 0; i < n; i++) {
        cin >> x[i];
        if (x[i] % 2 == 0)
            x_even.push_back((x[i]));
        else
            x_odd.push_back(x[i]);
    }

    vector<int> y_odd;
    vector<int> y_even;
    for (int i = 0; i < n; i++) {
        cin >> y[i];
        if (y[i] % 2 == 0)
            y_even.push_back(y[i]);
        else
            y_odd.push_back(y[i]);
    }

    if (x_even.size() != y_even.size() || x_odd.size() != y_odd.size()) {
        cout << -1 << endl;
        return;
    }

    sort(x_even.begin(), x_even.end());
    sort(x_odd.begin(), x_odd.end());
    sort(y_even.begin(), y_even.end());
    sort(y_odd.begin(), y_odd.end());

    int mx = 0;
    for (int i = 0; i < x_even.size(); i++) {
        mx = max(mx, abs(x_even[i] - y_even[i]));
    }

    for (int i = 0; i < x_odd.size(); i++) {
        mx = max(mx, abs(x_odd[i] - y_odd[i]));
    }

    vector<pair<int, int>> p;
    for (int i = 0; i < x_even.size(); i++) {
        int len = abs(x_even[i] - y_even[i]);
        int r = (mx - len) / 2;
        if (x_even[i] - y_even[i] <= 0) {
            p.push_back({len + r, r});
        } else {
            p.push_back({r, len + r});
        }
    }

    for (int i = 0; i < x_odd.size(); i++) {
        int len = abs(x_odd[i] - y_odd[i]);
        int r = (mx - len) / 2;
        if (x_odd[i] - y_odd[i] <= 0) {
            p.push_back({len + r, r});
        } else {
            p.push_back({r, len + r});
        }
    }

    sort(p.begin(), p.end());

    ll s = 0;
    ll lef = 0;
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        auto [l, r] = p[i];
        l -= lef;
        ans += s * (n - s) * l;
        s++;
        lef += l;
    }

    cout << ans << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}