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
        adj.resize(n+1, vector<int> (n+1, INF)); // vertices are 1-indexed

        for (int i = 1; i <= n; i++) adj[i][i] = 0;
    }

    void add_weighted_edge(int u, int v, int cost) { // O(1)
        adj[u][v] = cost; // directed edge
    }

    void matrixMultiplicationSlow(vector<vector<int> > &dis) { // O(V^4)
        dis = adj; // first iteration done

        for (int m = 2; m < n; m++) { // there will be at most n-1 edges for any simple path
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    for (int k = 1; k <= n; k++) {
                        if (dis[i][k] == INF || adj[k][j] == INF) continue; // k is unreachable so far from i, will help for negative weights

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
    void matrixMultiplicationFast(vector<vector<int> > &dis) { // O(V^3 * logV)
        dis = adj; // first iteration done

        for (int m = 2; ; m *= 2) { // logV times
            for (int i = 1; i <= n; i++) { // V times
                for (int j = 1; j <= n; j++) { // V times
                    for (int k = 1; k <= n; k++) { // V times
                        if (dis[i][k] == INF || dis[k][j] == INF) continue; // k is unreachable so far from i, will help for negative weights

                        // check if j should be visited from i via k
                        if (dis[i][k] + dis[k][j] < dis[i][j]) {
                            dis[i][j] = dis[i][k] + dis[k][j];
                        }
                    }
                }
            }
            if (m >= n) break; // m needs to be at least n-1
        }
    }

    void floydWarshall(vector<vector<int> > &dis) { // O(V^3)
        dis = adj;

        for (int k = 1; k <= n; k++) {
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    if (dis[i][k] == INF || dis[k][j] == INF) continue;

                    if (dis[i][k] + dis[k][j] < dis[i][j]) {
                        dis[i][j] = dis[i][k] + dis[k][j];
                    }
                }
            }
        }
    }
};

