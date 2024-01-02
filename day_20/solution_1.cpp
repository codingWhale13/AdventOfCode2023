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

ll totalLowPulses = 0, totalHighPulses = 0;

void simulateButtonPress(map<string, vector<string>> &network,
                         map<string, bool> &flipFlopStates,
                         map<string, map<string, bool>> &conjunctionStates) {
    deque<vector<string>> todo; // format: {trigger, module, "false"=low or "true"=high pulse}

    totalLowPulses++; // button press
    // broadcast low pulse to initial modules
    repAll(initialModule, network["start"]) {
        todo.push_back({"start", initialModule, "false"});
        totalLowPulses++;
    }

    while (!todo.empty()) {
        string trigger = todo.front()[0];
        string module = todo.front()[1];
        bool inPulse = todo.front()[2] == "true";
        todo.pop_front();

        bool outPulse;
        if (flipFlopStates.find(module) != flipFlopStates.end()) {
            // handle flip flop module
            if (!inPulse) {
                flipFlopStates[module] = !flipFlopStates[module];
                outPulse = flipFlopStates[module];
            } else
                continue; // high pulse has no effect
        } else {
            // handle conjunction module
            conjunctionStates[module][trigger] = inPulse;
            bool allInputsOn = true;
            repAll(inp, conjunctionStates[module]) {
                if (!inp.second) {
                    allInputsOn = false;
                    break;
                }
            }
            outPulse = !allInputsOn;
        }

        string outPulseStr = outPulse ? "true" : "false";
        repAll(neighbor, network[module]) {
            todo.push_back({module, neighbor, outPulseStr});
            if (outPulse)
                totalHighPulses++;
            else
                totalLowPulses++;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    map<string, vector<string>> network;
    map<string, bool> flipFlopStates;
    map<string, map<string, bool>> conjunctionStates;

    ifstream fp_in("input.txt", ios::in);
    string s, output, trash;
    char space;
    while (getline(fp_in, s)) {
        istringstream iss(s);
        getline(iss, trash, '>');
        iss.get(space);
        vector<string> outputs;
        while (getline(iss, output, ',')) {
            iss.get(space);
            outputs.push_back(output);
        }

        if (s[0] == 'b') { // broadcaster
            network["start"] = outputs;
        } else {
            string module = s.substr(1, 2);
            network[module] = outputs;
            if (s[0] == '%')
                flipFlopStates[module] = 0;
            else if (s[0] == '&')
                conjunctionStates[module] = {};
        }
    }

    repAll(item, network) {
        string from = item.first;
        vector<string> to = item.second;
        repAll(t, to) {
            if (conjunctionStates.find(t) != conjunctionStates.end())
                conjunctionStates[t][from] = false;
        }
    }

    rep(iter, 1000)
        simulateButtonPress(network, flipFlopStates, conjunctionStates);

    ll res = totalLowPulses * totalHighPulses;
    
    ofstream fp_out("output_1.txt", ios::out);
    fp_out << res << endl;
    fp_out.close();

    return 0;
}