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
    string line;
    vector<string> grid;
    while (getline(fp_in, line))
        grid.push_back(line);
    fp_in.close();
    ll h = sz(grid), w = ln(grid[0]);

    vector<ll> emptyRowsPrefixSum(h), emptyColsPrefixSum(w);
    ll emptyRowCount = 0, emptyColCount = 0;
    rep(i, h) {
        bool isEmptyRow = true;
        rep(j, w) if (grid[i][j] == '#') isEmptyRow = false;
        emptyRowCount += isEmptyRow;
        emptyRowsPrefixSum[i] = emptyRowCount;
    }
    rep(i, w) {
        bool isEmptyCol = true;
        rep(j, h) if (grid[j][i] == '#') isEmptyCol = false;
        emptyColCount += isEmptyCol;
        emptyColsPrefixSum[i] = emptyColCount;
    }

    vector<pair<ll, ll>> galaxies;
    rep(i, h) {
        rep(j, w) {
            if (grid[i][j] == '#')
                galaxies.push_back({j + emptyColsPrefixSum[j], i + emptyRowsPrefixSum[i]});
        }
    }

    ll res = 0;
    ll g = sz(galaxies);
    rep(i, g)
        reps(j, i + 1, g)
            res += abs(galaxies[i].first - galaxies[j].first) + abs(galaxies[i].second - galaxies[j].second);

    ofstream fp_out("output_1.txt", ios::out);
    fp_out << res << endl;
    fp_out.close();

    return 0;
}