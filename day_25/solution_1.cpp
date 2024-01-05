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

ll getBoss(ll u, vector<ll> &hierarchy) {
    while (hierarchy[u] != u)
        u = hierarchy[u];
    return u;
}

// https://www.cs.princeton.edu/courses/archive/fall13/cos521/lecnotes/lec2final.pdf
ll kargersMinCut(vector<pair<ll, ll>> edges, ll nodeCount) {
    vector<ll> hierarchy(nodeCount);
    rep(u, nodeCount)
        hierarchy[u] = u;

    rep(collapseIteration, nodeCount - 2) {
        // randomly select edge to collapse
        ll r = rand() % sz(edges);
        ll u = edges[r].first;
        ll v = edges[r].second;
        edges.erase(edges.begin() + r);

        ll uBoss = getBoss(u, hierarchy);
        ll vBoss = getBoss(v, hierarchy);
        assert(uBoss != vBoss);

        // merge uBoss and vBoss
        for (ll i = sz(edges) - 1; i > -1; i--) {
            ll wBoss = getBoss(edges[i].first, hierarchy);
            ll xBoss = getBoss(edges[i].second, hierarchy);
            if (wBoss == uBoss && xBoss == vBoss || wBoss == vBoss && xBoss == uBoss)
                edges.erase(edges.begin() + i);
        }

        hierarchy[uBoss] = vBoss; // finalize merge
    }

    if (sz(edges) == 3) {
        map<ll, ll> groupSizes;
        rep(i, nodeCount) {
            ll boss = getBoss(i, hierarchy);
            if (groupSizes.find(boss) == groupSizes.end())
                groupSizes[boss] = 0;
            groupSizes[boss]++;
        }

        assert(sz(groupSizes) == 2);

        ll res = 1;
        repAll(group, groupSizes)
            res *= group.second;

        return res;
    }

    return -1; // no luck this time
}

int main() {
    srand(time(NULL));

    ifstream fp_in("input.txt", ios::in);
    string s;
    vector<vector<ll>> adj;
    ll nextComponentId = 0;
    map<string, ll> componentMap;
    while (getline(fp_in, s)) {
        istringstream iss(s);
        string a, b;
        getline(iss, a, ':');

        ll idA, idB;
        if (componentMap.find(a) == componentMap.end()) {
            idA = nextComponentId;
            componentMap[a] = nextComponentId++;
        } else {
            idA = componentMap[a];
        }

        while (iss >> b) {
            if (componentMap.find(b) == componentMap.end()) {
                idB = nextComponentId;
                componentMap[b] = nextComponentId++;
            } else {
                idB = componentMap[b];
            }

            while (sz(adj) - 1 < max(idA, idB))
                adj.push_back({});

            adj[idA].push_back(idB);
        }
    }
    fp_in.close();

    ll n = sz(adj);
    vector<pair<ll, ll>> edges;
    rep(u, n)
        repAll(v, adj[u])
            edges.push_back({u, v});
    ll res = -1;
    while (res == -1)
        res = kargersMinCut(edges, n);

    ofstream fp_out("output_1.txt", ios::out);
    fp_out << res << endl;
    fp_out.close();

    return 0;
}
