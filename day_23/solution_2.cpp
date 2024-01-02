#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define rep(a, b) for (ll a = 0; a < (b); ++a)
#define reps(a, b, c) for (ll a = b; a < (c); ++a)
#define frep(a) while ((a)--)
#define repAll(i, v) for (auto &i : v)
#define sz(a) ((ll)((a).size()))
#define ln(a) ((ll)((a).length()))

const ll NINF = numeric_limits<ll>::min();
const ll INF = numeric_limits<ll>::max();
const ll MOD = 1000000007;

ll posToId(ll x, ll y, ll W) {
    return y * W + x;
}

pair<ll, ll> idToPos(ll id, ll W) {
    return {id % W, id / W};
}

void getLengthOfScenicRoute(map<ll, vector<pair<ll, ll>>> &adj, ll node, ll target, set<ll> &visited, ll score, ll &bestScore) {
    if (node == target) {
        bestScore = max(bestScore, score);
        return;
    }

    repAll(neighborData, adj[node]) {
        ll neighbor = neighborData.first;
        ll pathLength = neighborData.second;

        if (visited.find(neighbor) != visited.end())
            continue;

        visited.insert(neighbor);
        getLengthOfScenicRoute(adj, neighbor, target, visited, score + pathLength, bestScore);
        visited.erase(neighbor);
    }
}

int main() {
    // moving right (0), down (1), left (2), up (3)
    vector<vector<ll>> DIRS = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    ifstream fp_in("input.txt", ios::in);
    string s;
    vector<string> grid;
    while (getline(fp_in, s))
        grid.push_back(s);

    ll H = sz(grid);
    ll W = ln(grid[0]);

    vector<ll> start, target;
    rep(x, W) if (grid[0][x] == '.')
        start = {x, 0}; // get unique starting point in first row
    rep(x, W) if (grid[H - 1][x] == '.')
        target = {x, H - 1}; // get unique starting point in last row
    ll startId = posToId(start[0], start[1], W), targetId = posToId(target[0], target[1], W);

    // create condensed graph (skip hallways)
    vector<ll> intersections = {startId, targetId}; // start and target are not technically intersections, naming is hard...
    map<ll, vector<ll>> neighborDirections;
    rep(y, H) {
        rep(x, W) {
            if (grid[y][x] == '#')
                continue;

            ll cur = posToId(x, y, W);
            neighborDirections[cur] = {};
            rep(d, 4) {
                ll nx = x + DIRS[d][0];
                ll ny = y + DIRS[d][1];

                if (nx == -1 || nx == W || ny == -1 || ny == H)
                    continue; // out of bounds

                if (grid[ny][nx] == '#')
                    continue; // can't go there

                neighborDirections[cur].push_back(d);
            }

            if (sz(neighborDirections[cur]) > 2)
                intersections.push_back(cur);
        }
    }

    map<ll, vector<pair<ll, ll>>> adj = {}; // source -> {target, path length}
    repAll(intersection, intersections) {
        adj[intersection] = {};
        repAll(neighborDirection, neighborDirections[intersection]) {
            // walk the corridor until next intersection
            ll pathLength = 1, nextIntersection;

            pair<ll, ll> startPos = idToPos(intersection, W);
            ll x = startPos.first + DIRS[neighborDirection][0],
               y = startPos.second + DIRS[neighborDirection][1];
            ll oldDir = neighborDirection;

            bool foundNextIntersection = false;
            while (!foundNextIntersection) {
                pathLength++;
                rep(newDir, 4) {
                    if (newDir == (oldDir + 2) % 4)
                        continue; // no turning back

                    ll nx = x + DIRS[newDir][0];
                    ll ny = y + DIRS[newDir][1];

                    if (nx == -1 || nx == W || ny == -1 || ny == H)
                        continue; // out of bounds

                    if (grid[ny][nx] == '#')
                        continue; // can't go there

                    ll newId = posToId(nx, ny, W);
                    if (find(intersections.begin(), intersections.end(), newId) != intersections.end()) {
                        foundNextIntersection = true;
                        nextIntersection = newId;
                    } else {
                        x = nx;
                        y = ny;
                        oldDir = newDir;
                    }
                    break; // found either the next intersection or the only possible next step
                }
            }
            adj[intersection].push_back({nextIntersection, pathLength});
        }
    }

    set<ll> visited = {startId};
    ll res = 0;
    getLengthOfScenicRoute(adj, startId, targetId, visited, 0, res);

    ofstream fp_out("output_2.txt", ios::out);
    fp_out << res << endl;
    fp_out.close();

    return 0;
}
