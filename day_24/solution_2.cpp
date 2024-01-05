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

/*
EXPLANATION, inspired by: https://www.reddit.com/r/adventofcode/comments/18q40he/2023_day_24_part_2_a_straightforward_nonsolver

We are given hailstones moving from position x_i, y_i, z_i with velocity vx_i, vy_i, vz_i (with i being the hailstone's ID).
We are interested in throwing a stone from position X, Y, Z with velocity VX, VY, VZ.
Let's set up a system of linear equations that we can solve to arrive at X, Y, Z.

We know, for some amount of steps t and some hailstone with ID i.
X + t * VX = x_i + t * vx_i
=> t = (x_i - X) / (VX - vx_i)

We can do the same for the y and z coordinate.
Let's do it for y and set the right hand sides equal to each other:
(x_i - X) / (VX - vx_i) = (y_i - Y) / (VY - vy_i)
=> (x_i - X) * (VY - vy_i) = (y_i - Y) * (VX - vx_i)
=> x_i * VY - x_i * vy_i - X * VY + X * vy_i = y_i * VX - y_i * vx_i - Y * VX + Y * vx_i
=> Y * VX - X * VY = y_i * VX - X * vy_i + Y * vx_i - x_i * VY + x_i * vy_i - y_i * vx_i

Because the left hand side is now independent of the hailstone ID, we get the following equality for hailstone with ID j != i:
y_i * VX - X * vy_i + Y * vx_i - x_i * VY + x_i * vy_i - y_i * vx_i = y_j * VX - X * vy_j + Y * vx_j - x_j * VY + x_j * vy_j - y_j * vx_j
=> (vy_j - vy_i) * X + (y_i - y_j) * VX + (vx_i - vx_j) Y + (x_j - x_i) * VY = x_j * vy_j - x_i * vy_i + y_i * vx_i - y_j * vx_j

Now, we have a linear equation with four unknowns: X, VX, Y, VY.
Each equation requires information about two hailstones, so we can calculate the unknowns with data from any 5 hailstones.

In a similar way, we can find out Z and VZ.

##########################################################################################################################################

NOTE: Due to precision errors, the code doesn't quite  produce the correct result for the large test case.
My code gives
711031616314992 whereas the correct answer (checked with correct code from the community) is
711031616315001.
*/

vector<vector<double>> createMatrix(vector<pair<Point, Point>> &hailstones) {
    vector<vector<double>> m(4, vector<double>(5)); // four variables & value of right hand side+

    rep(i, 4) {
        ll x_i = hailstones[i].first.x;
        ll y_i = hailstones[i].first.y;
        ll z_i = hailstones[i].first.z;
        ll vx_i = hailstones[i].second.x;
        ll vy_i = hailstones[i].second.y;
        ll vz_i = hailstones[i].second.z;
        ll x_j = hailstones[i + 1].first.x;
        ll y_j = hailstones[i + 1].first.y;
        ll z_j = hailstones[i + 1].first.z;
        ll vx_j = hailstones[i + 1].second.x;
        ll vy_j = hailstones[i + 1].second.y;
        ll vz_j = hailstones[i + 1].second.z;
        m[i] = {vy_j - vy_i, y_i - y_j, vx_i - vx_j, x_j - x_i, x_j * vy_j - x_i * vy_i + y_i * vx_i - y_j * vx_j};
    }

    return m;
}

// this function is powered by ChatGPT

using namespace std;

// Perform Gauss-Jordan elimination on the augmented matrix
void gaussJordanElimination(vector<vector<double>> &matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    for (int i = 0; i < rows; ++i) {
        // Make the diagonal element 1
        double divisor = matrix[i][i];
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] /= divisor;
        }

        // Eliminate other rows
        for (int k = 0; k < rows; ++k) {
            if (k != i) {
                double factor = matrix[k][i];
                for (int j = 0; j < cols; ++j) {
                    matrix[k][j] -= factor * matrix[i][j];
                }
            }
        }
    }
}

// Print the solution from the augmented matrix
void printSolution(const vector<vector<double>> &matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    cout << "Solution:" << endl;
    for (int i = 0; i < rows; ++i) {
        cout << "x" << i + 1 << " = " << matrix[i][cols - 1] << endl;
    }
}

void bringZDimensionForward(vector<pair<Point, Point>> &hailstones) {
    rep(i, sz(hailstones)) {
        hailstones[i].first = {hailstones[i].first.z, hailstones[i].first.x, hailstones[i].first.z};
        hailstones[i].second = {hailstones[i].second.z, hailstones[i].second.x, hailstones[i].second.z};
    }
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
        ll x = stoll(valueStr);
        getline(iss, valueStr, ',');
        ll y = stoll(valueStr);
        getline(iss, valueStr, '@');
        ll z = stoll(valueStr);
        getline(iss, valueStr, ',');
        ll vx = stoll(valueStr);
        getline(iss, valueStr, ',');
        ll vy = stoll(valueStr);
        getline(iss, valueStr);
        ll vz = stoll(valueStr);

        Point p = {x, y, z}, v = {vx, vy, vz};
        hailstones.push_back({p, v});
    }
    fp_in.close();

    vector<vector<double>> m = createMatrix(hailstones);
    gaussJordanElimination(m);

    bringZDimensionForward(hailstones);
    printSolution(m);
    ll X = m[0][4];
    ll Y = m[2][4];

    m = createMatrix(hailstones);
    gaussJordanElimination(m);
    printSolution(m);
    ll Z = m[0][4];

    ll res = X + Y + Z;

    ofstream fp_out("output_2.txt", ios::out);
    fp_out << res << endl;
    fp_out.close();

    return 0;
}
