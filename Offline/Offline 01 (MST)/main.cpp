#include <bits/stdc++.h>
#include "Graph.h"

using namespace std;

#define ld long double

const ld eps = 1e-8;

void print_edge(pair<int, int> &e) {
    cout << '(' << e.first << ',' << e.second << ')';
}

void print_edge_list(vector<pair<int, int> > &edges, int n) {
    cout << '{';
    print_edge(edges[0]);
    for (int i = 1; i < n-1; i++) {
        cout << ',';
        print_edge(edges[i]);
    }
    cout << "}\n";
}

int main() {
    int n, m;
    cin >> n >> m;
    Graph G(n, m);
    for (int i = 0; i < m; i++) {
        int u, v;
        ld w;
        cin >> u >> v >> w;
        G.add_weighted_edge(u, v, w);
    }

    vector<pair<int, int> > taken_edges_Kruskal, taken_edges_Prim;
    ld mst_Prim = G.find_MST_Prim(taken_edges_Prim);
    ld mst_Kruskal = G.find_MST_Kruskal(taken_edges_Kruskal);

    assert(abs(mst_Prim - mst_Kruskal) < eps); // the mst's are equal
    if (abs(mst_Prim - (-1.0)) < eps) {
        // impossible to construct MST
        // given graph is a forest
        cout << "Impossible\n";
        return 1;
    }

    assert(taken_edges_Prim.size() == n-1);
    assert(taken_edges_Kruskal.size() == n-1);

    cout << "Cost of the minimum spanning tree : " << mst_Prim << '\n';

    cout << "List of edges selected by Prim\'s:";
    print_edge_list(taken_edges_Prim, n);

    cout << "List of edges selected by Kruskal\'s:";
    print_edge_list(taken_edges_Kruskal, n);

    return 0;
}

/*
6 9
0 1 1.0
1 3 5.0
3 0 3.0
3 4 1.0
1 4 1.0
1 2 6.0
5 2 2.0
2 4 4.0
5 4 4.0

--> 9.0

3 2
0 1 3.0
1 2 4.0

--> 7.0

7 14
0 2 21
0 1 14
1 2 15
0 5 7
5 1 2
1 6 19
5 6 18
6 2 3
5 3 13
5 4 15
6 4 2
0 3 5
2 4 4
3 4 22

--> 34

4 6
0 1 2.5
1 2 3.14
3 2 2.78
0 3 9.8
2 0 6.626
3 1 1.6

--> 6.88

*/
