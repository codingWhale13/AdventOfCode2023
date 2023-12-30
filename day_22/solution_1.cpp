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

vector<ll> UP = {0, 0, 1};
vector<ll> DOWN = {0, 0, -1};
vector<ll> LEFT = {-1, 0, 0};
vector<ll> RIGHT = {1, 0, 0};
vector<ll> FRONT = {0, 1, 0};
vector<ll> BACK = {0, -1, 0};
vector<vector<ll>> DIRS = {LEFT, RIGHT, FRONT, BACK};

ll getFreeUnitsBelow(vector<vector<ll>> &brick, vector<vector<vector<ll>>> &grid) {
    ll lowestZ = brick[0][2];
    ll freeUnitsBelow = 0;
    while (lowestZ > 1) { // while brick is not on ground
        bool isFree = true;
        lowestZ--; // check if brick can fall one step
        reps(x, brick[0][0], brick[1][0] + 1) {
            reps(y, brick[0][1], brick[1][1] + 1) {
                if (grid[x][y][lowestZ] != 0) {
                    isFree = false;
                    break;
                }
            }
            if (!isFree) {
                break;
            }
        }
        if (isFree) {
            freeUnitsBelow++;
        } else {
            lowestZ++; // revert to last legal position
            break;
        }
    }

    return freeUnitsBelow;
}

void letItFall(vector<vector<ll>> &brick, ll brickId, vector<vector<vector<ll>>> &grid, ll freeUnitsBelow) {
    // remove block from old position
    reps(x, brick[0][0], brick[1][0] + 1) {
        reps(y, brick[0][1], brick[1][1] + 1) {
            reps(z, brick[0][2], brick[1][2] + 1) {
                grid[x][y][z] = 0;
            }
        }
    }

    brick[0][2] -= freeUnitsBelow;
    brick[1][2] -= freeUnitsBelow;

    // build block at new position
    reps(x, brick[0][0], brick[1][0] + 1) {
        reps(y, brick[0][1], brick[1][1] + 1) {
            reps(z, brick[0][2], brick[1][2] + 1) {
                grid[x][y][z] = brickId;
            }
        }
    }
}

int main() {
    ifstream fp_in("input.txt", ios::in);
    // grid holds brick ids, 0 means empty, ids start with 1, indexed as [x][y][z]
    vector<vector<vector<ll>>> grid(10, vector<vector<ll>>(10, vector<ll>(400, 0)));
    map<ll, vector<vector<ll>>> bricks;
    ll brickId = 1;
    string line, s;
    while (getline(fp_in, line)) {
        istringstream iss(line);
        getline(iss, s, ',');
        ll x1 = stoll(s);
        getline(iss, s, ',');
        ll y1 = stoll(s);
        getline(iss, s, '~');
        ll z1 = stoll(s);
        getline(iss, s, ',');
        ll x2 = stoll(s);
        getline(iss, s, ',');
        ll y2 = stoll(s);
        getline(iss, s);
        ll z2 = stoll(s);

        ll minX = min(x1, x2);
        ll minY = min(y1, y2);
        ll minZ = min(z1, z2);
        ll maxX = max(x1, x2);
        ll maxY = max(y1, y2);
        ll maxZ = max(z1, z2);

        reps(x, minX, maxX + 1) {
            reps(y, minY, maxY + 1) {
                reps(z, minZ, maxZ + 1) {
                    grid[x][y][z] = brickId;
                }
            }
        }
        bricks[brickId] = {{minX, minY, minZ}, {maxX, maxY, maxZ}};

        brickId++;
    }

    // apply gravity
    bool somethingChanged = true;
    while (somethingChanged) {
        somethingChanged = false;
        repAll(brickData, bricks) {
            ll brickId = brickData.first;
            vector<vector<ll>> brick = brickData.second;
            ll freeUnitsBelow = getFreeUnitsBelow(brick, grid);

            if (freeUnitsBelow > 0) {
                somethingChanged = true;
                letItFall(brick, brickId, grid, freeUnitsBelow);
                bricks[brickId] = brick;
            }
        }
    }

    // count disintegratable blocks
    ll res = 0;
    repAll(brickDataToRemove, bricks) {
        // remove candidate
        ll brickIdToRemove = brickDataToRemove.first;
        vector<vector<ll>> brickToRemove = brickDataToRemove.second;
        reps(x, brickToRemove[0][0], brickToRemove[1][0] + 1) {
            reps(y, brickToRemove[0][1], brickToRemove[1][1] + 1) {
                reps(z, brickToRemove[0][2], brickToRemove[1][2] + 1) {
                    grid[x][y][z] = 0;
                }
            }
        }

        bool disintegratable = true;
        repAll(brickDataToCheck, bricks) {
            if (brickDataToRemove.first == brickDataToCheck.first)
                continue;
            ll freeUnitsBelow = getFreeUnitsBelow(brickDataToCheck.second, grid);
            if (freeUnitsBelow > 0) {
                disintegratable = false;
                break;
            }
        }

        // restore candidate
        reps(x, brickToRemove[0][0], brickToRemove[1][0] + 1) {
            reps(y, brickToRemove[0][1], brickToRemove[1][1] + 1) {
                reps(z, brickToRemove[0][2], brickToRemove[1][2] + 1) {
                    grid[x][y][z] = brickIdToRemove;
                }
            }
        }

        if (disintegratable) {
            res++;
        }
    }

    ofstream fp_out("output_1.txt", ios::out);
    fp_out << res << endl;
    fp_out.close();

    return 0;
}