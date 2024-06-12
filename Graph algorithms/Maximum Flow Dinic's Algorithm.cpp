#include<bits/stdc++.h>

#define INF INT_MAX

using namespace std;

struct Edge {
    int v, u, cap, flow = 0;

    Edge(int v, int u, int cap) : v(v), u(u), cap(cap) {};

    int res_cap() {
        return cap - flow;
    }

    void augment(int new_flow) {
        flow += new_flow;
    }
};

struct Dinic {
    int n, s, t, e = 0;
    vector<int> level, ptr;
    vector<Edge> edges;
    vector<vector<int>> g;

    Dinic(int n, int s, int t) : n(n), s(s), t(t) {
        level.resize(n + 1);
        ptr.resize(n + 1);
        g.resize(n + 1);
    }

    void add(int v, int u, int cap) {
        g[v].push_back(e++);
        g[u].push_back(e++);
        edges.emplace_back(v, u, cap);
        edges.emplace_back(u, v, 0);
    }

    bool BFS() {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        q.push(s);
        level[s] = 0;
        while(!q.empty()) {
            int v = q.front();
            q.pop();
            for(int id: g[v]) {
                Edge E = edges[id];
                if(E.res_cap() > 0 && level[E.u] == -1) {
                    q.push(E.u);
                    level[E.u] = level[v] + 1;
                }
            }
        }
        return level[t] != -1;
    }

    int DFS(int v, int flow) {
        if(v == t)
            return flow;
        for(int &i = ptr[v]; i < g[v].size(); i++) {
            Edge &E = edges[g[v][i]];
            Edge &F = edges[g[v][i] ^ 1];
            if(E.res_cap() > 0 && level[E.u] == level[v] + 1) {
                int new_flow = DFS(E.u, min(flow, E.res_cap()));
                if(new_flow) {
                    E.augment(new_flow);
                    F.augment(-new_flow);
                    return new_flow;
                }
            }
        }
        return 0;
    }

    int MaxFlow() {
        int max_flow = 0;
        while(true) {
            if(!BFS())
                break;
            fill(ptr.begin(), ptr.end(), 0);
            int flow = 0;
            while(flow = DFS(s, INF)) {
                max_flow += flow;
            }
        }
        return max_flow;
    }
};

int main() {
    int n, m, s, t;
    cin >> n >> m;
    cin >> s >> t;
    Dinic G(n, s, t);
    for(int i = 1; i <= m; i++) {
        int v, u, cap;
        cin >> v >> u >> cap;
        G.add(v, u, cap);
    }
    cout << G.MaxFlow();
}
