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
    string s;
    vector<string> grid;
    while (getline(fp_in, s))
        grid.push_back(s);
    fp_in.close();

    ll H = sz(grid);
    ll W = sz(grid[0]);

    // moving right, down, left, up
    vector<vector<ll>> DIRS = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    vector<vector<ll>> CHANGES = {
        {DIRS[0][0], DIRS[0][1], 0},
        {DIRS[1][0], DIRS[1][1], 1},
        {DIRS[2][0], DIRS[2][1], 2},
        {DIRS[3][0], DIRS[3][1], 3}};

    map<char, vector<vector<vector<ll>>>>
        m = {
            {'.',
             {
                 {CHANGES[0]},
                 {CHANGES[1]},
                 {CHANGES[2]},
                 {CHANGES[3]},
             }},
            {'/',
             {
                 {CHANGES[3]},
                 {CHANGES[2]},
                 {CHANGES[1]},
                 {CHANGES[0]},
             }},
            {'\\',
             {
                 {CHANGES[1]},
                 {CHANGES[0]},
                 {CHANGES[3]},
                 {CHANGES[2]},
             }},
            {'-', {
                      {CHANGES[0]},
                      {CHANGES[0], CHANGES[2]},
                      {CHANGES[2]},
                      {CHANGES[0], CHANGES[2]},
                  }},
            {'|', {
                      {CHANGES[1], CHANGES[3]},
                      {CHANGES[1]},
                      {CHANGES[1], CHANGES[3]},
                      {CHANGES[3]},
                  }}};

    deque<vector<ll>> points = {{0, 0, 0}};
    vector<vector<vector<bool>>> visited(H, vector<vector<bool>>(W, vector<bool>(4, false)));
    while (!points.empty()) {
        vector<ll> p = points.front();
        points.pop_front();
        ll x = p[0];
        ll y = p[1];
        ll d = p[2];

        if (visited[y][x][d])
            continue;
        visited[y][x][d] = true;

        repAll(v, m[grid[y][x]][d]) {
            ll nx = x + v[0];
            ll ny = y + v[1];
            ll nd = v[2];
            if (-1 < nx && nx < W && -1 < ny && ny < H)
                points.push_back({nx, ny, nd});
        }
    }

    ll res = 0;
    rep(y, H) {
        rep(x, W) {
            if (visited[y][x][0] || visited[y][x][1] || visited[y][x][2] || visited[y][x][3])
                res++;
        }
    }

    ofstream fp_out("output_1.txt", ios::out);
    fp_out << res << endl;
    fp_out.close();

    return 0;
}