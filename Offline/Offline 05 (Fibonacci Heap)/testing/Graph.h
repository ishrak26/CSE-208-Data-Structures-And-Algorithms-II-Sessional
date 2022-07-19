#include<bits/stdc++.h>
#include "fibonacci_heap.h"

using namespace std;

class Graph {
    int n; // no. of vertices
    int m; // count of the no. of edges
    vector<vector<pair<int, int> > > adj; // adjacency list of all vertices (v, w)
    const int INF = 1<<30;

public:
    // n is the no. of vertices, m being the no. of edges
    Graph(int n, int m) { // O(V+E)
        this->n = n;
        adj.resize(n);
        this->m = 0; // no edge currently added to the graph
    }

    void add_weighted_edge(int u, int v, int cost) { // O(1)
        adj[u].push_back({v, cost}); // directed edge
        m++;
    }

    // returns -1 if des cannot be reached from the src
    // assumes all weights are non-negative
    pair<int, int> dijkstra_bin_heap(int src, int des) { // O(ElogV + V)
        priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq; // (dis[u], u)
        vector<int> dis(n, INF); // O(V)
        vector<int> path(n, INF); // path length for each node, O(V)
        dis[src] = 0;
        pq.push({dis[src], src});
        path[src] = 0;

        while (!pq.empty()) { // O(ElogV)
            pair<int, int> p = pq.top();
            pq.pop(); // O(logV)
            int u = p.second;
            int dist = p.first;

            if (dist != dis[u]) continue;
            // dis was updated when this node was in the queue
            // sth better has been already processed
            // no need to process this

            for (int i = 0, sz = adj[u].size(); i < sz; i++) { // in total: O(E *logV)
                int v = adj[u][i].first;
                int w = adj[u][i].second;
                if (dis[u] + w < dis[v]) {
                    dis[v] = dis[u] + w;
                    path[v] = path[u] + 1;
                    pq.push({dis[v], v}); // O(logV)
                }
                else if (dis[u] + w == dis[v] && path[v] > path[u] + 1) { // optimize path length
                    path[v] = path[u] + 1;
                }
            }
        }

        return dis[des]==INF ? make_pair(-1, -1) : make_pair(dis[des], path[des]);
    }

    pair<int, int> dijkstra_fib_heap(int src, int des) { // O(VlgV + E)
        Fibonacci_heap<pair<int, int> > fq; // (dis[v], v)
        vector<int> dis(n, INF); // O(V)
        vector<int> path(n, INF); // path length for each node, O(V)
        vector<int> ids(n+1, -1); // node_ids for all insertions, O(V)

        dis[src] = 0;
        path[src] = 0;

        for (int i = 0; i < n; i++) { // O(V)
            ids[i] = fq.insert({dis[i], i}); // O(1)
        }

        while (!fq.empty()) { // O(VlgV + E)
            pair<int, int> p = fq.extractMinKey(); // O(lgV) amortized
            int u = p.second;
            for (int i = 0, sz = adj[u].size(); i < sz; i++) {
                pair<int, int> v = adj[u][i]; // (to, weight)
                if (dis[u] + v.second < dis[v.first]) {
                    dis[v.first] = dis[u] + v.second;
                    path[v.first] = path[u] + 1;
                    fq.decreaseKey(ids[v.first], {dis[v.first], v.first}); // O(1) amortized
                }
                else if (dis[u] + v.second == dis[v.first] && path[v.first] > path[u] + 1) { // optimize path length
                    path[v.first] = path[u] + 1;
                }
            }
        }

        return dis[des]==INF ? make_pair(-1, -1) : make_pair(dis[des], path[des]);
    }
};

