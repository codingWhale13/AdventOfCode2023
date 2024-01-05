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

const ll AREA_MIN = 200000000000000;
const ll AREA_MAX = 400000000000000;

struct Point {
    ll x, y, z;
};

// given line between points p1 and p2, find m and b in linear equation y=mx+b
pair<double, double> getMB(Point p1, Point p2) {
    double m = (double)(p2.y - p1.y) / (p2.x - p1.x);
    double b = p1.y - m * p1.x;

    return {m, b};
}

bool intersectInTestArea(pair<Point, Point> &stone1, pair<Point, Point> &stone2) {
    Point stone1Point1 = stone1.first;
    Point stone1Point2 = {
        stone1.first.x + stone1.second.x * 1000,
        stone1.first.y + stone1.second.y * 1000,
        stone1.first.z + stone1.second.z * 1000,
    };
    Point stone2Point1 = stone2.first;
    Point stone2Point2 = {
        stone2.first.x + stone2.second.x * 1000,
        stone2.first.y + stone2.second.y * 1000,
        stone2.first.z + stone2.second.z * 1000,
    };
    pair<double, double> mb1 = getMB(stone1Point1, stone1Point2), mb2 = getMB(stone2Point1, stone2Point2);
    double m1 = mb1.first,
           b1 = mb1.second,
           m2 = mb2.first,
           b2 = mb2.second;

    if (m1 == m2)
        return false;

    double intersectionX = (b2 - b1) / (m1 - m2);
    double intersectionY = m1 * intersectionX + b1;

    if (min(intersectionX, intersectionY) < AREA_MIN ||
        max(intersectionX, intersectionY) > AREA_MAX)
        return false; // not in test area

    if ((intersectionX > stone1Point1.x) != (stone1.second.x > 0) ||
        (intersectionY > stone1Point1.y) != (stone1.second.y > 0) ||
        (intersectionX > stone2Point1.x) != (stone2.second.x > 0) ||
        (intersectionY > stone2Point1.y) != (stone2.second.y > 0))
        return false; // collision is in the past

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    ifstream fp_in("input.txt", ios::in);
    string s, valueStr;
    vector<pair<Point, Point>> hailstones;
    while (getline(fp_in, s)) {
        istringstream iss(s);
        getline(iss, valueStr, ',');
        ll x1 = stoll(valueStr);
        getline(iss, valueStr, ',');
        ll y1 = stoll(valueStr);
        getline(iss, valueStr, '@');
        ll z1 = stoll(valueStr);
        getline(iss, valueStr, ',');
        ll vx = stoll(valueStr);
        getline(iss, valueStr, ',');
        ll vy = stoll(valueStr);
        getline(iss, valueStr);
        ll vz = stoll(valueStr);

        Point p = {x1, y1, z1}, v = {vx, vy, vz};
        hailstones.push_back({p, v});
    }
    fp_in.close();

    ll res = 0;
    rep(i, sz(hailstones))
        reps(j, i + 1, sz(hailstones))
            res += intersectInTestArea(hailstones[i], hailstones[j]);

    ofstream fp_out("output_1.txt", ios::out);
    fp_out << res << endl;
    fp_out.close();

    return 0;
}
