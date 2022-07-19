#include <bits/stdc++.h>
#include "Graph.h"

using namespace std;

int main() {
    freopen("heap1.txt", "r", stdin); // input from a given text file

    int n, m;
    cin >> n >> m;
    Graph G(n, m);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        G.add_weighted_edge(u, v, w);
        G.add_weighted_edge(v, u, w);
    }

    freopen("heap2.txt", "r", stdin); // input from a given text file
    freopen("heap_output.txt", "w", stdout); // output to a new text file

    int k;
    cin >> k;
    while (k--) {
        int src, des;
        cin >> src >> des;

        chrono::steady_clock::time_point begin = chrono::steady_clock::now();
        chrono::steady_clock::time_point end = chrono::steady_clock::now();

//        cout << "Time difference = " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
//        cout << "Time difference = " << chrono::duration_cast<chrono::nanoseconds> (end - begin).count() << "[ns]";

        pair<int, int> bin_heap;
        pair<int, int> fib_heap;

        chrono::steady_clock::time_point bin_heap_begin = chrono::steady_clock::now();
        bin_heap = G.dijkstra_bin_heap(src, des);
        chrono::steady_clock::time_point bin_heap_end = chrono::steady_clock::now();


        chrono::steady_clock::time_point fib_heap_begin = chrono::steady_clock::now();
        fib_heap = G.dijkstra_fib_heap(src, des);
        chrono::steady_clock::time_point fib_heap_end = chrono::steady_clock::now();

        if (bin_heap.first != fib_heap.first || bin_heap.second != fib_heap.second) {
            cout << "ERROR!\n";
            continue;
        }

        int cost = fib_heap.first, path_len = fib_heap.second;

        if (cost == -1) {
            cout << des << " is unreachable from " << src << '\n';
        }
        else {
            cout << path_len << ' ' << cost << ' ' <<
            chrono::duration_cast<chrono::microseconds> (bin_heap_end - bin_heap_begin).count() << ' ' <<
            chrono::duration_cast<chrono::microseconds> (fib_heap_end - fib_heap_begin).count() << '\n';
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

9 17
0 7 60
7 1 -150
4 8 -70
6 4 80
5 1 4000
8 0 100000
2 3 -200
8 2 1000
0 3 300
3 8 50000
3 7 -200
2 5 120
6 3 1500
4 0 90
5 7 -50
1 6 100
4 1 -90
0 5

-->
The graph does not contain a negative cycle
Shortest path cost: 1140
0 -> 7 -> 1 -> 6 -> 4 -> 8 -> 2 -> 5

4 4
0 1 1
1 2 -1
2 3 -1
3 0 -1
0 3

-->
The graph contains a negative cycle
*/
