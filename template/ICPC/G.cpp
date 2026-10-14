// https://github.com/kssaaaaaaaaaaan/kyopro
// https://github.com/ei1333/library/tree/dca071d33d8dbfd001e450a109c55eb6c38c2ee8
#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for (int i = 0; i < (int)(n); i++)
int main() {
    int N;
    cin >> N;
    deque<char> ans;

    cout << "? a" << endl;
    int a;
    int b;
    cin >> a;
    b = N - a;
    if (N % 2 != 0) {
        if (a % 2 == 0) {
            ans.push_back('b');
            b--;
        } else {
            ans.push_back('a');
            a--;
        }
    }
    while (a != 0 && b != 0) {
        ans.push_front('a');
        ans.push_back('a');
        string S;
        while (!ans.empty()) {
            S.push_back(ans.front());
            ans.pop_front();
        }
        REP(i, S.size()) ans.push_front(S[i]);
        int check;
        cout << "? " << S << endl;
        cin >> check;
        if (check % 2 != 0) {
            a -= 2;
            continue;
        } else {
            b -= 2;
            ans.pop_back();
            ans.pop_front();
            ans.push_front('b');
            ans.push_back('b');
        }
    }
    while (a != 0) {
        ans.push_front('a');
        ans.push_back('a');
        a -= 2;
    }
    while (b != 0) {
        ans.push_front('b');
        ans.push_back('b');
        b -= 2;
    }
    string S;
    while (!ans.empty()) {
        S.push_back(ans.front());
        ans.pop_front();
    }
    cout << "! " << S << endl;
}