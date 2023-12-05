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

pair<ll, ll> unifyRanges(pair<ll, ll> range1, pair<ll, ll> range2) {
    ll start1 = range1.first;
    ll end1 = range1.second;
    ll start2 = range2.first;
    ll end2 = range2.second;

    if (end1 < start2 || end2 < start1)
        return {-1, -1}; // no overlap

    return {min(start1, start2), max(end1, end2)};
}

pair<pair<ll, ll>, vector<pair<ll, ll>>> getMappedRanges(pair<ll, ll> seedRange, pair<ll, ll> mapRange, ll change) {
    ll start1 = seedRange.first;
    ll end1 = seedRange.second;
    ll start2 = mapRange.first;
    ll end2 = mapRange.second;

    if (end1 < start2 || end2 < start1)
        return {{-1, -1}, {seedRange}}; // nothing changes

    // some values found their wormhole, yay!
    pair<ll, ll> transformedValues = {max(start1, start2) + change, min(end1, end2) + change};

    vector<pair<ll, ll>> unchangedRanges;
    if (start1 < start2)
        unchangedRanges.push_back({start1, start2 - 1});
    if (end2 < end1)
        unchangedRanges.push_back({end2 + 1, end1});

    return {transformedValues, unchangedRanges};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    ifstream fp_in("input.txt", ios::in);
    string s, t, u, rngRng, dstStr, srcStr, rngStr;

    getline(fp_in, s);
    istringstream iss(s);
    iss >> s; // "seeds:"
    vector<pair<ll, ll>> seedRanges;
    while (iss >> srcStr) {
        iss >> rngStr;
        ll start = stoll(srcStr);
        ll end = start + stoll(rngStr);
        seedRanges.push_back({start, end});
    }
    getline(fp_in, s); // ignore empty line

    vector<vector<vector<ll>>> maps;
    while (getline(fp_in, s)) { // [a-to-b]
        vector<vector<ll>> whateverMap;
        getline(fp_in, s);
        while (ln(s) != 0) {
            istringstream iss(s);
            iss >> dstStr >> srcStr >> rngStr;
            whateverMap.push_back({stoll(dstStr), stoll(srcStr), stoll(rngStr)});
            getline(fp_in, s);
        }
        maps.push_back(whateverMap);
    }

    // what's changed? we don't go seed by seed but map by map, carrying all valid seed ranges with us
    repAll(whateverMap, maps) {
        vector<pair<ll, ll>> newSeedRanges;
        repAll(oldSeedRange, seedRanges) {
            vector<pair<ll, ll>> unchangedSeedRanges = {oldSeedRange};
            rep(i, sz(whateverMap)) { // iterate through transformation of the active map
                vector<pair<ll, ll>> newunchangedSeedRanges;
                repAll(unchangedSeedRange, unchangedSeedRanges) {
                    ll dst = whateverMap[i][0];
                    ll src = whateverMap[i][1];
                    ll rng = whateverMap[i][2];
                    auto uff = getMappedRanges(unchangedSeedRange, {src, src + rng}, dst - src);
                    pair<ll, ll> transformedRange = uff.first;
                    vector<pair<ll, ll>> stillUnchangedSeedRanges = uff.second;
                    if (transformedRange.first != -1)
                        newSeedRanges.push_back(transformedRange);
                    repAll(stillUnchangedRange, stillUnchangedSeedRanges)
                        newunchangedSeedRanges.push_back(stillUnchangedRange);
                }
                unchangedSeedRanges = newunchangedSeedRanges;
            }
            // these poor seeds haven't been wormholed
            repAll(unchangedSeedRange, unchangedSeedRanges) {
                newSeedRanges.push_back(unchangedSeedRange);
            }
        }
        seedRanges = newSeedRanges;

        // clean up
        vector<pair<ll, ll>> cleanedSeedRanges;
        sort(seedRanges.begin(), seedRanges.end());
        rep(i, sz(seedRanges) - 1) {
            pair<ll, ll> unifiedRange = unifyRanges(seedRanges[i], seedRanges[i + 1]);

            if (unifiedRange.first == -1) {
                cleanedSeedRanges.push_back(seedRanges[i]);
            } else {
                seedRanges[i + 1] = unifiedRange;
            }
        }
        cleanedSeedRanges.push_back(seedRanges[sz(seedRanges) - 1]);
        seedRanges = cleanedSeedRanges;
    }

    ll res = INF;
    repAll(seedRange, seedRanges) {
        res = min(res, seedRange.first);
    }

    fp_in.close();
    ofstream fp_out("output_2.txt", ios::out);
    fp_out << res << endl;
    fp_out.close();

    return 0;
}