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

struct Rule {
    char category, inequality;
    ll threshold;
    string onSuccess;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    ifstream fp_in("input.txt", ios::in);

    map<string, vector<Rule>> instructions;
    string s;
    while (getline(fp_in, s)) {
        if (ln(s) == 0)
            break; // end of instructions

        istringstream iss(s);

        string partName, thresholdStr, onSuccess;
        char trash, category, inequality, nextChar;

        getline(iss, partName, '{');
        vector<Rule> rules;
        while (true) {
            iss >> category >> nextChar;

            if (nextChar != '<' && nextChar != '>') {
                string restOfString;
                getline(iss, restOfString);
                string terminalState = string(1, category) + string(1, nextChar) + restOfString;
                terminalState = terminalState.substr(0, ln(terminalState) - 1); // remove '}' at end
                rules.push_back({'?', '?', -1LL, terminalState});
                break;
            } else {
                inequality = nextChar;
                getline(iss, thresholdStr, ':');
                ll threshold = stoll(thresholdStr);
                getline(iss, onSuccess, ',');
                rules.push_back({category, inequality, threshold, onSuccess});
            }
        }
        instructions[partName] = rules;
    }

    ll res = 0;
    while (getline(fp_in, s)) {
        istringstream iss(s);
        char trash, category;
        map<char, ll> rating;
        iss >> trash;
        ll value;
        rep(i, 4) {
            iss >> category >> trash >> value >> trash;
            rating[category] = value;
        }

        string workflow = "in";
        while (workflow != "R" && workflow != "A") {
            repAll(rule, instructions[workflow]) {
                bool success = rule.inequality == '?' ||
                               rule.inequality == '>' && rating[rule.category] > rule.threshold ||
                               rule.inequality == '<' && rating[rule.category] < rule.threshold;
                if (success) {
                    workflow = rule.onSuccess;
                    break;
                }
            }
        }

        if (workflow == "A")
            res += rating['x'] + rating['m'] + rating['a'] + rating['s'];
    }

    ofstream fp_out("output_1.txt", ios::out);
    fp_out << res << endl;
    fp_out.close();

    return 0;
}