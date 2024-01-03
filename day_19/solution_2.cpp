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

ll countAcceptances(map<char, pair<ll, ll>> &ratingRange, string workflow, ll localRuleId, map<string, vector<Rule>> &instructions) {
    if (workflow == "A") {
        ll acceptanceCount = 1;
        repAll(item, ratingRange)
            acceptanceCount *= item.second.second - item.second.first + 1;
        return acceptanceCount;
    } else if (workflow == "R" || localRuleId >= sz(instructions[workflow])) {
        return 0;
    } else if (instructions[workflow][localRuleId].inequality == '?') {
        return countAcceptances(ratingRange, instructions[workflow][localRuleId].onSuccess, 0, instructions);
    }

    ll acceptanceCount = 0;
    Rule rule = instructions[workflow][localRuleId];

    // split ranges
    map<char, pair<ll, ll>> rangeLower = ratingRange, rangeUpper = ratingRange; // copy original range
    rangeLower[rule.category].second = rule.inequality == '<' ? rule.threshold - 1 : rule.threshold;
    rangeUpper[rule.category].first = rule.inequality == '<' ? rule.threshold : rule.threshold + 1;

    // recursive calls
    if (rangeLower[rule.category].second >= rangeLower[rule.category].first) {
        string newWorkflow = rule.inequality == '<' ? rule.onSuccess : workflow;
        ll newLocalRuleId = rule.inequality == '<' ? 0 : localRuleId + 1;
        acceptanceCount += countAcceptances(rangeLower, newWorkflow, newLocalRuleId, instructions);
    }
    if (rangeUpper[rule.category].second >= rangeUpper[rule.category].first) {
        string newWorkflow = rule.inequality == '>' ? rule.onSuccess : workflow;
        ll newLocalRuleId = rule.inequality == '>' ? 0 : localRuleId + 1;
        acceptanceCount += countAcceptances(rangeUpper, newWorkflow, newLocalRuleId, instructions);
    }

    return acceptanceCount;
}

int main() {
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

    map<char, pair<ll, ll>> initialRange = {{'x', {1, 4000}}, {'m', {1, 4000}}, {'a', {1, 4000}}, {'s', {1, 4000}}};
    ll res = countAcceptances(initialRange, "in", 0, instructions);

    ofstream fp_out("output_2.txt", ios::out);
    fp_out << res << endl;
    fp_out.close();

    return 0;
}