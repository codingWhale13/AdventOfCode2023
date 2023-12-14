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

void rotateClockwise(vector<vector<char>> &grid) {
    ll newH = sz(grid[0]), newW = sz(grid);
    vector<vector<char>> newGrid(newH, vector<char>(newW));

    rep(y, newH)
        rep(x, newW)
            newGrid[y][x] = grid[newW - x - 1][y];

    grid = newGrid;
}

void rollNorth(vector<vector<char>> &grid) {
    rep(x, sz(grid[0])) {
        rep(y, sz(grid)) {
            if (grid[y][x] == 'O') {
                ll newY = y;
                while (newY > 0 && grid[newY - 1][x] == '.')
                    newY--;
                grid[y][x] = '.';
                grid[newY][x] = 'O';
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    ifstream fp_in("input.txt", ios::in);
    string s;
    vector<vector<char>> grid;
    while (getline(fp_in, s)) {
        vector<char> row;
        repAll(c, s) row.push_back(c);
        grid.push_back(row);
    }
    fp_in.close();

    ll dir = 0; // 0=N, 1=W, 2=S,3=E

    // tilt in NWSE cycles a bunch of times
    rep(i, 1000) {
        rep(i, 4) {
            rollNorth(grid);
            rotateClockwise(grid);
        }
    }

    // count
    ll res = 0;
    rep(x, sz(grid[0]))
        rep(y, sz(grid)) if (grid[y][x] == 'O')
            res += sz(grid) - y;

    ofstream fp_out("output_2.txt", ios::out);
    fp_out << res << endl;
    fp_out.close();

    return 0;
}