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
    string nav, start, left, right;
    fp_in >> nav;

    map<string, pair<string, string>> network;
    vector<string> starts, targets;
    while (fp_in >> start) {
        fp_in >> left >> left >> right;
        left = left.substr(1, 3);
        right = right.substr(0, 3);

        network[start] = {left, right};

        if (start[2] == 'A')
            starts.push_back(start);
        if (start[2] == 'Z')
            targets.push_back(start);
    }

    cout << "There are " << sz(starts) << " starts, " << sz(targets) << " targets, and " << sz(network) << " nodes in total." << endl;

    vector<ll> ghostPositions, cycleTimes;
    repAll(start, starts) {
        ll t = 0, cycleStart;
        map<pair<string, ll>, ll> visitTimes; // keep track of points in space-time continuum: {pos, navIdx} -> time
        pair<string, ll> cur = {start, 0};
        vector<ll> targetTimes;
        while (!(visitTimes.find(cur) != visitTimes.end())) {
            if (find(targets.begin(), targets.end(), cur.first) != targets.end()) {
                targetTimes.push_back(t);
            }

            visitTimes[cur] = t;
            t++;

            if (nav[cur.second] == 'L')
                cur.first = network[cur.first].first;
            else
                cur.first = network[cur.first].second;
            cur.second = (cur.second + 1) % ln(nav);
        }
        ll burnInTime = visitTimes[cur];
        ll cycleTime = t - visitTimes[cur];
        ghostPositions.push_back(burnInTime);
        cycleTimes.push_back(cycleTime);

        cout << "Burn-in time: " << burnInTime << ", cycle time: " << cycleTime << ", targets:";
        rep(i, sz(targetTimes)) cout << ' ' << targetTimes[i];
        cout << endl;
    }
    cout << "The puzzle input seems to be generated in a way that:" << endl;
    cout << "- Each ghost is only able to reach one target." << endl;
    cout << "- Each ghost reaches its target for the first time after only a few steps." << endl;
    cout << "- For each ghost, the first repeating position is a target." << endl;

    ll res = lcm(cycleTimes[0], cycleTimes[1]);
    reps(i, 2, sz(cycleTimes))
        res = lcm(cycleTimes[i], res);

    ofstream fp_out("output_2.txt", ios::out);
    fp_out << res << endl;
    fp_out.close();

    return 0;
}