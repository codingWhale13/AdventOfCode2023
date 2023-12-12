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

ll countArrangements(string &record, vector<ll> &values, ll recordIdx, ll valuesIdx, vector<vector<ll>> &cache) {
    if (recordIdx >= ln(record))
        return valuesIdx == sz(values); // 0 or 1

    if (valuesIdx >= sz(values)) {
        // make sure all remaining positions can be operational
        bool noRemainingDamagedSprings = true;
        while (recordIdx < ln(record)) {
            if (record[recordIdx] == '#') {
                noRemainingDamagedSprings = false;
                break;
            }
            recordIdx++;
        }
        return noRemainingDamagedSprings; // 0 or 1
    }

    if (cache[recordIdx][valuesIdx] != -1)
        return cache[recordIdx][valuesIdx];

    ll res = 0, value = values[valuesIdx];
    if (record[recordIdx] != '#')
        res += countArrangements(record, values, recordIdx + 1, valuesIdx, cache);

    // NOTE: cache is only effective if we call countArrangements here as soon as we can
    // (instead of just keeping iterating)
    if (record[recordIdx] != '.' && recordIdx < ln(record) - value + 1) {
        bool isNotDamagedAfter = recordIdx + value == ln(record) || record[recordIdx + value] != '#';
        bool canBeDamaged = true;
        reps(i, recordIdx, recordIdx + value) {
            if (record[i] == '.') {
                canBeDamaged = false;
                break;
            }
        }
        if (isNotDamagedAfter && canBeDamaged)
            res += countArrangements(record, values, recordIdx + value + 1, valuesIdx + 1, cache);
    }

    cache[recordIdx][valuesIdx] = res;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    ifstream fp_in("input.txt", ios::in);
    string record, valuesRaw, valueRaw;
    ll res = 0;
    while (fp_in >> record) {
        fp_in >> valuesRaw;
        istringstream valueStream(valuesRaw);
        vector<ll> values;
        while (getline(valueStream, valueRaw, ','))
            values.push_back(stoll(valueRaw));

        // duplicate record and values
        ll originalValueCount = sz(values);
        string originalRecord = record;
        rep(i, 4) {
            record += '?' + originalRecord;
            rep(j, originalValueCount)
                values.push_back(values[j]);
        }

        vector<vector<ll>> cache(ln(record) + 2, vector<ll>(sz(values) + 2, -1));
        res += countArrangements(record, values, 0, 0, cache);
    }
    fp_in.close();

    ofstream fp_out("output_2.txt", ios::out);
    fp_out << res << endl;
    fp_out.close();

    return 0;
}

/*
1 2 3 2 1 1 2 3 2 1 1 2 3 2 1 1 2 3 2 1 1 2 3 2 1 .#?#???????.????#?.#?#???????.????#?.#?#???????.????#?.#?#???????.????#?.#?#???????.????# 1525248
CACHE hits misses: 10886 79151 1 4 1 1 4 1 1 4 1 1 4 1 1 4 ?????????????????????????????????????????????????????? 5764904
CACHE hits misses: 865311542 4025841321 2 1 2 1 2 1 2 1 2 ????.??.??.????????.??.??.????????.??.??.????????.??.??.????????.??.??.??? 1901239241
*/