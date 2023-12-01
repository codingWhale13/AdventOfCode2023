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

    vector<string> digitsSpelledOut = {
        "zeroEvenThoughItDoesntOccurInInput",
        "one",
        "two",
        "three",
        "four",
        "five",
        "six",
        "seven",
        "eight",
        "nine",
    };

    ifstream fp_in("input.txt", ios::in);

    string s;
    ll res = 0;
    while (fp_in >> s) {
        ll first, last;
        bool digitSeen = false;
        rep(idx, s.length()) {
            char c = s[idx];
            ll digit = -1;
            if ('0' <= c && c <= '9') {
                digit = c - '0';
            }

            if (digit == -1) {
                rep(i, 10) {
                    ll l = digitsSpelledOut[i].length();
                    if (idx + l <= s.length() && s.substr(idx, l) == digitsSpelledOut[i]) {
                        digit = i;
                        break;
                    }
                }
            }

            if (digit != -1) {
                if (!digitSeen) {
                    digitSeen = true;
                    first = digit;
                }
                last = digit;
            }
        }

        res += first * 10 + last;
        cout << first << " " << last << endl;
    }

    fp_in.close();
    ofstream fp_out("output_2.txt", ios::out);
    fp_out << res << endl;
    fp_out.close();

    return 0;
}