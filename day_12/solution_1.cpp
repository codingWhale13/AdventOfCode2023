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

ll countArrangements(string &record, vector<ll> &values, ll recordIdx, ll valuesIdx) {
    if (valuesIdx == sz(values)) {
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

    // try all combinations to fit `value` many consecutive damaged springs
    ll res = 0, value = values[valuesIdx];
    while (recordIdx < ln(record) - value + 1) {
        bool isNotDamagedBefore = recordIdx == 0 || record[recordIdx - 1] != '#';
        bool isNotDamagedAfter = record[recordIdx + value] != '#';
        bool canBeDamaged = true;
        reps(i, recordIdx, recordIdx + value) {
            if (record[i] == '.') {
                canBeDamaged = false;
                break;
            }
        }
        if (isNotDamagedBefore && isNotDamagedAfter && canBeDamaged)
            res += countArrangements(record, values, recordIdx + value + 1, valuesIdx + 1);

        if (record[recordIdx] == '#')
            break; // we have to start the next group of broken springs here, can't skip it!

        recordIdx++;
    }
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

        res += countArrangements(record, values, 0, 0);
    }
    fp_in.close();

    ofstream fp_out("output_1.txt", ios::out);
    fp_out << res << endl;
    fp_out.close();

    return 0;
}