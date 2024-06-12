#include<bits/stdc++.h>

#define INF INT_MAX
#define pii pair<int,int>

using namespace std;

vector<pii > g[100001];

void dijkstra(int n, int st, int fs) {
    vector<int> d(n + 1, INF), parent(n + 1, -1);
    set<pii > s;
    d[st] = 0;
    s.insert({0, st});
    while(!s.empty()) {
        int v = s.begin()->second;
        s.erase(s.begin());
        for(pii u: g[v]) {
            int to = u.first;
            int len = u.second;
            if(d[v] + len < d[to]) {
                s.erase({d[to], to});
                d[to] = d[v] + len;
                s.insert({d[to], to});
                parent[to] = v;
            }
        }
    }
    if(d[fs] == INF) {
        cout << -1;
        return;
    }
    vector<int> path;
    cout << d[fs] << "\n";
    int cur = fs;
    while(cur != -1) {
        path.push_back(cur);
        cur = parent[cur];
    }
    reverse(path.begin(), path.end());
    for(int v: path)
        cout << v << " ";
}

int main() {
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        int v, u, w;
        cin >> v >> u >> w;
        g[v].push_back({u, w});
    }
    int st, fs;
    cin >> st >> fs;
    dijkstra(n, st, fs);
}
