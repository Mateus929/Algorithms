#include<bits/stdc++.h>

#define pii pair<int,int>
#define ff first
#define ss second
#define INF INT_MAX

using namespace std;

vector<pii > g[201];
int cap[201][201];

int ShortestPath(int n, int s, int t, vector<int> &path, int &dt) {
    vector<int> d(n + 1, INF), p(n + 1, -1), cnt(n + 1, 0);
    vector<bool> inq(n + 1, 0);
    queue<int> q;
    q.push(s);
    d[s] = 0;
    inq[s] = 1;

    while(!q.empty()) {
        int v = q.front();
        q.pop();
        inq[v] = 0;
        for(pii E: g[v]) {
            int to = E.ff, len = E.ss;
            if(d[to] > d[v] + len && cap[v][to] > 0) {
                d[to] = d[v] + len;
                p[to] = v;
                if(!inq[to]) {
                    inq[to] = 1;
                    q.push(to);
                }
            }
        }
    }
    dt = d[t];
    int v = t, mn = INF;
    while(p[v] != -1) {
        mn = min(mn, cap[p[v]][v]);
        path.push_back(v);
        v = p[v];
    }
    path.push_back(s);
    return mn;
}

int MinCostFlow(int n, int s, int t, int k) {
    int flow = 0, cost = 0, dt = 0;
    while(flow < k) {
        vector<int> path;
        int f = ShortestPath(n, s, t, path, dt);
        if(dt == INF)
            break;
        f = min(f, k - flow);
        flow += f;
        cost += f * dt;
        for(int i = 0; i < path.size() - 1; i++) {
            int v = path[i], u = path[i + 1];
            cap[v][u] += f;
            cap[u][v] -= f;
        }
    }
    if(flow < k)
        return -1;
    return cost;
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    for(int i = 1; i <= m; i++) {
        int v, u, c, w;
        cin >> v >> u;
        cin >> c >> w;
        cap[v][u] += c;
        g[v].push_back({u, w});
    }
    int s, t;
    cin >> s >> t;
    cout << MinCostFlow(n, s, t, k);
}
