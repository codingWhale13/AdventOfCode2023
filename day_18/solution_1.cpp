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

ll GRID_SIZE = 500;
map<char, pair<ll, ll>> DIRS = {
    {'U', {0, -1}},
    {'R', {1, 0}},
    {'D', {0, 1}},
    {'L', {-1, 0}},
};

void floodfill(vector<vector<char>> &grid, pair<ll, ll> start) {
    if (grid[start.second][start.first] != '?')
        return;
    vector<vector<bool>> visited(GRID_SIZE, vector<bool>(GRID_SIZE, false));
    visited[start.second][start.first] = true;
    vector<pair<ll, ll>> todo = {start};
    char cellType = '#'; // assume we're inside
    while (todo.size()) {
        pair<ll, ll> pos = todo.back();
        todo.pop_back();
        repAll(d, DIRS) {
            ll nx = pos.first + d.second.first;
            ll ny = pos.second + d.second.second;
            if (nx == -1 || nx == GRID_SIZE || ny == -1 || ny == GRID_SIZE) {
                cellType = '.';
                continue;
            }
            if (grid[ny][nx] != '#' && !visited[ny][nx]) {
                visited[ny][nx] = true;
                todo.push_back({nx, ny});
            }
        }
    }

    // mark all visited positions as inside
    ll abc = 0;
    rep(y, GRID_SIZE)
        rep(x, GRID_SIZE) if (visited[y][x]) {
        grid[y][x] = cellType;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    vector<vector<char>> grid(GRID_SIZE, vector<char>(GRID_SIZE, '?')); // ?#. (unknown, inside, outside)
    ll x = GRID_SIZE / 2;
    ll y = GRID_SIZE / 2;

    ifstream fp_in("input.txt", ios::in);
    char c;
    ll steps;
    string whatever;
    while (fp_in >> c) {
        fp_in >> steps >> whatever;
        while (steps--) {
            grid[y][x] = '#';

            x += DIRS[c].first;
            y += DIRS[c].second;
        }
    }

    rep(y, GRID_SIZE)
        rep(x, GRID_SIZE)
            floodfill(grid, {x, y});

    ll res = 0;
    rep(y, GRID_SIZE)
        rep(x, GRID_SIZE) if (grid[y][x] == '#')
            res++;

    ofstream fp_out("output_1.txt", ios::out);
    fp_out << res << endl;
    fp_out.close();

    return 0;
}