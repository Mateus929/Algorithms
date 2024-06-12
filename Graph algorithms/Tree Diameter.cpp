#include <bits/stdc++.h>

using namespace std;

vector<int> g[100001];

void DiamDFS(int v, int e, int dist, int &dm, int &diam) {
    if(dist > diam) {
        dm = v;
        diam = dist;
    }
    for(int u: g[v])
        if(u != e)
            DiamDFS(u, v, dist + 1, dm, diam);
}

void FindDiam(int &dm1, int &dm2, int &diam) {
    DiamDFS(1, -1, 0, dm1, diam);
    diam = 0;
    DiamDFS(dm1, -1, 0, dm2, diam);
}

int main() {
    int n;
    cin >> n;
    for(int i = 1; i < n; i++) {
        int v, u;
        cin >> v >> u;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    int dm1, dm2, diam;
    FindDiam(dm1, dm2, diam);
    cout << dm1 << " " << dm2 << " " << diam;
}
