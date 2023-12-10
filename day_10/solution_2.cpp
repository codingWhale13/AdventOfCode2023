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

// NESW
vector<vector<ll>> DIRS = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
map<char, vector<bool>> OPTIONS = {
    {'|', {true, false, true, false}},
    {'-', {false, true, false, true}},
    {'L', {true, true, false, false}},
    {'J', {true, false, false, true}},
    {'7', {false, false, true, true}},
    {'F', {false, true, true, false}},
    {'.', {false, false, false, false}},
    {'S', {true, true, true, true}}};

bool isEnclosed(ll x, ll y, vector<vector<bool>> &grid, vector<vector<ll>> &cellStates) {
    // BFS
    vector<vector<ll>> todo = {{x, y}};
    vector<vector<bool>> visited(sz(grid), vector<bool>(sz(grid[0]), false));
    visited[y][x] = true;
    while (sz(todo) > 0) {
        vector<vector<ll>> newTodo;
        repAll(pos, todo) {
            rep(d, 4) {
                ll nx = pos[0] + DIRS[d][0];
                ll ny = pos[1] + DIRS[d][1];
                if (!(-1 < nx && nx < sz(grid[0]) && -1 < ny && ny < sz(grid))) {
                    rep(i, sz(visited)) {
                        rep(j, sz(visited[0])) {
                            if (visited[i][j])
                                cellStates[i][j] = -1;
                        }
                    }
                    return false; // found a way to escape
                }

                if (cellStates[ny][nx] == 1)
                    return true;
                else if (cellStates[ny][nx] == -1)
                    return false;

                if (!visited[ny][nx] && !grid[ny][nx]) {
                    newTodo.push_back({nx, ny});
                    visited[ny][nx] = true;
                }
            }
        }
        todo = newTodo;
    }
    rep(i, sz(visited)) {
        rep(j, sz(visited[0])) {
            if (visited[i][j])
                cellStates[i][j] = 1;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    ifstream fp_in("input.txt", ios::in);
    string line;
    vector<string> grid;
    ll x, y;
    while (getline(fp_in, line)) {
        grid.push_back(line);
        auto startX = line.find('S');
        if (startX != string::npos) {
            x = startX;
            y = sz(grid) - 1;
        }
    }
    fp_in.close();

    //  construct grid twice as large (true <-> path)
    vector<vector<bool>> bigGrid(sz(grid) * 2, vector<bool>(ln(grid[0]) * 2, false));
    ll startX = x, startY = y;
    ll lastD = -1;
    while (true) {
        rep(d, 4) {
            if (d == (lastD + 2) % 4)
                continue; // no turning back

            ll nx = x + DIRS[d][0];
            ll ny = y + DIRS[d][1];
            if (!(-1 < nx && nx < ln(grid[0]) && -1 < ny && ny < sz(grid)))
                continue; // out of bounds

            if (OPTIONS[grid[y][x]][d] && OPTIONS[grid[ny][nx]][(d + 2) % 4]) {
                bigGrid[y * 2][x * 2] = true;                           // mark old position as part of path
                bigGrid[y * 2 + DIRS[d][1]][x * 2 + DIRS[d][0]] = true; // mark in-between step as part of path
                x = nx;
                y = ny;
                lastD = d;
                break;
            }
        }
        if (x == startX && y == startY)
            break;
    }

    // for each cell, check if it's enclosed
    // has serious potential for optimization but whatever
    // cell states: 0 is unexplored, 1 is enclosed, -1 leads to freedom
    vector<vector<ll>> cellStates(sz(bigGrid), vector<ll>(sz(bigGrid[0]), 0));
    ll res = 0;
    rep(originalY, sz(grid)) {
        rep(originalX, ln(grid[0])) {
            ll x = originalX * 2;
            ll y = originalY * 2;

            if (bigGrid[y][x])
                continue; // part of path -> not enclosed

            cout << x << " " << y << endl;

            if (isEnclosed(x, y, bigGrid, cellStates))
                res++;
        }
    }

    ofstream fp_out("output_2.txt", ios::out);
    fp_out << res << endl;
    fp_out.close();

    return 0;
}