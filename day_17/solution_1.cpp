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
        number of steps in same direction (2 bits)
    */
    ull res = 0;
    res |= (x << 18);
    res |= (y << 10);
    res |= (dir << 2);
    res |= straightSteps;
    return res;
}

ull getX(ull binRep) {
    return (binRep >> 18) & 255;
}
ull getY(ull binRep) {
    return (binRep >> 10) & 255;
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
                reps(straightSteps, 1, 4)
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
                rep(historyDirection, 4) {
                    if (stepDirection == (historyDirection + 2) % 4)
                        continue; // no turning back
                    rep(straightSteps, 4) {
                        ull newStraightSteps = historyDirection == stepDirection ? straightSteps + 1 : 1;
                        if (newStraightSteps > 3)
                            continue;
                        ull from = binarify(x, y, historyDirection, straightSteps);
                        ull to = binarify(nx, ny, stepDirection, newStraightSteps);
                        adj[from].push_back(to);
                    }
                }
            }
        }
    }

    ull start = binarify(0, 0, 0, 0);
    vector<ull> targets;
    rep(stepDirection, 2)
        reps(straightSteps, 1, 4)
            targets.push_back(binarify(W - 1, H - 1, stepDirection, straightSteps));

    ull res = dijkstra(start, targets, adj, heatLossValues);

    ofstream fp_out("output_1.txt", ios::out);
    fp_out << res << endl;
    fp_out.close();

    return 0;
}