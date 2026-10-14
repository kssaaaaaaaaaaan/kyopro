// https://github.com/kssaaaaaaaaaaan/kyopro
// https://github.com/ei1333/library/tree/dca071d33d8dbfd001e450a109c55eb6c38c2ee8
#include <bits/stdc++.h>
#include <atcoder/all>
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
using namespace std;
using namespace atcoder;
typedef pair<ll, ll> pll;
ll p = 998244353;
ll INF = 2000000000000000010;

template <class T> bool chmax(T& a, const T& b) {
    if (a < b) {
        a = b;
        return 1;
    }
    return 0;
}
template <class T> bool chmin(T& a, const T& b) {
    if (b < a) {
        a = b;
        return 1;
    }
    return 0;
}

void yn(bool a) {
    if (a) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}

ll mex(const vector<ll>& a) {
    ll n = (ll)a.size();
    vector<int> b(n + 1, 0);
    for (ll i = 0; i < n; i++) {
        if (a[i] < n && a[i] >= 0) {
            b[a[i]]++;
        }
    }
    for (ll i = 0; i < n + 1; i++) {
        if (b[i] == 0) {
            return i;
        }
    }
    return 0;
}

void init() { std::cout << std::fixed << std::setprecision(10); }

vector<vector<ll>> vec_seki(const vector<vector<ll>>& a,
                            const vector<vector<ll>>& b,
                            ll p) {
    if (a.size() == 0) {
        return {};
    }
    assert(a[0].size() == b.size());
    assert(p != 0);
    vector<vector<ll>> ans(a.size(), vector<ll>(b[0].size(), 0));
    for (ll i = 0; i < (ll)a.size(); i++) {
        for (ll k = 0; k < (ll)a[0].size(); k++) {
            for (ll j = 0; j < (ll)b[0].size(); j++) {
                ans[i][j] = (ans[i][j] + a[i][k] * b[k][j]) % p;
            }
        }
    }
    return ans;
}

template <class T> vector<pair<T, ll>> runlength(const vector<T>& vec) {
    vector<pair<T, ll>> ret;
    if (vec.size() == 0) {
        return ret;
    }
    pair<T, ll> temp;
    temp.first = vec[0];
    temp.second = 1;
    ret.push_back(temp);
    T mae = vec[0];
    for (ll i = 1; i < (ll)vec.size(); i++) {
        if (vec[i] != mae) {
            temp.first = vec[i];
            temp.second = 1;
            ret.push_back(temp);
            mae = vec[i];
        } else {
            ret[ret.size() - 1].second++;
        }
    }
    return ret;
}

ll bintoll(const string& S) {
    ll ret = 0;
    ll n = (ll)S.size();
    for (ll i = 0; i < n; i++) {
        if (S[i] == '1') {
            ret += 1LL << (n - 1 - i);
        }
    }
    return ret;
}

string lltobin(const ll N) {
    if (N == 0) return "0";
    string S;
    ll Nco = N;
    while (Nco != 0) {
        S += char('0' + (Nco & 1));
        Nco >>= 1;
    }
    reverse(S.begin(), S.end());
    return S;
}

int main() {
    init();

    ll P;
    cin >> P;
    ll in1 = -1;
    ll in2 = -1;
    ll re;
    ll a, d;
    bool check = false;
    for (ll i = 0; i < P; i++) {
        cout << "? " << 0 + (in1 != -1) << endl;
        cin >> re;
        if (in1 == -1 && re == 1) {
            in1 = i;
            break;
        }
    }
    if (in1 == -1) {
        for (ll i = 0; i < P; i++) {
            cout << "? " << i << endl;
            cin >> re;
            if (re == 1) {
                a = i;
            }
        }
        ll d = 0;
        cout << "! " << a << " " << d << endl;
        return 0;
    }
    for (ll i = in1 + 1; i < 2 * P; i++) {
        cout << "? " << 1 << endl;
        cin >> re;
        if (re == 1) {
            in2 = i;
            break;
        }
    }
    d = inv_mod(in2 - in1, P);
    a = 1000 * P - d * in2 + 1;
    a = a % P;
    cout << "! " << a << " " << d << endl;

    // ここにプログラムを追記
}