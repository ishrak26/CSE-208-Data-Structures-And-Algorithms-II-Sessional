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

    // returns -1 if des cannot be reached from the src
    // assumes all weights are non-negative
    int dijkstra(int src, int des, vector<int> &path) {
        priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
        vector<int> dis(n, INF);
        dis[src] = 0;
        pq.push({dis[src], src});
        vector<int> par(n, -1);

        while (!pq.empty()) {
            pair<int, int> p = pq.top();
            pq.pop();
            int u = p.second;
            int dist = p.first;

            if (dist != dis[u]) continue;
            // dis was updated when this node was in the queue
            // sth better has been already processed
            // no need to process this

            for (int i = 0, sz = adj[u].size(); i < sz; i++) {
                int v = adj[u][i].first;
                int w = adj[u][i].second;
                if (dis[u] + w < dis[v]) {
                    dis[v] = dis[u] + w;
                    par[v] = u;
                    pq.push({dis[v], v});
                }
            }
        }

        // backtrack the path
        for (int curr = des; curr != -1; curr = par[curr]) {
            path.push_back(curr);
        }
        reverse(path.begin(), path.end());

        return dis[des]==INF ? -1 : dis[des];
    }
};

