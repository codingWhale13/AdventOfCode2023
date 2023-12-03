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

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool onGrid(ll x, ll y, ll w, ll h) {
    return x >= 0 && x < w && y >= 0 && y < h;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    ifstream fp_in("input.txt", ios::in);

    vector<string> grid;
    string s;
    ll res = 0;
    while (fp_in >> s) {
        grid.push_back(s);
    }

    ll h = sz(grid);
    ll w = sz(grid[0]);

    rep(y, h) {
        ll x = 0;
        while (x < w) {
            if (isDigit(grid[y][x])) {
                ll x2 = x + 1;
                while (x2 < w && isDigit(grid[y][x2])) {
                    x2++;
                }

                bool isPartNumber = false;
                reps(i, y - 1, y + 2) {
                    reps(j, x - 1, x2 + 1) {
                        if (onGrid(j, i, w, h) && grid[i][j] != '.' && !isDigit(grid[i][j])) {
                            isPartNumber = true;
                        }
                    }
                }
                if (isPartNumber) {
                    res += stoll(grid[y].substr(x, x2 - x + 1));
                }
                x = x2;
            } else {
                x++;
            }
        }
    }

    fp_in.close();
    ofstream fp_out("output_1.txt", ios::out);
    fp_out << res << endl;
    fp_out.close();

    return 0;
}