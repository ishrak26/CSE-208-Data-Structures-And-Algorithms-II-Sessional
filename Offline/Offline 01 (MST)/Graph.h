#include<vector>
#include<queue>
#include<algorithm>
#include<cassert>

using namespace std;

#define ld long double

class Graph {
    int n; // no. of vertices
    int m; // no. of edges
    vector<vector<pair<int, ld> > > adj; // adjacency list of all vertices
    vector<pair<int, int> > edges; // list of all edges
    vector<pair<ld, int> > costs; // list of cost of an edge

    vector<int> par; // set for DSU
    vector<int> sz; // sizes of disjoint sets

    // dsu-find
    int find_parent(int u) {
        if (u == par[u]) return u;
        return par[u] = find_parent(par[u]);
    }

    // dsu-union
    bool union_sets(int u, int v) {
        int par_u = find_parent(u);
        int par_v = find_parent(v);
        if (par_u == par_v) {
            // already belong to the same set
            return false;
        }
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
    Graph(int n, int m) {
        this->n = n;
        adj.resize(n);
        edges.resize(m);
        costs.resize(m);
        this->m = 0;

        par.resize(n);
        sz.resize(n);
    }

    void add_weighted_edge(int u, int v, ld &cost) {
        adj[u].push_back({v, cost});
        adj[v].push_back({u, cost});
        edges[m] = {u, v};
        costs[m] = {cost, m};
        m++;
    }

    // returns -1 if forest
    ld find_MST_Prim(vector<pair<int, int> > &taken_edges) {
        vector<bool> taken(n, 0);
        priority_queue<pair<ld, pair<int, int> >, vector<pair<ld, pair<int, int> > >, greater<pair<ld, pair<int, int> > > > pq; // min-heap
        pq.push({0.0, {-1, 0}}); // weight, (u, v), where u is the parent of v
        ld mst = 0;
        int cnt = 0;

        while (!pq.empty()) {
            pair<ld, pair<int, int> > p = pq.top();
            pq.pop();
            pair<int, int> e = p.second;
            int u = e.second;
            if (taken[u]) continue;

            // take this edge
            if (e.first != -1) taken_edges.push_back(e);
            taken[u] = 1;
            mst += p.first;
            cnt++;
            if (cnt == n) break;
            for (int i = 0, siz = adj[u].size(); i < siz; i++) {
                int v = adj[u][i].first;
                ld w = adj[u][i].second;
                if (!taken[v]) {
                    pq.push({w, {u, v}});
                }
            }
        }
        if (cnt == n) return mst;
        return -1.0;
    }

    // returns -1 if no MST possible i.e. forest
    ld find_MST_Kruskal(vector<pair<int, int> > &taken_edges) {
        // sort the edges based on cose in ascending order
        assert(costs.size() == m);
        sort(costs.begin(), costs.end());

        // makeset
        for (int i = 0; i < n; i++) {
            par[i] = i;
            sz[i] = 1;
        }

        ld mst = 0.0;
        // traverse through all the edges
        for (int i = 0; i < m; i++) {
            int idx = costs[i].second;
            int u = edges[idx].first;
            int v = edges[idx].second;
            if (union_sets(u, v)) {
                mst += costs[i].first;
                taken_edges.push_back(edges[idx]);
            }

        }
        for (int i = 0; i < n; i++) {
            if (sz[i] == n) return mst;
        }
        return -1.0;
    }
};

