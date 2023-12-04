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

vector<ll> numbersStrToVector(string &s) {
    istringstream iss(s);
    vector<ll> res;
    string numStr;
    while (iss >> numStr) {
        res.push_back(stoll(numStr));
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    ifstream fp_in("input.txt", ios::in);

    string s, trash, winningNumbersStr, myNumbersStr;
    vector<ll> matchCounts;
    while (getline(fp_in, s)) {
        istringstream iss(s);
        iss >> trash; // "Card"
        iss >> trash; // "[card number]:"
        getline(iss, winningNumbersStr, '|');
        getline(iss, myNumbersStr, '|');
        vector<ll> winningNumbers = numbersStrToVector(winningNumbersStr);
        vector<ll> myNumbers = numbersStrToVector(myNumbersStr);

        ll matchCount = 0;
        repAll(num, myNumbers) {
            if (find(winningNumbers.begin(), winningNumbers.end(), num) != winningNumbers.end()) {
                matchCount++;
            }
        }
        matchCounts.push_back(matchCount);
    }

    ll n = sz(matchCounts);

    ll res = n;
    vector<ll> cardAmounts(n, 1);
    rep(i, n) {
        reps(j, i + 1, i + 1 + matchCounts[i]) {
            cardAmounts[j] += cardAmounts[i];
            res += cardAmounts[i];
        }
    }

    fp_in.close();
    ofstream fp_out("output_2.txt", ios::out);
    fp_out << res << endl;
    fp_out.close();

    return 0;
}