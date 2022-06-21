#include <bits/stdc++.h>
#include "Graph.h"

using namespace std;

#define ld long double

void check_if_already_eliminated(vector<int> &teams, vector<int> &wins, int ma, int tot_teams) {
    int idx = max_element(wins.begin(), wins.end()) - wins.begin();
    if (wins[idx] > ma) {
        // current team is already eliminated
        // no need to check min-cut
        teams.push_back(idx);
    }
}

void deduce_reasons(vector<int> &teams, vector<int> &wins, vector<vector<int> > &games, vector<string> &team_names) {
    int n = teams.size();
    int games_won = 0;
    for (int i = 0; i < n; i++) games_won += wins[teams[i]];

    cout << team_names[teams[0]];
    for (int i = 1; i < n-1; i++) cout << ", " << team_names[teams[i]];
    if (n > 1) cout << " and " << team_names[teams[n-1]] << " have ";
    else cout << " has ";
    cout << "won a total of " << games_won << " games.\n";

    int each_other = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            each_other += games[teams[i]][teams[j]];
        }
    }
    cout << "They play each other " << each_other << " times.\n";

    ld num = games_won + each_other;
    ld den = n;
    ld avg = num/n;

    cout << "So on average, each of the teams in this group wins ";
    cout << games_won+each_other << '/' << n << " = " << avg << " games.\n";
}

int main() {
//    freopen("input.txt", "r", stdin); // input from a given text file

    int n;
    cin >> n;

    vector<string> team_names(n);
    vector<int> wins(n), rems(n);
    vector<vector<int> > games(n, vector<int> (n));

    for (int i = 0; i < n; i++) {
        cin >> team_names[i];
        int foo;
        cin >> wins[i] >> foo >> rems[i];
        for (int j = 0; j < n; j++) cin >> games[i][j];
    }

    cerr << '\n';
    for (int i = 0; i < n; i++) {
        Graph G(n, games, i, wins, rems);
        int safe = G.check_saturation();
        if (!safe) {
            cout << team_names[i] << " is eliminated.\n";

            // find the teams responsible for elimination
            vector<int> teams;

            check_if_already_eliminated(teams, wins, wins[i]+rems[i], n);
            if (teams.size() == 0) G.find_eliminating_teams(teams, n);
            assert(teams.size() > 0);

            cout << "They can win at most " << wins[i] << " + " << rems[i] << " = " << wins[i]+rems[i] << " games.\n";
            deduce_reasons(teams, wins, games, team_names);
            cout << '\n';
        }
    }

    return 0;
}

/*
4
Atlanta 83 71 8 0 1 6 1
Philadelphia 80 79 3 1 0 0 2
New_York 78 78 6 6 0 0 0
Montreal 77 82 3 1 2 0 0

-->
Philadelphia is eliminated.
They can win at most 80 + 3 = 83 games.
Atlanta and New York have won a total of 161 games.
They play each other 6 times.
So on average, each of the teams wins 167/2 = 83.5 games.

Montreal is eliminated.
They can win at most 77 + 3 = 80 games.
Atlanta has won a total of 83 games.
They play each other 0 times.
So on average, each of the teams in this group wins 83/1 = 83 games.
*/
