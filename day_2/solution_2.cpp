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
        ll r = 0, g = 0, b = 0;
        while (true) {
            getline(iss, sub, ' ');
            ll count = stoll(sub);
            while (true) {
                getline(iss, sub, ' ');
                if (sub[0] == 'r')
                    r = max(r, count);
                else if (sub[0] == 'g')
                    g = max(g, count);
                else if (sub[0] == 'b')
                    b = max(b, count);
                if (sub[ln(sub) - 1] == ';' || sub[ln(sub) - 1] != ',')
                    break;
                getline(iss, sub, ' ');
                count = stoll(sub);
            }
            if (sub[ln(sub) - 1] != ';')
                break; // EOL
        }

        res += r * g * b;
    }

    fp_in.close();
    ofstream fp_out("output_2.txt", ios::out);
    fp_out << res << endl;
    fp_out.close();

    return 0;
}