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
    while (getline(fp_in, s)) {
        istringstream iss(s);
        string sub;
        getline(iss, sub, ' '); // "Game"
        getline(iss, sub, ' '); // "[id]:"
        ll gameId = stoll(sub.substr(0, ln(sub) - 1));
        bool isPossible = true;
        while (true) {
            getline(iss, sub, ' ');
            ll count = stoll(sub);
            while (true) {
                getline(iss, sub, ' ');
                if (sub[0] == 'r' && count > 12)
                    isPossible = false;
                else if (sub[0] == 'g' && count > 13)
                    isPossible = false;
                else if (sub[0] == 'b' && count > 14)
                    isPossible = false;
                if (sub[ln(sub) - 1] == ';' || sub[ln(sub) - 1] != ',')
                    break;
                getline(iss, sub, ' ');
                count = stoll(sub);
            }
            if (sub[ln(sub) - 1] != ';')
                break; // EOL
        }
        if (isPossible)
            res += gameId;
    }

    fp_in.close();
    ofstream fp_out("output_1.txt", ios::out);
    fp_out << res << endl;
    fp_out.close();

    return 0;
}