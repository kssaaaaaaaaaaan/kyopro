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
    sort(Points.begin(), Points.end());
    vector<pair<int, int>> ans;
    // コーナーケース
    if (Points[0].first == 0 && Points[0].second == 0) {
        REP(i, N) swap(Points[i].first, Points[i].second);
        sort(Points.begin(), Points.end());
        FOR(i, 1, N) {
            ans.push_back({i - 1, Points[i].second});
            ans.push_back({Points[i].first, Points[i].second});
        }
        ans.push_back({N - 1, 0});
        ans.push_back({0, 0});
        REP(i, 2 * N)
        cout << ans[i].first + 1 << " " << ans[i].second + 1 << endl;
        return 0;
    }
    if (Points[N - 1].first == N - 1 && Points[N - 1].second == N - 1) {
        REP(i, N) swap(Points[i].first, Points[i].second);
        sort(Points.begin(), Points.end());
        for (int i = N - 2; i >= 0; i--) {
            ans.push_back({i + 1, Points[i].second});
            ans.push_back({Points[i].first, Points[i].second});
        }
        ans.push_back({0, N - 1});
        ans.push_back({N - 1, N - 1});
        REP(i, 2 * N)
        cout << ans[i].first + 1 << " " << ans[i].second + 1 << endl;
        return 0;
    }

    int left = Points[0].second, right = Points[N - 1].second;
    VI upper(N, -1), lower(N, -1);
    FOR(i, 1, N - 1) {
        if (Points[i].second > right)
            upper[i] = Points[i].second;
        else
            lower[i] = Points[i].second;
    }
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

    REP(i, 2 * N) cout << ans[i].second + 1 << " " << ans[i].first + 1 << endl;
}