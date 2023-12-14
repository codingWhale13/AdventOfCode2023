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
    ll res = 0;
    string s;
    vector<vector<char>> grid;
    while (getline(fp_in, s)) {
        vector<char> row;
        repAll(c, s) row.push_back(c);
        grid.push_back(row);
    }
    fp_in.close();

    rep(x, sz(grid[0])) {
        // tilt
        rep(y, sz(grid)) {
            if (grid[y][x] == 'O') {
                ll newY = y;
                while (newY > 0 && grid[newY - 1][x] == '.')
                    newY--;
                grid[y][x] = '.';
                grid[newY][x] = 'O';
            }
        }

        // count
        rep(y, sz(grid)) {
            if (grid[y][x] == 'O')
                res += sz(grid) - y;
        }
    }

    ofstream fp_out("output_1.txt", ios::out);
    fp_out << res << endl;
    fp_out.close();

    return 0;
}