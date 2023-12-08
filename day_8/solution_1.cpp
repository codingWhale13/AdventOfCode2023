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
    string nav, start, left, right;
    fp_in >> nav;

    map<string, pair<string, string>> network;
    while (fp_in >> start) {
        fp_in >> left >> left >> right;
        left = left.substr(1, 3);
        right = right.substr(0, 3);

        network[start] = {left, right};
    }

    ll res = 0, navIdx = 0;
    string cur = "AAA", target = "ZZZ";
    while (cur != target) {
        res++;
        if (nav[navIdx] == 'L')
            cur = network[cur].first;
        else
            cur = network[cur].second;
        navIdx = (navIdx + 1) % ln(nav);
    }

    ofstream fp_out("output_1.txt", ios::out);
    fp_out << res << endl;
    fp_out.close();

    return 0;
}