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

    string s, raceTimeStr, recordStr;
    istringstream issTimes(timesStr), issRecords(recordsStr);
    issTimes >> s;
    while (issTimes >> s)
        raceTimeStr += s;
    issRecords >> s;
    while (issRecords >> s)
        recordStr += s;

    ll raceTime = stoll(raceTimeStr);
    ll record = stoll(recordStr);

    ll waysToWin = 0;
    rep(buttonHoldDuration, raceTime) {
        ll speed = buttonHoldDuration;
        ll cruiseTime = raceTime - buttonHoldDuration;
        ll dist = speed * cruiseTime;
        if (dist > record)
            waysToWin++;
    }

    ofstream fp_out("output_2.txt", ios::out);
    fp_out << waysToWin << endl;
    fp_out.close();

    return 0;
}