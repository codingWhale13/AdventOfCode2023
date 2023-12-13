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

ll getMirrorIndex(vector<string> &strings) {
    reps(mirrorIndex, 1, sz(strings)) {
        ll i = mirrorIndex - 1, j = mirrorIndex;
        bool isMirror = true;
        while (i > -1 && j < sz(strings)) {
            if (strings[i] != strings[j]) {
                isMirror = false;
                break;
            }
            i--;
            j++;
        }
        if (isMirror)
            return mirrorIndex;
    }

    return -1; // no mirror found
}

void analyzePattern(vector<string> &rows, ll &res) {
    ll mirrorIndex = getMirrorIndex(rows);
    if (mirrorIndex != -1)
        res += mirrorIndex * 100;
    else {

        vector<string> cols(ln(rows[0]));
        repAll(row, rows)
            rep(j, ln(row))
                cols[j] += row[j];
        res += getMirrorIndex(cols);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    ifstream fp_in("input.txt", ios::in);
    ll res = 0;
    string row;
    vector<string> rows;
    while (getline(fp_in, row)) {
        if (ln(row) > 0) {
            rows.push_back(row);
        } else {
            analyzePattern(rows, res);
            rows.clear();
        }
    }
    analyzePattern(rows, res);
    fp_in.close();

    ofstream fp_out("output_1.txt", ios::out);
    fp_out << res << endl;
    fp_out.close();

    return 0;
}