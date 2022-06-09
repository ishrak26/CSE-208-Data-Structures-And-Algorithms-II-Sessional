#include <bits/stdc++.h>
#include "Graph.h"

using namespace std;

int main() {
//    freopen("input.txt", "r", stdin); // input from a given text file

    int n, m;
    cin >> n >> m;
    Graph G(n, m);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        G.add_weighted_edge(u, v, w);
        G.add_weighted_edge(v, u, w);
    }
    int src;
    cin >> src;

    vector<int> best(n);
    G.dijkstra(src, best);

    for (int i = 0; i < n; i++) cout << best[i] << '\n';

    return 0;
}

/*
7 10
0 1 2
0 3 4
0 2 2
1 3 2
2 3 2
3 5 1
3 6 3
3 4 1
5 6 1
4 6 1
0

-->
0
1
1
1
2
2
3

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
0

-->
0
2
3
2
1
2
2
1
2

4 3
0 1 1
1 2 1
2 3 1
1

-->
1
0
1
2
*/
