#include<bits/stdc++.h>

using namespace std;

class Graph {
    int n; // no. of vertices
    int m; // count of the no. of edges
    vector<vector<pair<int, int> > > adj; // adjacency list of all vertices
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

    // best[i] = -1 if vertex i cannot be reached from the src
    // assumes all weights are non-negative
    void dijkstra(int src, vector<int> &best) { // O(ElogV + V)
        priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq; // (dis[u], u)
        vector<int> dis(n, INF); // O(V)
        best.assign(n, INF); // O(V)
        dis[src] = 0;
        best[src] = 0;
        pq.push({dis[src], src}); // O(logV)

        while (!pq.empty()) { // O(ElogV)
            pair<int, int> p = pq.top();
            pq.pop(); // O(logV)
            int u = p.second;
            int dist = p.first;

            if (dist != dis[u]) {
                assert(dis[u] < dist);
                continue;
            }
            // dis was updated when this node was in the queue
            // sth better has been already processed
            // no need to process this

            for (int i = 0, sz = adj[u].size(); i < sz; i++) { // in total: O(E *logV)
                int v = adj[u][i].first;
                int w = adj[u][i].second;
                if (dis[u] + w < dis[v]) {
                    // cost can be minimized
                    // best must be updated
                    dis[v] = dis[u] + w;
                    best[v] = best[u] + 1;
                    pq.push({dis[v], v}); // O(logV)
                }
                else if (dis[u] + w == dis[v]) {
                    // cost will remain the same
                    // check if best can be updated
                    if (best[u] + 1 < best[v]) {
                        best[v] = best[u] + 1;
                        pq.push({dis[v], v}); // O(logV)
                    }
                }
            }
        }

        // check if any node is unreachable from the src
        for (int i = 0; i < n; i++) {
            if (best[i] == INF) best[i] = -1;
        }
    }
};

