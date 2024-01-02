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

ll posToId(ll x, ll y, ll W) {
    return y * W + x;
}

ll getLengthOfScenicRoute(map<ll, vector<pair<ll, ll>>> &adj, ll current, ll target) {
    ll res = 0;
    queue<ll> q;
    ll maxSteps = 0;
    repAll(neighborData, adj[current]) {
        ll neighbor = neighborData.first;
        ll pathLength = neighborData.second;
        ll steps = pathLength + getLengthOfScenicRoute(adj, neighbor, target);
        maxSteps = max(maxSteps, steps);
    }

    return maxSteps;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    // moving right (0), down (1), left (2), up (3)
    vector<vector<ll>> DIRS = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    map<char, ll> DIRS_CHAR = {{'>', 0}, {'v', 1}, {'<', 2}, {'^', 3}, {'#', -1}};

    ifstream fp_in("input.txt", ios::in);
    string s;
    vector<string> grid;
    while (getline(fp_in, s))
        grid.push_back(s);

    ll H = sz(grid);
    ll W = ln(grid[0]);

    vector<ll> start;
    rep(x, W) if (grid[0][x] == '.')
        start = {x, 0}; // get unique starting point in first row
    ll startId = posToId(start[0], start[1], W), targetId;

    // create condensed graph (skip hallways)
    map<ll, vector<pair<ll, ll>>> adj = {{startId, {}}};             // source -> {target, path length}
    vector<vector<ll>> todo = {{start[0], start[1], 1, 0, startId}}; // {x, y, direction, step count since last check point, previous id}

    while (sz(todo) > 0) {
        vector<ll> item = todo.back();
        todo.pop_back();

        ll x = item[0];
        ll y = item[1];
        ll oldDir = item[2];
        ll stepCount = item[3];
        ll previousId = item[4];

        vector<vector<ll>> possibleNextSteps; // x, y, dir
        rep(newDir, 4) {
            if (newDir == (oldDir + 2) % 4)
                continue; // no turning back

            ll nx = item[0] + DIRS[newDir][0];
            ll ny = item[1] + DIRS[newDir][1];

            if (nx == -1 || nx == W || ny == -1 || ny == H)
                continue; // out of bounds

            if (grid[ny][nx] != '.' && DIRS_CHAR[grid[ny][nx]] != newDir)
                continue; // can't go there

            possibleNextSteps.push_back({nx, ny, newDir});
        }

        if (sz(possibleNextSteps) == 0 && y == H - 1) {
            // reached target
            targetId = posToId(x, y, W);
            adj[previousId].push_back({targetId, stepCount});
        }

        if (sz(possibleNextSteps) == 1) {
            // just go along the corridor
            todo.push_back({possibleNextSteps[0][0],
                            possibleNextSteps[0][1],
                            possibleNextSteps[0][2],
                            stepCount + 1,
                            previousId});
        } else if (sz(possibleNextSteps) > 1) {
            for (vector<ll> nextPos : possibleNextSteps) {
                ll nx = nextPos[0];
                ll ny = nextPos[1];
                ll dir = nextPos[2];
                ll newId = posToId(nx, ny, W);

                adj[previousId].push_back({newId, stepCount + 1}); // + 1 to account for target itself

                if (adj.find(newId) == adj.end())
                    todo.push_back({nx, ny, dir, 0, newId}); // keep exploring
            }
        }
    }

    ll res = getLengthOfScenicRoute(adj, startId, targetId);

    ofstream fp_out("output_1.txt", ios::out);
    fp_out << res << endl;
    fp_out.close();

    return 0;
}
