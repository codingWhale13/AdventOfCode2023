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

    // moving right, down, left, up
    vector<vector<ll>> DIRS = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    ifstream fp_in("input.txt", ios::in);
    string s;
    vector<vector<char>> grid;
    while (getline(fp_in, s)) {
        vector<char> v;
        repAll(c, s) v.push_back(c == 'S' ? 'O' : c);
        grid.push_back(v);
    }

    ll H = sz(grid), W = sz(grid[0]);
    rep(bfsStep, 64) {
        vector<vector<char>> newGrid(H, vector<char>(W));

        rep(y, H) {
            rep(x, W) {
                if (grid[y][x] == 'O') {
                    rep(d, 4) {
                        ll nx = x + DIRS[d][0];
                        ll ny = y + DIRS[d][1];
                        if (nx == -1 || ny == -1 || nx == W || ny == H || grid[ny][nx] == '#')
                            continue;
                        newGrid[ny][nx] = 'O';
                    }
                } else if (grid[y][x] == '#') {
                    newGrid[y][x] = '#';
                }
            }
        }

        grid = newGrid;
    }

    ll res = 0;
    rep(y, H)
        rep(x, W)
            res += grid[y][x] == 'O';

    ofstream fp_out("output_1.txt", ios::out);
    fp_out << res << endl;
    fp_out.close();

    return 0;
}