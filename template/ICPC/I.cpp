// https://github.com/kssaaaaaaaaaaan/kyopro
// https://github.com/ei1333/library/tree/dca071d33d8dbfd001e450a109c55eb6c38c2ee8
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define REP(i, n) for (int i = 0; i < (int)(n); i++)
#define FOR(i, a, b) for (ll i = (a); i < (ll)(b); i++)
using VI = vector<int>;
int main() {
    int N;
    cin >> N;
    VI P(N);
    vector<pair<int, int>> Points(N);
    REP(i, N) {
        cin >> P[i];
        P[i]--;
        Points[i] = {P[i], i};
    }
    vector<pair<int, int>> ans;
    sort(Points.begin(), Points.end());
    int left = Points[0].second, right = Points[N - 1].second;
    VI upper(N, -1), lower(N, -1);
    FOR(i, 1, N - 1) {
        if (Points[i].second > right)
            upper[i] = Points[i].second;
        else
            lower[i] = Points[i].second;
    }
    if (left < right) {
        lower[0] = Points[0].second;
        // lowerから埋めていく
        int prev = N - 1;
        for (int i = N - 1; i >= 0; i--) {
            if (lower[i] == -1) continue;

            ans.push_back({prev, lower[i]});
            ans.push_back({i, lower[i]});
            prev = i;
        }
        upper[N - 1] = Points[N - 1].second;
        FOR(i, 1, N) {
            if (upper[i] == -1) continue;
            ans.push_back({prev, upper[i]});
            ans.push_back({i, upper[i]});
            prev = i;
        }

    } else {
        lower[N - 1] = Points[N - 1].second;
        // lowerから埋めていく
        int prev = 0;
        FOR(i, 1, N) {
            if (lower[i] == -1) continue;

            ans.push_back({prev, lower[i]});
            ans.push_back({i, lower[i]});
            prev = i;
        }
        upper[0] = Points[0].second;
        for (int i = N - 1; i >= 0; i--) {
            if (upper[i] == -1) continue;
            ans.push_back({prev, upper[i]});
            ans.push_back({i, upper[i]});
            prev = i;
        }
    }

    REP(i, 2 * N) cout << ans[i].second + 1 << " " << ans[i].first + 1 << endl;
}