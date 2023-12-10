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

    // BFS
    ll startX = x, startY = y;
    ll steps = 0;
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
                x = nx;
                y = ny;
                lastD = d;
                steps++;
                break;
            }
        }
        if (x == startX && y == startY)
            break;
    }

    ll res = steps / 2;

    ofstream fp_out("output_1.txt", ios::out);
    fp_out << res << endl;
    fp_out.close();

    return 0;
}