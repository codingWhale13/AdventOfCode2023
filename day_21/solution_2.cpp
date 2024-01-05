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

/* EXPLANATION, inspired by: https://www.youtube.com/watch?v=99Mjs1i0JxU
- The amount of reachable tiles f(s) after s steps is quadratic, so we can do the following:
1) Find 3 points on the quadratic by going x1, x2, x3 steps toward the edges of the diamond shaped reachable zones
2) Use 3 point method to find out coefficients of f
3) Evaluate f at desired x
*/

// moving right, down, left, up
vector<vector<ll>> DIRS = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

vector<ll> getFUntil(ll maxStep, vector<vector<char>> gridTile) {
    // extend grid
    ll S = sz(gridTile);
    assert(S == sz(gridTile));
    ll factor = (maxStep / S) * 2 + 1;
    if (factor % 2 == 0)
        factor++; // we want to start right in the middle
    ll S_NEW = S * factor;

    vector<vector<char>> grid(S_NEW, vector<char>(S_NEW));
    rep(y, S_NEW)
        rep(x, S_NEW)
            grid[y][x] = gridTile[y % S][x % S] == '#' ? '#' : '.'; // no start point yet

    grid[S_NEW / 2][S_NEW / 2] = 'O';

    vector<ll> f = {1};
    rep(bfsStep, maxStep) {
        vector<vector<char>> newGrid(S_NEW, vector<char>(S_NEW));

        rep(y, S_NEW) {
            rep(x, S_NEW) {
                if (grid[y][x] == 'O') {
                    rep(d, 4) {
                        ll nx = x + DIRS[d][0];
                        ll ny = y + DIRS[d][1];
                        if (nx == -1 || ny == -1 || max(nx, ny) == S_NEW || grid[ny][nx] == '#')
                            continue;
                        newGrid[ny][nx] = 'O';
                    }
                } else if (grid[y][x] == '#') {
                    newGrid[y][x] = '#';
                }
            }
        }

        grid = newGrid;

        ll possibilities = 0;
        rep(y, S_NEW)
            rep(x, S_NEW)
                possibilities += grid[y][x] == 'O';
        f.push_back(possibilities);
    }

    return f;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    ifstream fp_in("input.txt", ios::in);
    string s;
    vector<vector<char>> grid;
    while (getline(fp_in, s)) {
        vector<char> v;
        repAll(c, s) v.push_back(c);
        grid.push_back(v);
    }

    ll H = sz(grid),
       W = sz(grid[0]),
       STEPS = 26501365;
    assert(H == W);

    // points of interest
    ll x1 = H / 2,
       x2 = x1 + H,
       x3 = x2 + H;

    assert((STEPS - x1) % H == 0);

    vector<ll> f = getFUntil(x3, grid);

    ll y1 = f[x1],
       y2 = f[x2],
       y3 = f[x3];

    ll a = (y3 - 2 * y2 + y1) / 2,
       b = y2 - y1 - a,
       c = y1;

    ll x = (STEPS - x1) / H;
    ll res = a * x * x + b * x + c;

    ofstream fp_out("output_2.txt", ios::out);
    fp_out << res << endl;
    fp_out.close();

    return 0;
}