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
    string s, t, u, numStr, dstStr, srcStr, rngStr;

    getline(fp_in, s);
    istringstream iss(s);
    iss >> s; // "seeds:"
    vector<ll> seeds;
    while (iss >> numStr)
        seeds.push_back(stoll(numStr));
    getline(fp_in, s); // ignore empty line

    vector<vector<vector<ll>>> maps;
    while (getline(fp_in, s)) { // [a-to-b]
        vector<vector<ll>> whateverMap;
        getline(fp_in, s);
        while (ln(s) != 0) {
            istringstream iss(s);
            iss >> dstStr >> srcStr >> rngStr;
            whateverMap.push_back({stoll(dstStr), stoll(srcStr), stoll(rngStr)});
            getline(fp_in, s);
        }
        maps.push_back(whateverMap);
    }

    ll res = INF;
    repAll(seed, seeds) {
        ll cur = seed; // current seed value
        repAll(whateverMap, maps) {
            rep(i, sz(whateverMap)) {
                ll dst = whateverMap[i][0];
                ll src = whateverMap[i][1];
                ll rng = whateverMap[i][2];
                if (cur >= src && cur <= src + rng) {
                    cur += dst - src;
                    break;  // mapping is unique and we found it
                }
            }
        }
        res = min(res, cur);
    }

    fp_in.close();
    ofstream fp_out("output_1.txt", ios::out);
    fp_out << res << endl;
    fp_out.close();

    return 0;
}