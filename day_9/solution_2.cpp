#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define rep(a, b) for (ll a = 0; a < (b); ++a)
#define reps(a, b, c) for (ll a = b; a < (c); ++a)
#define frep(a) while ((a)--)
#define repAll(i, v) for (auto &i : v)
#define endl '\n'
#define sz(a) ((ll)((a).size()))
#define ln(a) ((ll)((a).length()))

const ll NINF = numeric_limits<ll>::min();
const ll INF = numeric_limits<ll>::max();
const ll MOD = 1000000007;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    ifstream fp_in("input.txt", ios::in);
    string history;
    ll res = 0;
    while (getline(fp_in, history)) {
        istringstream iss(history);
        vector<vector<ll>> levels = {{}};
        ll x;
        while (iss >> x)
            levels[0].push_back(x);

        ll levelCount = 0;
        while (true) {
            vector<ll> newLevel;
            bool allZero = true;
            rep(i, sz(levels[levelCount]) - 1) {
                ll diff = levels[levelCount][i + 1] - levels[levelCount][i];
                newLevel.push_back(diff);
                if (diff != 0)
                    allZero = false;
            }
            levelCount++;
            levels.push_back(newLevel);
            if (allZero)
                break;
        }

        // extend all levels by one value
        levels[levelCount].insert(levels[levelCount].begin(), 0);
        for (ll i = levelCount - 1; i > -1; i--) {
            ll imputedValue = levels[i][0] - levels[i + 1][0];
            levels[i].insert(levels[i].begin(), imputedValue);
        }

        res += levels[0][0];
    }

    ofstream fp_out("output_2.txt", ios::out);
    fp_out << res << endl;
    fp_out.close();

    return 0;
}