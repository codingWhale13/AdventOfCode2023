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

ll GRID_SIZE = 500;
map<char, pair<ll, ll>> DIRS = {
    {'R', {1, 0}},
    {'D', {0, 1}},
    {'L', {-1, 0}},
    {'U', {0, -1}},
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    ll x = 0, y = 0;
    ll boundary = 0;

    ifstream fp_in("input.txt", ios::in);
    string whatever, colorCode;
    vector<pair<ll, ll>> points = {{x, y}};
    while (fp_in >> whatever) {
        fp_in >> whatever >> colorCode;
        ll steps = stoll(colorCode.substr(2, 5), nullptr, 16);
        ll d = colorCode[7] == '0' ? 'R' : (colorCode[7] == '1' ? 'D' : (colorCode[7] == '2' ? 'L' : 'U'));
        x += DIRS[d].first * steps;
        y += DIRS[d].second * steps;
        points.push_back({x, y});
        boundary += steps;
    }

    // shoelace formula
    ll n = sz(points);
    ll area = points[n - 1].first * points[0].second - points[0].first * points[n - 1].second;
    rep(i, n - 1) {
        area += points[i].first * points[i + 1].second;
        area -= points[i + 1].first * points[i].second;
    }
    area /= 2;

    // Pick's theorem
    ll interior = area - boundary / 2 + 1;
    ll res = interior + boundary;

    ofstream fp_out("output_2.txt", ios::out);
    fp_out << res << endl;
    fp_out.close();

    return 0;
}