#include <bits/stdc++.h>
#include "Graph.h"

using namespace std;

void print_matrix(vector<vector<int> > &dis, int n) {
    cout << "Shortest distance matrix\n";
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (dis[i][j] == INF) cout << "INF ";
            else cout << dis[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}

int main() {
//    freopen("input.txt", "r", stdin); // input from a given text file

    int n, m;
    cin >> n >> m;
    Graph G(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        G.add_weighted_edge(u, v, w);
    }

    vector<vector<int> > dis_mat_mul_slow, dis_mat_mul_fast, dis_floyd;
    G.matrixMultiplicationSlow(dis_mat_mul_slow);
    G.matrixMultiplicationFast(dis_mat_mul_fast);
    G.floydWarshall(dis_floyd);

    cout << "Using Matrix Multiplication:\n";
    print_matrix(dis_mat_mul_slow, n);

    cout << "Using Matrix Multiplication with Repeated Squaring:\n";
    print_matrix(dis_mat_mul_fast, n);

    cout << "Using Floyd-Warshall Algorithm\n";
    print_matrix(dis_floyd, n);

    return 0;
}

/*
4 6
1 2 8
1 4 1
2 3 1
3 1 4
4 2 2
4 3 9

-->
Shortest distance matrix
0 3 4 1
5 0 1 6
4 7 0 5
7 2 3 0

4 4
1 2 5
2 3 3
3 4 1
1 4 10

-->
Shortest distance matrix
0 5 8 9
INF 0 3 4
INF INF 0 1
INF INF INF 0
*/
