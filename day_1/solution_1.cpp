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

    string s;
    ll res = 0;
    while (fp_in >> s) {
        ll first, last;
        bool digitSeen = false;
        for (char c : s) {
            if ('0' <= c && c <= '9') {
                if (!digitSeen) {
                    digitSeen = true;
                    first = c - '0';
                }
                last = c - '0';
            }
        }
        res += first * 10 + last;
    }

    fp_in.close();
    ofstream fp_out("output_1.txt", ios::out);
    fp_out << res << endl;
    fp_out.close();

    return 0;
}