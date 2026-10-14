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

vector<vector<char>> sur(ll N, vector<vector<char>> A) {
    vector<vector<char>> ans(N, vector<char>(N));
    for (ll i = 0; i < N; i++) {
        for (ll j = 0; j < N; j++) {
            ans[j][N - 1 - i] = A[i][j];
        }
    }
    return ans;
}

int main() {
    init();

    ll N, M;
    cin >> N >> M;
    vector<vector<string>> S(N, vector<string>(M));
    vector<vector<vector<char>>> smo(
        N, vector<vector<char>>(M, (vector<char>(M))));
    for (ll i = 0; i < N; i++) {
        for (ll j = 0; j < M; j++) {
            cin >> S[i][j];
            for (ll k = 0; k < M; k++) {
                smo[i][j][k] = S[i][j][k];
            }
        }
    }
    vector<vector<char>> temp;
    vector<ll> muki(N, 0);
    vector<ll> retu(N, 0);
    vector<ll> tyo(N, 0);
    for (ll i = 0; i < N; i++) {
        temp = smo[i];
        for (ll j = 0; j < 4; j++) {
            for (ll l = 0; l < M; l++) {
                for (ll k = 0; k < M; k++) {
                    if (temp[k][l] == '.') {
                        if (tyo[i] <= k + 1) {
                            tyo[i] = k + 1;
                            muki[i] = j;
                            retu[i] = l;
                        }
                    } else {
                        break;
                    }
                }
            }
            temp = sur(M, temp);
        }
    }
    vector<ll> sta(N, 0);
    ll dai = 0;
    for (ll i = 0; i < N; i++) {
        for (ll j = i; j < N; j++) {
            sta[i] += tyo[j];
            dai = max(dai, sta[i]);
            if (i != j && tyo[j] != M) {
                break;
            }
        }
        // cout << sta[i] << " ";
    }
    ll staza = -1;
    // cout << endl;
    for (ll i = 0; i < N; i++) {
        if (dai == sta[i]) {
            staza = i;
        }
    }
    cout << dai << endl;
    vector<vector<vector<char>>> ans(
        N, vector<vector<char>>(M, (vector<char>(M * 2 - 1, '#'))));
    for (ll i = 0; i < N; i++) {
        if (i == staza) {
            muki[i] = (muki[i] + 2) % 4;
        }
        cout << muki[i] << " ";
    }
    cout << endl;
    for (ll i = 0; i < N; i++) {
        if (i == staza) {
            retu[i] = M - 1 - retu[i];
            // 個々のような気がする
        }
        retu[i] = M - 1 - retu[i];
        cout << retu[i] << " ";
    }
    cout << endl;
    for (ll i = 0; i < N; i++) {
        for (ll j = 0; j < muki[i]; j++) {
            smo[i] = sur(M, smo[i]);
        }
        for (ll j = 0; j < M; j++) {
            for (ll k = 0; k < M; k++) {
                ans[i][j][k + retu[i]] = smo[i][j][k];
            }
        }
    }
    for (ll i = 0; i < N; i++) {
        for (ll j = 0; j < M; j++) {
            for (ll k = 0; k < M * 2 - 1; k++) {
                cout << ans[i][j][k];
            }
            cout << endl;
        }
        // cout << endl;
    }

    // ここにプログラムを追記
}
