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

ll getHash(string &s) {
    ll res = 0;
    repAll(c, s) {
        res += c;
        res *= 17;
        res %= 256;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    ifstream fp_in("input.txt", ios::in);
    string s;
    vector<vector<pair<string, ll>>> lenses(256); // there are 256 boxes
    while (getline(fp_in, s, ',')) {
        if (s[ln(s) - 1] == '-') {
            string sub = s.substr(0, ln(s) - 1);
            ll hash = getHash(sub);
            rep(i, sz(lenses[hash])) {
                if (lenses[hash][i].first == sub)
                    lenses[hash].erase(lenses[hash].begin() + i);
            }
        } else {
            string sub = s.substr(0, ln(s) - 2);
            ll hash = getHash(sub);
            ll val = s[ln(s) - 1] - '0';
            ll isNewElement = true;
            rep(i, sz(lenses[hash])) {
                if (lenses[hash][i].first == sub) {
                    lenses[hash][i].second = val;
                    isNewElement = false;
                    break;
                }
            }
            if (isNewElement)
                lenses[hash].push_back({sub, val});
        }
    }
    fp_in.close();
    ll res = 0;
    rep(boxId, 256) {
        rep(i, sz(lenses[boxId]))
            res += (boxId + 1) * (i + 1) * lenses[boxId][i].second;
    }

    ofstream fp_out("output_2.txt", ios::out);
    fp_out << res << endl;
    fp_out.close();

    return 0;
}