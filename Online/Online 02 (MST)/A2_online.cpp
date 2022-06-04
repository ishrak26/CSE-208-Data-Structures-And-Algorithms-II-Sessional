#include <bits/stdc++.h>
#include "Graph.h"

using namespace std;

#define ld long double

const ld eps = 1e-8;

void print_edge(pair<int, int> &e) {
    cout << '(' << e.first << ',' << e.second << ")\n";
}

void print_edge_list(vector<pair<int, int> > &edges, int n) {
    cout << "Edges in MST\n";
    for (int i = 0; i < n-1; i++) {
        print_edge(edges[i]);
    }
}

int main() {
//    freopen("mst_in.txt", "r", stdin); // input from a given text file

    int n, m;
    cin >> n >> m;
    Graph G(n, m);
    for (int i = 0; i < m; i++) {
        int u, v;
        ld w;
        cin >> u >> v >> w;
        G.add_weighted_edge(u, v, w);
    }

    vector<pair<int, int> > taken_edges;
    ld mst = G.find_MST_reverse_deletion(taken_edges);

    if (abs(mst - (-1.0)) < eps) {
        // impossible to construct MST
        // given graph is a forest
        cout << "Impossible\n";
        return 1;
    }

    assert(taken_edges.size() == n-1);

    print_edge_list(taken_edges, n);
    cout << "Total weight of MST is " << mst << '\n';

    return 0;
}

/*
9 14
0 1 4
0 7 8
1 2 8
1 7 11
2 3 7
2 8 2
2 5 4
3 4 9
3 5 14
4 5 10
5 6 2
6 7 1
6 8 6
7 8 7
*/

