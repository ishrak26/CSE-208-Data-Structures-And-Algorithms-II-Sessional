#include <bits/stdc++.h>
#include "Graph.h"

using namespace std;

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
            cout << team_names[i] << " is eliminated.\n\n";
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
*/
