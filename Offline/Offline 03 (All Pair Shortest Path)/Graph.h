#include<bits/stdc++.h>

using namespace std;

const int INF = 1<<30;

class Graph {
    int n; // no. of vertices
    vector<vector<int> > adj; // adjacency matrix of all vertices

public:
    // n is the no. of vertices, m being the no. of edges
    Graph(int n) { // O(V+E)
        this->n = n;
        adj.resize(n+1, vector<int> (n+1, INF));

        for (int i = 1; i <= n; i++) adj[i][i] = 0;
    }

    void add_weighted_edge(int u, int v, int cost) { // O(1)
        adj[u][v] = cost; // directed edge
    }


    void matrixMultiplicationSlow(vector<vector<int> > &dis) {
        dis = adj;

        for (int m = 2; m < n; m++) {
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    for (int k = 1; k <= n; k++) {
                        if (dis[i][k] == INF) continue; // k is unreachable from i
                        // check if j should be visited from i via k
                        if (dis[i][k] + adj[k][j] < dis[i][j]) {
                            dis[i][j] = dis[i][k] + adj[k][j];
                        }
                    }
                }
            }
        }
    }

    // using repeated squaring method
    void matrixMultiplicationFast(vector<vector<int> > &dis) {
        dis = adj;

        for (int m = 2; ; m *= 2) {
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    for (int k = 1; k <= n; k++) {
                        if (dis[i][k] == INF) continue; // k is unreachable from i
                        // check if j should be visited from i via k
                        if (dis[i][k] + dis[k][j] < dis[i][j]) {
                            dis[i][j] = dis[i][k] + dis[k][j];
                        }
                    }
                }
            }
            if (m >= n) break;
        }
    }

    void floydWarshall(vector<vector<int> > &dis) {
        dis = adj;

        for (int k = 1; k <= n; k++) {
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    if (dis[i][k] == INF) continue;
                    if (dis[i][k] + dis[k][j] < dis[i][j]) {
                        dis[i][j] = dis[i][k] + dis[k][j];
                    }
                }
            }
        }
    }
};

