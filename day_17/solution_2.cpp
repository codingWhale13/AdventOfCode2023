#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define rep(a, b) for (ll a = 0; a < (b); ++a)
#define reps(a, b, c) for (ll a = b; a < (c); ++a)
#define repAll(i, v) for (auto &i : v)
#define sz(a) ((ll)((a).size()))
#define ln(a) ((ll)((a).length()))

const ll INF = numeric_limits<ll>::max();

ull binarify(ull x, ull y, ull dir, ull straightSteps) {
    /* binary representation:
        x (8 bits)
        y (8 bits)
        direction (2 bits)
        number of steps in same direction (4 bits)
    */
    ull res = 0;
    res |= (x << 20);
    res |= (y << 12);
    res |= (dir << 4);
    res |= straightSteps;
    return res;
}

ull getX(ull binRep) {
    return (binRep >> 20) & 255;
}
ull getY(ull binRep) {
    return (binRep >> 12) & 255;
}

ull dijkstra(ull start, vector<ull> targets, map<ull, vector<ull>> &adj, vector<vector<ll>> &heatLossValues) {
    map<ull, ll> distance;
    map<ull, bool> processed;
    repAll(u, adj) {
        distance[u.first] = INF;
        processed[u.first] = false;
    }

    distance[start] = 0;
    priority_queue<pair<ll, ull>> q; // {cost, node}
    q.push({0, start});
    while (!q.empty()) {
        ull a = q.top().second;
        q.pop();
        if (processed[a])
            continue;
        processed[a] = true;
        for (ull b : adj[a]) {
            ull x = getX(b);
            ull y = getY(b);
            ll w = heatLossValues[y][x];
            if (distance[a] + w < distance[b]) {
                distance[b] = distance[a] + w;
                q.push({-distance[b], b});
            }
        }
    }

    ll res = INF;
    repAll(target, targets)
        res = min(res, distance[target]);

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    // moving right, down, left, up
    vector<vector<ll>> DIRS = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    ifstream fp_in("input.txt", ios::in);
    string s;
    vector<vector<ll>> heatLossValues;
    while (getline(fp_in, s)) {
        vector<ll> heatLossRow(ln(s));
        rep(i, ln(s))
            heatLossRow[i] = s[i] - '0';
        heatLossValues.push_back(heatLossRow);
    }
    fp_in.close();

    ull H = sz(heatLossValues);
    ull W = sz(heatLossValues[0]);
    assert(H <= 256 && W <= 256); // otherwise, binary representation doesn't work

    // build adjanceny list of possibilities
    // (plus some nonsensical for convenience, coming from the sides of the grid)
    map<ull, vector<ull>> adj;
    rep(y, H)
        rep(x, W)
            rep(d, 4)
                reps(straightSteps, 1, 11)
                    adj[binarify(x, y, d, straightSteps)] = {};
    rep(d, 4)
        adj[binarify(0, 0, d, 0)] = {};

    rep(y, H) {
        rep(x, W) {
            rep(stepDirection, 4) {
                ll nx = x + DIRS[stepDirection][0];
                ll ny = y + DIRS[stepDirection][1];
                if (nx == -1 || ny == -1 || nx == W || ny == H)
                    continue;

                // keep going in the same direction
                rep(straightSteps, 10) {
                    ull from = binarify(x, y, stepDirection, straightSteps);
                    ull to = binarify(nx, ny, stepDirection, straightSteps + 1);
                    adj[from].push_back(to);
                }

                // turn left or right
                rep(historyDirection, 4) {
                    if (stepDirection % 2 == historyDirection % 2)
                        continue; // no turning back or going straight
                    reps(straightSteps, 4, 11) {
                        ull from = binarify(x, y, historyDirection, straightSteps);
                        ull to = binarify(nx, ny, stepDirection, 1);
                        adj[from].push_back(to);
                    }
                }
            }
        }
    }

    // we consider two starting points, looking right and down
    // reason: turning "on the spot" like in part 1 isn't possible anymore
    ull start1 = binarify(0, 0, 0, 0);
    ull start2 = binarify(0, 0, 1, 0);
    vector<ull> targets;
    rep(stepDirection, 2)
        reps(straightSteps, 4, 11)
            targets.push_back(binarify(W - 1, H - 1, stepDirection, straightSteps));

    ull res1 = dijkstra(start1, targets, adj, heatLossValues);
    ull res2 = dijkstra(start2, targets, adj, heatLossValues);
    ull res = min(res1, res2);

    ofstream fp_out("output_2.txt", ios::out);
    fp_out << res << endl;
    fp_out.close();

    return 0;
}