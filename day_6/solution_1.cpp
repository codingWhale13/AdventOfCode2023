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
    string timesStr, recordsStr;
    getline(fp_in, timesStr);
    getline(fp_in, recordsStr);
    fp_in.close();

    string timeStr, recordStr, trash;
    vector<ll> times, records;
    istringstream issTimes(timesStr), issRecords(recordsStr);
    issTimes >> trash;
    while (issTimes >> timeStr)
        times.push_back(stoll(timeStr));
    issRecords >> trash;
    while (issRecords >> recordStr)
        records.push_back(stoll(recordStr));

    ll res = 1;
    rep(raceId, sz(times)) {
        ll raceTime = times[raceId];
        ll record = records[raceId];
        ll waysToWin = 0;
        rep(buttonHoldDuration, raceTime) {
            ll speed = buttonHoldDuration;  
            ll cruiseTime = raceTime - buttonHoldDuration;
            ll dist = speed * cruiseTime;
            if (dist > record)
                waysToWin++;
        }
        res *= waysToWin;
    }

    ofstream fp_out("output_1.txt", ios::out);
    fp_out << res << endl;
    fp_out.close();

    return 0;
}