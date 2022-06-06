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

    // detect negative cycle
    int bellman_ford(int src, int des, vector<int> &path, bool &neg_cycle, bool &unreachable) {
        vector<int> dis(n, INF);
        dis[src] = 0;
        vector<int> par(n, -1);

        for (int i = 1; i < n; i++) {
            int flag = 1;
            for (int u = 0; u < n; u++) {
                int sz = adj[u].size();
                for (int j = 0; j < sz; j++) {
                    int v = adj[u][j].first;
                    int w = adj[u][j].second;
                    if (dis[u] < INF && dis[u] + w < dis[v]) { // dis[u] must first be reachable from src
                        dis[v] = max(-INF, dis[u] + w); // dis[v] can never be less than -INF
                        par[v] = u;
                        if (flag) flag = 0;
                    }
                }
            }
            if (flag) break; // no relaxation took place in this iteration i.e. end of relaxation
        }

        for (int u = 0; u < n; u++) {
            int sz = adj[u].size();
            for (int j = 0; j < sz; j++) {
                int v = adj[u][j].first;
                int w = adj[u][j].second;
                if (dis[u] < INF && dis[u] + w < dis[v]) { // dis[u] must first be reachable from src
                    // relaxation still possible
                    // negative cycle
                    neg_cycle = true;
                    return -1;
                }
            }
        }
        // no negative cycle

        // check if des is unreachable from src
        if (dis[des] == INF) {
            unreachable = true;
            return -1;
        }

        // des is reachable from src
        // backtrack the path
        for (int curr = des; curr != -1; curr = par[curr]) {
            path.push_back(curr);
        }
        reverse(path.begin(), path.end());

        return dis[des];


//        to see if the negative cycle impacts the des
//        for (int i = 1; i < n; i++) {
//            int flag = 1;
//            for (int u = 0; u < n; u++) {
//                int sz = adj[u].size();
//                for (int j = 0; j < sz; j++) {
//                    int v = adj[u][j].first;
//                    int w = adj[u][j].second;
//                    if (dis[u] < INF) {
//                        // u is reachable from 1
//                        dis[v] = max(-INF, dis[v]);
//                        if (dis[u] + w < dis[v]) { // relaxation still possible
//                            dis[v] = -INF; // v is reachable through a neg cycle
//                            if (flag) flag = 0;
//                        }
//                    }
//                }
//            }
//            if (flag) break; // no relaxation took place in this iteration i.e. end of relaxation
//        }
    }
};

