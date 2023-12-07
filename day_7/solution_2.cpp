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

    string labels = "J23456789TQKA"; // weak to strong (now, J is joker)
    ll numLabels = ln(labels);

    ifstream fp_in("input.txt", ios::in);
    string card;
    ll bid;
    vector<pair<pair<ll, vector<ll>>, ll>> cards; // {{type (high is good), card representation}, bid}
    while (fp_in >> card) {
        fp_in >> bid;

        vector<ll> cardInNumbers;
        repAll(ch, card)
            cardInNumbers.push_back(labels.find(ch));

        vector<ll> labelAmounts(numLabels, 0);
        repAll(label, cardInNumbers)
            labelAmounts[label]++;
        ll jokerAmounts = labelAmounts[0];
        labelAmounts[0] = 0; // take jokers out of the equation

        vector<ll> cardSimplified;
        repAll(val, labelAmounts) {
            if (val != 0)
                cardSimplified.push_back(val);
        }
        sort(cardSimplified.begin(), cardSimplified.end());

        ll cardType; // will be 1-7
        vector<vector<ll>> possibleCardTypes = {{5}, {1, 4}, {2, 3}, {1, 1, 3}, {1, 2, 2}, {1, 1, 1, 2}, {1, 1, 1, 1, 1}};
        rep(i, sz(possibleCardTypes)) {
            vector<ll> possibleMatch = possibleCardTypes[i];
            if (sz(cardSimplified) > sz(possibleMatch))
                continue; // no way to make up for this with jokers

            bool typeMatches = sz(cardSimplified) < sz(possibleMatch);
            if (!typeMatches) {
                typeMatches = true;
                rep(j, sz(cardSimplified)) {
                    if (cardSimplified[j] > possibleMatch[j])
                        typeMatches = false;
                }
            }
            if (typeMatches) {
                cardType = sz(possibleCardTypes) - i; // because we're looking at card types in decreasing order
                break;                                // jokers optimally used, don't look any further
            }
        }

        cards.push_back({{cardType, cardInNumbers}, bid});
    }
    sort(cards.begin(), cards.end());

    ll res = 0;
    ll rank = 1;
    repAll(card, cards)
        res += card.second * rank++;

    ofstream fp_out("output_2.txt", ios::out);
    fp_out << res << endl;
    fp_out.close();

    return 0;
}