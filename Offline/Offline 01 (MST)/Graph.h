#include<bits/stdc++.h>

using namespace std;

#define ld long double

class Graph {
    int n; // no. of vertices
    int m; // count of the no. of edges
    vector<vector<pair<int, ld> > > adj; // adjacency list of all vertices
    vector<pair<int, int> > edges; // list of all edges in (u, v) form
    vector<pair<ld, int> > costs; // list of cost of an edge, edge is in (cost, edge_id) form

    vector<int> par; // disjoint sets for DSU
    vector<int> sz; // sizes of disjoint sets

    // dsu-find
    int find_parent(int u) { // O(logV)
        if (u == par[u]) return u;
        return par[u] = find_parent(par[u]); // path compression
    }

    // dsu-union
    // returns true if u and v belongs to different set, and truly merged
    // returns false otherwise
    bool union_sets(int u, int v) { // O(logV)
        int par_u = find_parent(u); // O(logV)
        int par_v = find_parent(v); // O(logV)
        if (par_u == par_v) {
            // already belong to the same set
            return false;
        }
        // union by size
        if (sz[par_u] < sz[par_v]) {
            swap(u, v);
            swap(par_u, par_v);
        }
        // add v to u
        par[par_v] = par_u;
        sz[par_u] += sz[par_v];
        return true;
    }

public:
    // n is the no. of vertices, m being the no. of edges
    Graph(int n, int m) { // O(V+E)
        this->n = n;
        adj.resize(n);
        edges.resize(m);
        costs.resize(m);
        this->m = 0; // no edge currently added to the graph

        par.resize(n);
        sz.resize(n);
    }

    void add_weighted_edge(int u, int v, ld &cost) { // O(1)
        adj[u].push_back({v, cost});
        adj[v].push_back({u, cost}); // undirected graph
        edges[m] = {u, v};
        costs[m] = {cost, m};
        m++;
    }

    // returns -1 if forest i.e. disconnected
    // taken_edges will be updated with the edges actually included in the MST
    ld find_MST_Prim(vector<pair<int, int> > &taken_edges) { // O(V + ElogV) = O(ElogV)
        vector<bool> taken(n, 0); // O(V)
        priority_queue<pair<ld, pair<int, int> >, vector<pair<ld, pair<int, int> > >, greater<pair<ld, pair<int, int> > > > pq; // min-heap
        // (weight, (u, v)), where u is the predecessor of v

        pq.push({0.0, {-1, 0}}); // starting from vertex 0
        ld mst = 0.0;
        int cnt = 0; // keeps track of the no. of vertices included in the MST

        while (!pq.empty()) { // O(ElogE) = O(ElogV)
            pair<ld, pair<int, int> > p = pq.top();
            pq.pop(); // O(logE) = O(logV)
            pair<int, int> e = p.second; // (a, b) where a is the predecessor of b
            int u = e.second;
            if (taken[u]) continue;

            // take this edge
            if (e.first != -1) taken_edges.push_back(e); // predecessor is not the root
            taken[u] = 1; // u is now part of the MST
            mst += p.first; // weight of this newly taken edge
            cnt++;
            if (cnt == n) break; // MST construction completed

            // O(ElogE)
            for (int i = 0, siz = adj[u].size(); i < siz; i++) { // total traversal is O(E) times throughout the whole while loop
                int v = adj[u][i].first;
                ld w = adj[u][i].second;
                if (!taken[v]) {
                    pq.push({w, {u, v}}); // O(logE)
                }
            }
        }

        if (cnt == n) return mst; // MST was successfully constructed with n vertices and n-1 edges
        return -1.0; // disconnected graph i.e. forest
    }

    // returns -1 if no MST possible i.e. forest
    // taken_edges will be updated with the edges actually included in the MST
    ld find_MST_Kruskal(vector<pair<int, int> > &taken_edges) { // O(V + ElogV) = O(ElogV)

        // sort the edges based on cost in increasing order of weights
        assert(costs.size() == m);
        sort(costs.begin(), costs.end()); // O(ElogE) = O(ElogV)

        // makeset for DSU
        for (int i = 0; i < n; i++) { // O(V)
            par[i] = i;
            sz[i] = 1;
        }

        ld mst = 0.0;

        // traverse through all the edges O(E)
        for (int i = 0; i < m; i++) { // O(ElogV)
            int idx = costs[i].second;
            int u = edges[idx].first;
            int v = edges[idx].second;
            if (union_sets(u, v)) { // O(logV)
                mst += costs[i].first;
                taken_edges.push_back(edges[idx]); // O(1)
            }

        }

        for (int i = 0; i < n; i++) { // O(V)
            if (sz[i] == n) return mst; // all n vertices connected in the same set implying MST was constructed successfully
        }
        return -1.0; // disconnected graph i.e. forest
    }
};

