#include <bits/stdc++.h>
#include "Graph.h"

using namespace std;

void print_path(vector<int> &path) {
    int n = path.size();
    assert(n);
    cout << path[0];
    for (int i = 1; i < n; i++) cout << " -> " << path[i];
    cout << '\n';
}

int main() {
//    freopen("input.txt", "r", stdin); // input from a given text file

    int n, m;
    cin >> n >> m;
    Graph G(n, m);
    bool negEdge = 0;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        if (!negEdge && w < 0) negEdge = 1;
        G.add_weighted_edge(u, v, w);
    }
    int src, des;
    cin >> src >> des;

    if (!negEdge) {
        // dijkstra
        vector<int> path;
        int cost = G.dijkstra(src, des, path);
        if (cost == -1) {
            cout << des << " is unreachable from " << src << '\n';
        }
        else {
            cout << "Shortest path cost: " << cost << '\n';
            print_path(path);
        }
    }

    return 0;
}

/*
9 17
0 7 60
7 1 150
4 8 70
6 4 80
5 1 4000
8 0 100000
2 3 200
8 2 1000
0 3 300
3 8 50000
3 7 200
2 5 120
6 3 1500
4 0 90
5 7 50
1 6 100
4 1 90
0 5

-->
Shortest path cost: 1580
0 -> 7 -> 1 -> 6 -> 4 -> 8 -> 2 -> 5
*/
