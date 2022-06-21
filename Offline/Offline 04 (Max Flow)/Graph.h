#include<bits/stdc++.h>

using namespace std;

class Graph {
    const int INF = 1<<25;

    int n; // no. of vertices in the graph
    vector<vector<int> > adj; // adjacency list of all vertices (forward + back)
    vector<vector<int> > cf; // residual capacity for all forward and back edges
    vector<int> par; // parent node for all vertices constructed during bfs
    int game_cnt; // total no. of matches played in this graph

    // add an edge in the graph and set its initial capacity
    void add_weighted_edge(int u, int v, int cap) { // O(1)
        adj[u].push_back(v);
        adj[v].push_back(u);
        cf[u][v] = cap;
    }

    // bfs to find augmenting path in Edmonds-Karp algorithm
    int bfs_find_aug_path(int s, int t) { // O(V + E)
        fill(par.begin(), par.end(), -1);
        queue<pair<int, int> > q; // (node, flow)
        q.push({s, INF});
        par[s] = -2;

        while (!q.empty()) {
            int u = q.front().first;
            int flow = q.front().second;
            q.pop();

            for (int i = 0, sz = adj[u].size(); i < sz; i++) {
                int v = adj[u][i];
                if (par[v] == -1 && cf[u][v] > 0) {
                    // v is yet to be visited
                    // path can be extended
                    int new_flow = min(flow, cf[u][v]); // bottleneck for this path
                    par[v] = u;
                    if (v == t) return new_flow; // path exists from s to t
                    q.push({v, new_flow});
                }
            }
        }
        return 0; // no augmenting path to t exists
    }

    // implementation help taken from https://cp-algorithms.com/graph/edmonds_karp.html#edmonds-karp-algorithm
    int edmonds_karp(int s, int t) { // O(VE^2)
        int flow = 0;
        int new_flow;
        while ((new_flow = bfs_find_aug_path(s, t)) > 0) {
            // there exists a augmenting path from s to t
            flow += new_flow;
            // backtrack the path to recalculate the flow in the residual graph
            int cur = t;
            while (cur != s) {
                int pre = par[cur];
                cf[pre][cur] -= new_flow;
                cf[cur][pre] += new_flow;
                cur = pre;
            }
        }
        return flow;
    }

    // min-cut
    void bfs_find_reachable_nodes(int s) { // O(V+E)
        queue<int> q;
        fill(par.begin(), par.end(), -1);
        par[s] = -2;
        q.push(s);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int i = 0, sz = adj[u].size(); i < sz; i++) {
                int v = adj[u][i];
                if (par[v] == -1 && cf[u][v] > 0) {
                    // v is reachable from s
                    par[v] = u;
                    q.push(v);
                }
            }
        }
    }

public:
    Graph(int tot_teams, vector<vector<int> > &games, int cur_team, vector<int> &wins, vector<int> &rems) { // O(V+E)
        // count how many nodes will be in the graph
        // source s, destination t
        // (n-1)(n-2)/2 games
        // n-1 teams
        game_cnt = ((tot_teams-1)*(tot_teams-2))/2;
        n = 2 + game_cnt + tot_teams;
        // keep a dummy node for cur_team for simplicity
        // node for cur_team will be kept disconnected from the graph

        adj.resize(n);
        cf.resize(n, vector<int> (n, 0));
        par.resize(n);
        // s will be node 0
        // then there will be all the game nodes from 1 to game_cnt
        // then all to team nodes from game_cnt+1 to game_cnt+tot_teams
        // t will be node n-1

        // construct the graph
        int curr_game = 1;
        for (int i = 0; i < tot_teams; i++) {
            if (i == cur_team) continue;
            for (int j = i+1; j < tot_teams; j++) {
                if (j == cur_team) continue;

                // game will be between team i and team j
                // connect s to this match
                add_weighted_edge(0, curr_game, games[i][j]);

                // connect this match to playing teams
                add_weighted_edge(curr_game, game_cnt+1+i, INF);
                add_weighted_edge(curr_game, game_cnt+1+j, INF);
                curr_game++;
            }
        }
        assert(curr_game == game_cnt+1);

        // add team nodes to t
        for (int i = 0; i < tot_teams; i++) {
            if (i == cur_team) continue;
            add_weighted_edge(game_cnt+1+i, n-1, wins[cur_team]+rems[cur_team]-wins[i]);
        }
    }

    // check if full in-flow could be given
    bool check_saturation() { // O(VE^2)
        int flow = edmonds_karp(0, n-1);
        for (int i = 1; i <= game_cnt; i++) {
            if (cf[0][i] > 0) {
                // this edge could not be saturated
                return false;
            }
        }
        // all edges from s to a game is saturated
        return true;
    }

    void find_eliminating_teams(vector<int> &teams, int tot_teams) { // O(V+E)
        // run a bfs to find reachable nodes from s
        bfs_find_reachable_nodes(0); // min-cut
        // find team vertices reachable from s
        for (int i = 0; i < tot_teams; i++) {
            if (par[game_cnt+1+i] != -1) teams.push_back(i);
        }
    }
};

