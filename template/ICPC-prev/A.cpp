// https://github.com/kssaaaaaaaaaaan/kyopro
// https://github.com/ei1333/library/tree/dca071d33d8dbfd001e450a109c55eb6c38c2ee8
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
using ll = long long;
using VI = vector<int>;
using VLL = vector<ll>;
#define REP(i, n) for (int i = 0; i < (int)(n); i++)
#define FOR(i, a, b) for (ll i = a; i < (ll)(b); i++)
#define ALL(a) (a).begin(), (a).end()
int main() {
    int N, L;
    cin >> N >> L;
    vector<int> A(N);
    REP(i, N) cin >> A[i];
    if (N == 1) {
        cout << 0 << endl;
        return 0;
    }
    sort(ALL(A));
    vector<int> A2(2 * N);
    REP(i, N) {
        A2[i] = A[i];
        A2[N + i] = A[i] + L;
    }
    int ans = 1e9;
    REP(i, N) {
        int start = A2[i];
        int check = 0;
        int tmp = lower_bound(ALL(A2), start + L / 2) - A2.begin();
        check = A2[tmp - 1] - start;
        tmp = lower_bound(ALL(A2), start + L) - A2.begin();
        check = max(check, A2[tmp - 1] - start - L / 2);
        ans = min(ans, check);
    }
    cout << ans << endl;
    return 0;
}